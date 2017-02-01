#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"
#include "DialogManager.h"
#include "DrawingLogic.h"
#include <vector>
#include "ImageVector.h"

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();
	void Show();
	void Hide();
private:
	//fields

	std::vector<ImageVector*> image_vector_list;

	//controls

	HMENU hMenu;

	//methods

	void Init();
	void DrawImageVectorList(HDC hdc);

	//friends procs

	static LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
};

