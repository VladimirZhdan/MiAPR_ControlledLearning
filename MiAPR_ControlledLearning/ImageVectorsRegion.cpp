#include "stdafx.h"
#include "ImageVectorsRegion.h"


ImageVectorsRegion::ImageVectorsRegion(COLORREF region_color)
{
	this->color = region_color;
	this->old_core = nullptr;
	this->current_core = nullptr;
}

void ImageVectorsRegion::SetCore(ImageVector * value)
{
	value->ChangeColor(RGB(0, 0, 0));
	old_core = current_core;
	current_core = value;		
}

ImageVector * ImageVectorsRegion::GetCore()
{
	return current_core;
}

bool ImageVectorsRegion::IsCoreCompleted()
{
	if (current_core != nullptr)
	{
		return current_core->CompareTo(old_core);
	}
	else
	{
		return false;
	}
}

void ImageVectorsRegion::AddImageVectorToRegion(ImageVector * value)
{
	value->ChangeColor(color);
	image_vector_list.push_back(value);
}

void ImageVectorsRegion::ClearRegion()
{
	image_vector_list.clear();
}


ImageVectorsRegion::~ImageVectorsRegion()
{
	image_vector_list.clear();
}
