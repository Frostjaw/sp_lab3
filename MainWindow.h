#pragma once
#include "DWriteWindow.h"

class MainWindow : public DWriteWindow
{
	const wchar_t* wszText_;
	UINT32 cTextLength_;
	D2D1_RECT_F layoutRect;
public:

	MainWindow()
	{
		wszText_ = L"Hello World using  DirectWrite!";
		cTextLength_ = (UINT32)wcslen(wszText_);
		layoutRect.bottom = layoutRect.right = 0.0f;
		layoutRect.left = layoutRect.top = 0.0f;
	}

	PCWSTR  ClassName() const { return L"SimpleText Class"; }
	void OnPaintScene();
	void    CalculateLayout();
};

