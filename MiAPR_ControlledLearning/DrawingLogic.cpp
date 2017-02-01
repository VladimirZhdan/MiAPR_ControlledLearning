#include "stdafx.h"
#include "DrawingLogic.h"


DrawingLogic::DrawingLogic()
{

}


DrawingLogic::~DrawingLogic()
{
}

void DrawingLogic::Drawing(HDC hdc, RECT clientRect, vector<ImageVector*> image_vector_list)
{
	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;

	HDC bufferHDC = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);

	try
	{
		HGDIOBJ oldBitmap = SelectObject(bufferHDC, bitmap);
		FillRect(bufferHDC, &clientRect, (HBRUSH)WHITE_BRUSH);

		for (ImageVector* image_vector : image_vector_list)
		{
			image_vector->Draw(bufferHDC);
		}

		BitBlt(hdc, 0, 0, windowWidth, windowHeight, bufferHDC, 0, 0, SRCCOPY);
		SelectObject(bufferHDC, oldBitmap);
	}
	catch(...)
	{
		DeleteDC(bufferHDC);
		DeleteObject(bitmap);
	}
	DeleteDC(bufferHDC);
	DeleteObject(bitmap);
}
