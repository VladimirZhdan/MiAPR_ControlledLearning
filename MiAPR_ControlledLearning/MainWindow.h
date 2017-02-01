#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"
#include "DialogManager.h"

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();
	void Show();
	void Hide();
private:
	//fields

	HMENU hMenu;

	//controls


	//methods

	void Init();

	//friends procs

	static LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
};
