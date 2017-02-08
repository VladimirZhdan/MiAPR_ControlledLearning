#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"
#include "DialogManager.h"
#include "DrawingLogic.h"
#include <vector>
#include "ImageVector.h"
#include "ControlledLearningLogic.h"
#include <process.h>

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();
	void ClearData();
	void Show();
	void Hide();
	void SetInitialData(int regions_cores_count, int image_vectors_count);
private:
	//fields

	std::vector<ImageVector*> image_vector_list;
	ControlledLearningLogic* controlled_learning;
	int image_vectors_count;
	int regions_cores_count;

	//controls

	HMENU hMenu;

	//methods

	void Init();
	void DrawImageVectorList(HDC hdc);
	void PerformNextStep();
	void PerformAllSteps();

	//friends procs

	static LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);

	static unsigned __stdcall PerformAllStepsThreadFunc(void* param);
};

