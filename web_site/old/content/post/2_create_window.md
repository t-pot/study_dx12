+++
title = "2. ウィンドウの生成"
date = 2020-07-15T00:00:02+08:00
description = "ウィンドウの生成"
tags = [
    "DirextX12"
]
showToc = false
+++

# はじめに

Win32アプリケーションとして、ウィンドウを表示します。

# Windowsの表示

まずは、アプリケーションを作成します。

[今回のソースコード](https://github.com/t-pot/study_dx12/tree/master/src/2_1_create_window/)

VisualStudioを立ち上げたら、どのプロジェクトを立ち上げるか聞かれるので、新規のプロジェクトを作成するようにします。
今後、同じプロジェクトを立ち上げるのであれば、左側の最近使ったプロジェクトから選択したり、プロジェクトを読み込みます。
![Visual Studio Installer](start.png)

プロジェクトは、「Windows デスクトップアプリケーション」を作成してください。
![Visual Studio Installer](create_project.png)
次のページで、プロジェクトの名前を入力します。今後、いろいろとファイルを追加していくこともあり、「main」というプロジェクトを作ろうと思います。
![Visual Studio Installer](configure.png)

すると、いろいろなファイルが作られます。
最初に実行されるエントリーポイントの関数 wWinMain は、プロジェクト名のファイルとして作られます。
中身を整理してみました。その中を見ていきましょう。

{{< highlight cpp "linenos=table, linenostart=1">}}
#include "targetver.h"                  // リソースファイルでも使われているので残す
#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include <windows.h>                    // Windows ヘッダー ファイル
#include "resource.h"                   // アイコン


// このコード モジュールに含まれる関数の宣言:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
	// 使わない引数の宣言
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
{{< /highlight >}}

wWinMain 関数では、いろいろなパラメータを設定して、RegisterClassExW の後で CreateWindowW を呼び出します。
これらの呼び出しは定番なので、そんなものと思いましょう。

CreateWindowW の呼び出しが上手くいったら、ShowWindow 関数を呼び出してWindowを表示します。



{{< highlight cpp "linenos=table, linenostart=26">}}
	// 初期化用パラメータ
	const int width = 800;
	const int height = 600;
	const WCHAR *szWindowClass = TEXT("window class name");  // ウィンドウクラス名
	const WCHAR *szTitle = TEXT("window title");             // タイトルバーの文字列

	// ウィンドウ クラスを登録
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);                 // この構造体のサイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW;             // ウィンドウの挙動の指定
	wcex.lpfnWndProc = WndProc;                       // イベントのコールバック関数の指定
	wcex.cbClsExtra = 0;                              // ウィンドウクラス構造体の追加バイト数
	wcex.cbWndExtra = 0;                              // ウィンドウインスタンスの追加バイト数
	wcex.hInstance = hInstance;                       // アプリケーションのインスタンス
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));// アイコン
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);    // カーソル
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // 背景ブラシ
	wcex.lpszMenuName = nullptr;                      // メニュー
	wcex.lpszClassName = szWindowClass;               // ウィンドウクラス名
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));// 小さいアイコン
	RegisterClassExW(&wcex);

	// メイン ウィンドウを作成
	HWND hWnd = CreateWindowW(
		szWindowClass,                      // ウィンドウクラス名
		szTitle,                            // タイトルバー文字列
		WS_OVERLAPPEDWINDOW,                // 生成するウィンドウ種類
		CW_USEDEFAULT, 0,                   // ウィンドウの位置
		width, height,                      // ウィンドウのサイズ
		nullptr,                            // 親ウィンドウ
		nullptr,                            // メニューバー
		hInstance,                          // アプリケーションのインスタンス
		nullptr);                           // WM_CREATE メッセージに渡すパラメータ
	if (!hWnd) {// 失敗時
		MessageBox(hWnd, TEXT("メイン ウィンドウの生成に失敗しました"), TEXT("Error!"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
{{< /highlight >}}

アプリケーションが立ち上がったら無限ループを回します。
キーが押されたなどの各種イベントを読み込んで、処理をして、終了のメッセージが来るまで続けます。

{{< highlight cpp "linenos=table, linenostart=62">}}
	// メイン メッセージ ループ:
	MSG msg;
	do
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {// イベントがあるか調べる
			TranslateMessage(&msg); // キーの分析
			DispatchMessage(&msg);  // イベント処理
		}
	} while (msg.message != WM_QUIT);

    return (int) msg.wParam;
}

{{< /highlight >}}

ウィンドウで発生するイベントですが、これは、WndProc という関数で処理をします。
この関数自体は、RegisterClassExW の引数でコールバック関数として指定します。

今後、この関数の「WM_PAINT」のイベントとして、ゲームの処理を挿入していくことになります。

{{< highlight cpp "linenos=table, linenostart=76">}}
//
//  メイン ウィンドウのイベントメッセージの処理
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_PAINT:
		// ここに描画処理が入る
		break;
	case WM_DESTROY: // 中止メッセージ
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);// ディフォルト処理をする
    }
    return 0;
}
{{< /highlight >}}

# アプリケーションクラスの導入

さて、今まで説明した処理は、Windows 特有の処理でした。
今後、移植性のことを考えたりすると、ウィンドウズクラスのことは極力忘れていきたいです。
この場合の対処方法として、アプリケーションのクラスを作って、そのクラスでゲームを作っていくのが定番の一つです。

今回は、ここで「初期化」、「片付け」、「毎フレームの更新」をするのに注力するアプリケーションクラスを導入しようと思います。

[今回のソースコード](https://github.com/t-pot/study_dx12/tree/master/src/2_2_application_class/)

## アプリケーションクラス

ひとまずのクラスを導入してみましょう。
application.h をヘッダファイルとします。

ウィンドウハンドルやウィンドウ解像度は必要になるので、それらを引数として受け取る初期化関数をもつクラスを作ります。

{{< highlight cpp "linenos=table, linenostart=1">}}
#pragma once

#define WIN32_LEAN_AND_MEAN   // Windows ヘッダーからほとんど使用されていない部分を除外する
#include <windows.h>          // Windows ヘッダー (HWND用)

class Application {
public:
	Application();
	~Application();

	int OnInit(HWND hwnd, int width, int height);// 初期化：終了時は返り値に-1
	void OnDestroy();

	int OnUpdate();// フレーム更新：終了時は返り値に-1
};
{{< /highlight >}}

中身は、ひとまず空っぽです。
実装ファイルは application.cpp とします。

{{< highlight cpp "linenos=table, linenostart=1">}}
#include "application.h"

Application::Application()
{
}

Application::~Application()
{
}

int Application::OnInit(HWND hwnd, int width, int height)
{
	return 0;
}

void Application::OnDestroy()
{
}

int Application::OnUpdate()
{
	return 0;
}
{{< /highlight >}}

## アプリケーションクラスの利用

アプリケーションクラスをmain関数に組み込みます。main.cppでヘッダファイルをインクルードして、
汚いですが、クラスインスタンスのポインタを保持するようにしてみましょう。

{{< highlight cpp "linenos=table, hl_lines=5 12, linenostart=1">}}
#include "targetver.h"                  // リソースファイルでも使われているので残す
#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include <windows.h>                    // Windows ヘッダー ファイル
#include "resource.h"                   // アイコン
#include "application.h"                // ★アプリケーションクラスの利用


// このコード モジュールに含まれる関数の宣言:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// グローバル変数
static Application*pApp = nullptr;// ★アプリケーションの初期化が終わったら代入される

{{< /highlight >}}

アプリケーションクラスの初期化は、CreateWindowW が成功してからウィンドウを表示する前に行います。
これで、画面が表示される前にいろいろな初期化を用意することができます。

{{< highlight cpp "linenos=table, hl_lines=17-24, linenostart=31">}}
	// メイン ウィンドウを作成
	HWND hWnd = CreateWindowW(
		szWindowClass,                      // ウィンドウクラス名
		szTitle,                            // タイトルバー文字列
		WS_OVERLAPPEDWINDOW,                // 生成するウィンドウ種類
		CW_USEDEFAULT, 0,                   // ウィンドウの位置
		width, height,                      // ウィンドウのサイズ
		nullptr,                            // 親ウィンドウ
		nullptr,                            // メニューバー
		hInstance,                          // アプリケーションのインスタンス
		nullptr);                           // WM_CREATE メッセージに渡すパラメータ
	if (!hWnd) {// 失敗時
		MessageBox(hWnd, TEXT("メイン ウィンドウの生成に失敗しました"), TEXT("Error!"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	// ★アプリケーションクラスの初期化
	Application app;
	if (app.OnInit(hWnd, width, height))
	{
		MessageBox(hWnd, TEXT("アプリケーションクラスの初期化に失敗しました"), TEXT("Error!"), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	pApp = &app;

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
{{< /highlight >}}

なお、片付けはメインのメッセージループから抜けてから実行します。

{{< highlight cpp "linenos=table, hl_lines=9-13, linenostart=92">}}
	// メイン メッセージ ループ:
	MSG msg;
	do
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {// イベントがあるか調べる
			TranslateMessage(&msg); // キーの分析
			DispatchMessage(&msg);  // イベント処理
		}
	} while (msg.message != WM_QUIT);

	app.OnDestroy();// ★ゲームエンジンの後片付け

    return (int) msg.wParam;
}
{{< /highlight >}}

更新処理は、「WM_PAINT」イベント行います。

```cpp  {linenos=table, hl_lines=9-13, linenostart=92}
//
//  メイン ウィンドウのイベントメッセージの処理
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
		// ★ゲームエンジンのフレーム毎の処理
		if (pApp && pApp->OnUpdate()) {// 0以外で終了
			pApp = nullptr;// すぐにOnUpdateを呼べなくする
			PostQuitMessage(0);// 終了リクエスト
		}
        break;
    case WM_DESTROY: // 中止メッセージ
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);// ディフォルト処理をする
    }
    return 0;
}
```
