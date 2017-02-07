#pragma once

#include <time.h>
#include <cmath>

#include <string>
#include <iostream>
#include <locale>
#include <vector>
#include <algorithm>

class ImageVector
{
public:
	ImageVector(POINT center, COLORREF color);
	~ImageVector();
	POINT GetCoordinate();
	void SetCoordinate(POINT value);
	void ChangeColor(COLORREF color);
	void Draw(HDC hdc);
	static ImageVector* GetRandomImageVector(int max_x, int max_y);
	static COLORREF GetRandomColor();
	bool CompareTo(ImageVector* obj);
	double DistanceTo(ImageVector *obj);
	double SquaredDistanceTo(ImageVector *obj);

private:
	//fields

	POINT coordinate;
	POINT start;
	POINT end;
	HPEN hPen;
	HBRUSH hBrush;

	//methods

	void DeleteColorObjects();
};

