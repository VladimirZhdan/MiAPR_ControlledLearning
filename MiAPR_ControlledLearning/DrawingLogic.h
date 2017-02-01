#pragma once

#include <vector>
#include "ImageVector.h"

using namespace std;

class DrawingLogic
{
public:
	DrawingLogic();
	~DrawingLogic();
	static void Drawing(HDC hdc, RECT clientRect, vector<ImageVector*> image_vector_list);
};

