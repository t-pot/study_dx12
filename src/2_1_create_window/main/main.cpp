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
