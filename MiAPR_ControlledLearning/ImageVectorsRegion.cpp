#include "stdafx.h"
#include "ImageVectorsRegion.h"


ImageVectorsRegion::ImageVectorsRegion(COLORREF region_color)
{
	this->color = region_color;
	this->old_core = nullptr;
	this->current_core = nullptr;
	this->is_core_completed = false;
}

void ImageVectorsRegion::SetCore(ImageVector * value)
{
	if (value == current_core || value == old_core)
	{
		is_core_completed = true;
	}
	else
	{
		is_core_completed = false;
	}
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
	return is_core_completed;
}

void ImageVectorsRegion::AddImageVectorToRegion(ImageVector * value)
{
	if (value != current_core)
	{
		value->ChangeColor(color);
		image_vector_list.push_back(value);
	}	
}

void ImageVectorsRegion::ClearRegion()
{
	image_vector_list.clear();
}


void ImageVectorsRegion::FindAndDefineRegionCore()
{
	int index_min_squared_distance_sum = 0;
	double min_squared_distance_sum = DBL_MAX;

	for (int i = 0; i < image_vector_list.size(); ++i)
	{
		ImageVector* current_image_vector = image_vector_list[i];
		double current_squared_distance_sum = 0;
		for (int j = 0; j < image_vector_list.size(); ++j)
		{
			current_squared_distance_sum += current_image_vector->SquaredDistanceTo(image_vector_list[j]);
		}

		if (current_squared_distance_sum < min_squared_distance_sum)
		{
			index_min_squared_distance_sum = i;
			min_squared_distance_sum = current_squared_distance_sum;
		}
	}

	SetCore(image_vector_list[index_min_squared_distance_sum]);
}

ImageVectorsRegion::~ImageVectorsRegion()
{
	image_vector_list.clear();
}
