#include "stdafx.h"
#include "ControlledLearningLogic.h"

ControlledLearningLogic::ControlledLearningLogic(std::vector<ImageVector*> core_list, std::vector<ImageVector*> image_vector_list)
{
	this->image_vector_list = image_vector_list;
	Init(core_list);
	is_define_regions_completed = false;
}

void ControlledLearningLogic::Init(std::vector<ImageVector*> core_list)
{
	for(ImageVector* core : core_list)
	{
		ImageVectorsRegion *new_region = new ImageVectorsRegion(ImageVector::GetRandomColor());
		new_region->SetCore(core);
		region_list.push_back(new_region);
	}
}

void ControlledLearningLogic::PerformNextStepPackingRegions()
{
	DefineRegions();
}

bool ControlledLearningLogic::IsDefineRegionsCompleted()
{
	return is_define_regions_completed;
}

ControlledLearningLogic::~ControlledLearningLogic()
{
}

void ControlledLearningLogic::DefineRegions()
{
	for (ImageVectorsRegion* region : region_list)
	{
		region->ClearRegion();
	}
	
	double min_distance;
	double current_distance;
	ImageVectorsRegion* choosen_region;
	for (ImageVector* image_vector : image_vector_list)
	{		
		if (region_list.size() > 0)		
		{
			choosen_region = region_list[0];
			min_distance = FindDistance(image_vector, region_list[0]->GetCore());

			for (int i = 1; i < region_list.size(); ++i)
			{
				current_distance = FindDistance(image_vector, region_list[i]->GetCore());
				if (current_distance < min_distance)
				{
					min_distance = current_distance;
					choosen_region = region_list[i];
				}
			}

			choosen_region->AddImageVectorToRegion(image_vector);
		}		
	}
}

double ControlledLearningLogic::FindDistance(ImageVector * start, ImageVector * end)
{
	POINT start_point = start->GetCoordinate();
	POINT end_point = end->GetCoordinate();

	double result_distance = 0;
	result_distance += pow(end_point.x - start_point.x, 2);
	result_distance += pow(end_point.y - start_point.y, 2);
	result_distance = pow(result_distance, 0.5);

	return result_distance;
}
