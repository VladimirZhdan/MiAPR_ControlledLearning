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

void ImageVector::SetCoordinate(POINT value)
{
	this->coordinate = value;
	this->start.x = coordinate.x - 2;
	this->start.y = coordinate.y - 2;
	this->end.x = coordinate.x + 2;
	this->end.y = coordinate.y + 2;
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

ImageVector * ImageVector::GetRandomImageVector(int max_x, int max_y)
{		
	POINT coordinate;	
	coordinate.x = rand() % (max_x + 1);
	coordinate.y = rand() % (max_y + 1);	

	COLORREF color = GetRandomColor();

	ImageVector* result = new ImageVector(coordinate, color);

	return result;
}

COLORREF ImageVector::GetRandomColor()
{
	BYTE color_r{ BYTE(rand() % 256) };
	BYTE color_g{ BYTE(rand() % 256) };
	BYTE color_b{ BYTE(rand() % 256) };

	return RGB(color_r, color_g, color_b);
}

bool ImageVector::CompareTo(ImageVector * obj)
{
	if (obj == nullptr)
	{
		return false;
	}
	if (obj == this)
	{
		return true;
	}
	if (obj->coordinate.x != this->coordinate.x)
	{
		return false;
	}
	if (obj->coordinate.y != this->coordinate.y)
	{
		return false;
	}	
	return true;
}

double ImageVector::DistanceTo(ImageVector * obj)
{
	if (obj == nullptr)
	{
		throw std::runtime_error("Null Reference Exception of Agrument in DistanceTo method(class ImageVector)");
	}

	double result_distance = this->SquaredDistanceTo(obj);
	result_distance = pow(result_distance, 0.5);

	return result_distance;
}

double ImageVector::SquaredDistanceTo(ImageVector * obj)
{
	if (obj == nullptr)
	{
		throw std::runtime_error("Null Reference Exception of Agrument in DistanceTo method(class ImageVector)");
	}

	POINT start_point = this->GetCoordinate();
	POINT end_point = obj->GetCoordinate();

	double result_distance = 0;
	result_distance += pow(end_point.x - start_point.x, 2);
	result_distance += pow(end_point.y - start_point.y, 2);	

	return result_distance;
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
