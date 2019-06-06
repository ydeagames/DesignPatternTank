#include "MyGame.h"

// デバッグコンソール
#include <io.h>
#include <Fcntl.h>

// ウィンドウ幅
constexpr int width = 800;
// ウィンドウ高
constexpr int height = 600;

// デバッグコンソール
static void CreateConsoleWindow() {
#ifdef _DEBUG
	AllocConsole();
	SetConsoleTitleA("ConsoleTitle");
	typedef struct { char* _ptr; int _cnt; char* _base; int _flag; int _file; int _charbuf; int _bufsiz; char* _tmpfname; } FILE_COMPLETE;
	*(FILE_COMPLETE*)stdout = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
	*(FILE_COMPLETE*)stderr = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((intptr_t)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT), "w");
	*(FILE_COMPLETE*)stdin = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((intptr_t)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r");
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
#endif
}

// エントリポイント Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	CreateConsoleWindow();

    if (!DirectX::XMVerifyCPUSupport())
        return 1;
	// COMライブラリを初期化する
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// MyGameオブジェクトを生成する
	MyGame myGame(width, height);
	// ゲームを実行する
	MSG msg = myGame.Run();

	// COMライブラリの終了処理をする
    CoUninitialize();
    return (int) msg.wParam;
}
