#pragma once


class ImageVector
{
public:
	ImageVector(POINT center, COLORREF color);
	~ImageVector();
	POINT GetCoordinate();
	void ChangeColor(COLORREF color);
	void Draw(HDC hdc);		
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

