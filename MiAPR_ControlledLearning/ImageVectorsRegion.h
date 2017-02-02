#pragma once

#include "ImageVector.h"
#include <vector>

class ImageVectorsRegion
{
public:
	//methods

	ImageVectorsRegion(COLORREF region_color);	
	ImageVector* GetCore();
	void SetCore(ImageVector* value);	
	bool IsCoreCompleted();

	void AddImageVectorToRegion(ImageVector* value);
	void ClearRegion();
	~ImageVectorsRegion();
private:
	//fields		

	COLORREF color;
	ImageVector* old_core;
	ImageVector* current_core;
	std::vector<ImageVector*> image_vector_list;
};

