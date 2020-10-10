#include "DWriteWindow.h"
#pragma comment(lib, "DWrite")


DWriteWindow::DWriteWindow()
{
}


DWriteWindow::~DWriteWindow()
{
}

bool DWriteWindow::OnCreate()
{
	if (!Direct2DWindow::OnCreate())
	{
		return false;
	}
	HRESULT hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory_)
	);
	if (SUCCEEDED(hr))
	{
		hr = pDWriteFactory_->CreateTextFormat(
			L"Gabriola",                // Font family name.
			NULL,                       // Font collection (NULL sets it to use the system font collection).
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			72.0f,
			L"en-us",
			&pTextFormat_
		);
	}
	else
	{
		return false;  // Fail CreateWindowEx.
	}
	// Center align (horizontally) the text.
	if (SUCCEEDED(hr))
	{
		hr = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}
	else
	{
		return false;  // Fail CreateWindowEx.
	}

	if (SUCCEEDED(hr))
	{
		hr = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else
	{
		return false;  // Fail CreateWindowEx.
	}
	return true;
}

HRESULT DWriteWindow::CreateAdditionalGraphicsResources()
{
	HRESULT hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&pBlackBrush_
	);
	if (SUCCEEDED(hr))
	{
		CalculateLayout();
	}
	return hr;
}

void DWriteWindow::DiscardGraphicsResources()
{
	Direct2DWindow::DiscardGraphicsResources();
	SafeRelease(&pBlackBrush_);
}

void DWriteWindow::OnDestroy()
{
	SafeRelease(&pTextFormat_);
	SafeRelease(&pDWriteFactory_);
	Direct2DWindow::OnDestroy();
}
