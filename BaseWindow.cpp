#include <windows.h>
#include "BaseWindow.h"

LRESULT CALLBACK BaseWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BaseWindow *pThis = NULL;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (BaseWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

		pThis->m_hwnd = hwnd;
	}
	else
	{
		pThis = (BaseWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}
	if (pThis)
	{
		return pThis->HandleMessage(uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void BaseWindow::Register()
{
	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = ClassName();
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&wc);
}

BOOL BaseWindow::Create(
	PCWSTR lpWindowName,
	DWORD dwStyle,
	DWORD dwExStyle,
	int x,
	int y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu
)
{
	m_hwnd = CreateWindowEx(
		dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
		nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
	);

	return (m_hwnd ? TRUE : FALSE);
}

LRESULT BaseWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		OnDestroy();
		PostQuitMessage(0);
		return 0;
	}
	LRESULT Result = 0;
	if (HandleAdditionalMessage(uMsg, wParam, lParam, &Result)) return Result;
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
