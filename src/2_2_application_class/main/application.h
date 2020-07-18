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
