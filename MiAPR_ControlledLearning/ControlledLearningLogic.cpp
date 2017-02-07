#include "stdafx.h"
#include "ControlledLearningLogic.h"

ControlledLearningLogic::ControlledLearningLogic(std::vector<ImageVector*> core_list, std::vector<ImageVector*>* image_vector_list)
{
	this->image_vector_list = image_vector_list;
	Init(core_list);
	is_form_regions_completed = false;

	for (ImageVector* core : core_list)
	{
		image_vector_list->push_back(core);
	}
}

void ControlledLearningLogic::Init(std::vector<ImageVector*> core_list)
{
	for(ImageVector* core : core_list)
	{
		ImageVectorsRegion *new_region = new ImageVectorsRegion(ImageVector::GetRandomColor());
		new_region->SetCore(core);
		region_list.push_back(new_region);
	}
	DefineRegions();
}

void ControlledLearningLogic::PerformNextStepPackingRegions()
{	
	long sync_variable = region_list.size();

	for (ImageVectorsRegion* region : region_list)
	{
		region->DefineRegionCore(&sync_variable);
	}

	while (InterlockedCompareExchange(&sync_variable, 1, 0) != 0)
	{
		Sleep(10);
		//Yield();
	}

	DefineRegions();	
	DefineIsFormRegionsCompleted();
}

bool ControlledLearningLogic::IsFormRegionsCompleted()
{
	return is_form_regions_completed;
}

void ControlledLearningLogic::DrawRegions(HDC hdc)
{
	for (ImageVectorsRegion* region : region_list)
	{
		region->Draw(hdc);
	}
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
	for (ImageVector* image_vector : *image_vector_list)
	{		
		if (region_list.size() > 0)		
		{
			choosen_region = region_list[0];
			min_distance = image_vector->DistanceTo(region_list[0]->GetCore());				

			for (int i = 1; i < region_list.size(); ++i)
			{
				current_distance = image_vector->DistanceTo(region_list[i]->GetCore());				
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

void ControlledLearningLogic::DefineIsFormRegionsCompleted()
{
	bool is_completed = true;

	for (ImageVectorsRegion* region : region_list)
	{
		is_completed &= region->IsCoreCompleted();
	}

	is_form_regions_completed = is_completed;
}