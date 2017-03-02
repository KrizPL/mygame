#include <Windows.h>
#include "..\Engine\Render.h"

#pragma comment(lib, "Debug/Engine.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hWnd;
MSG message;
bool isRunning = true;
Engine::CRender* renderer;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPCWSTR className = TEXT("MainWnd");
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = className;
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(0, L"Cannot create window", L"Error", MB_ICONERROR);
		return -1;
	}

	hWnd = CreateWindowEx(WS_EX_WINDOWEDGE, className, L"Engine test", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);
	if(!hWnd)
	{
		MessageBox(0, L"Cannot create window", L"Error", MB_ICONERROR);
		return -1;
	}
	renderer = new Engine::CRender();
	renderer->OpenGLInit(hWnd, 800, 600, 32);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (isRunning)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		renderer->startFrame();
		renderer->endFrame();
	}
	if (renderer)
	{
		delete renderer;
		renderer = 0;
	}
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		isRunning = false;
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}