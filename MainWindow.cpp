#include <windows.h>
#include "MainWindow.h"
#include "WindowsX.h"

// Recalculate drawing layout when the size of the window changes.

void MainWindow::OnPaintScene()
{
	if (layoutRect.bottom<1.0f)
	{
		CalculateLayout();
	}
	pRenderTarget->DrawText(
		wszText_,        // The string to render.
		cTextLength_,    // The string's length.
		pTextFormat_,    // The text format.
		layoutRect,       // The region of the window where the text will be rendered.
		pBlackBrush_     // The brush used to draw the text.
	);
}

void MainWindow::CalculateLayout()
{
	// “екущее положени€ курсора
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hwnd, &pt);

	RECT rc;
	GetClientRect(m_hwnd, &rc);
	const float dipX = DPIScale::PixelsToDipsX(rc.right);
	const float dipY = DPIScale::PixelsToDipsY(rc.bottom);
	
	// –асположение в зависимости от текущего положени€ курсора
	curX = pt.x;
	curY = pt.y;
	layoutRect = D2D1::RectF(curX*2, curY*2 - 50, 0, 0);
}
