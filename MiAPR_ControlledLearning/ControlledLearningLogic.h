#pragma once

#include "ImageVectorsRegion.h"
#include "ImageVector.h"
#include <vector>
#include <cmath>

class ControlledLearningLogic
{
public:
	ControlledLearningLogic(std::vector<ImageVector*> core_list, std::vector<ImageVector*> image_vector_list);
	void Init(std::vector<ImageVector*> core_list);
	void PerformNextStepPackingRegions();
	bool IsDefineRegionsCompleted();
	~ControlledLearningLogic();
private:
	//fields

	std::vector<ImageVector*> image_vector_list;
	std::vector<ImageVectorsRegion*> region_list;	
	bool is_define_regions_completed;

	//methods
	void DefineRegions();
	double FindDistance(ImageVector* start, ImageVector* end);
};

