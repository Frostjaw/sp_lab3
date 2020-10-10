#pragma once
class BaseWindow
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BaseWindow() : m_hwnd(NULL) { }
	void Register();
	BOOL Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	);
	HWND Window() const { return m_hwnd; }

protected:

	virtual PCWSTR  ClassName() const = 0;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual bool HandleAdditionalMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *) { return false; }
	virtual void OnDestroy() {}
	HWND m_hwnd;
	// Для текущей позиции курсора
	float curX = 0, curY = 0;
};
