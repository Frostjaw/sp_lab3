#include "Direct2DWindow.h"
#include "WindowsX.h"
#pragma comment(lib, "d2d1")

float DPIScale::scaleX = 1.0f;
float DPIScale::scaleY = 1.0f;

Direct2DWindow::Direct2DWindow() : pFactory(NULL), pRenderTarget(NULL)
{
}


Direct2DWindow::~Direct2DWindow()
{
}

HRESULT Direct2DWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget);
		if (SUCCEEDED(hr))
		{
			hr = CreateAdditionalGraphicsResources();
		}
	}
	return hr;
}

HRESULT Direct2DWindow::CreateAdditionalGraphicsResources()
{
	return S_OK;
}

void Direct2DWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
}

void Direct2DWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		OnPaintScene();
		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(m_hwnd, &ps);
	}
}

void Direct2DWindow::Resize()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

bool Direct2DWindow::HandleAdditionalMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	switch (uMsg)
	{
	case WM_CREATE:
		if (!OnCreate())
		{
			return false;  // Неудача CreateWindowEx.
		}
		DPIScale::Initialize(pFactory);
		return true;

	case WM_PAINT:
		OnPaint();
		return true;


	case WM_LBUTTONDOWN:
	{

		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		POINT pt1;
		while (DragDetect(m_hwnd, pt))
		{
			GetCursorPos(&pt1);
			ScreenToClient(m_hwnd, &pt1);
			// Проверка на нажатие по тексту
			if ((abs(int(pt1.x - curX)) < 350) && (abs(int(pt1.y - curY)) < 100)) OnPaint();
		}
	}
	return 0;

	case WM_SIZE:
		Resize();
		return true;
	}
	return false;
}

bool Direct2DWindow::OnCreate()
{
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
	{
		return false;  // Неудача CreateWindowEx.
	}
	return true;
}

void Direct2DWindow::OnDestroy()
{
	DiscardGraphicsResources();
	SafeRelease(&pFactory);
}
