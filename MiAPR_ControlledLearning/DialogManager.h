#pragma once

#include "Dialog.h"
#include "Window.h"
#include "WindowManager.h"

#include "AboutDialog.h"
#include "ChooseRegionsCoresDialog.h"

enum class DIALOG_TYPE
{
	ABOUT,
	CHOOSECORES
};

class DialogManager
{
public:
	DialogManager();
	~DialogManager();
	void ShowDialog(DIALOG_TYPE, HWND hWndParent);
	static DialogManager* GetInstance();
private:
	Dialog* GetDialog(DIALOG_TYPE, HWND hWndParent);
	AboutDialog *aboutDialog;
	ChooseRegionsCoresDialog* chooseDialog;

};