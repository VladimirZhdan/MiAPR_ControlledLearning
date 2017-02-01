#include "stdafx.h"
#include "ImageVector.h"


ImageVector::ImageVector(POINT coordinate, COLORREF color)
{
	this->coordinate = coordinate;
	this->hPen = CreatePen(PS_SOLID, 1, color);
	this->hBrush = CreateSolidBrush(color);
	this->start.x = coordinate.x - 2;
	this->start.y = coordinate.y - 2;
	this->end.x = coordinate.x + 2;
	this->end.y = coordinate.y + 2;
}


ImageVector::~ImageVector()
{
	DeleteColorObjects();
}

POINT ImageVector::GetCoordinate()
{
	return this->coordinate;
}

void ImageVector::ChangeColor(COLORREF color)
{
	DeleteColorObjects();
	hPen = CreatePen(PS_SOLID, 1, color);
	hBrush = CreateSolidBrush(color);
}

void ImageVector::Draw(HDC hdc)
{
	HGDIOBJ prevPen = SelectObject(hdc, hPen);
	HGDIOBJ prevBrush = SelectObject(hdc, hBrush);
	Ellipse(hdc, start.x, start.y, end.x, end.y);	
	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}

void ImageVector::DeleteColorObjects()
{
	if (hPen != NULL)				
	{
		DeleteObject(hPen);
	}
	if (hBrush != NULL)
	{
		DeleteObject(hBrush);
	}
	hPen = NULL;
	hBrush = NULL;
}
