#pragma once
#include <dwrite.h>
#include "Direct2DWindow.h"
class DWriteWindow :
	public Direct2DWindow
{
protected:
	IDWriteFactory* pDWriteFactory_;
	IDWriteTextFormat* pTextFormat_;
	ID2D1SolidColorBrush* pBlackBrush_;
public:
	DWriteWindow();
	~DWriteWindow();
	bool OnCreate();
	HRESULT CreateAdditionalGraphicsResources();
	void    DiscardGraphicsResources();
	void OnDestroy();
};

