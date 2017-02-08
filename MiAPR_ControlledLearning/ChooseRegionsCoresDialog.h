#pragma once

#include "Dialog.h"
#include "resource.h"
#include <CommCtrl.h>

class ChooseRegionsCoresDialog : public Dialog
{
public:
	ChooseRegionsCoresDialog(HWND hWndParent);
	~ChooseRegionsCoresDialog();
private:
	static INT_PTR CALLBACK ChooseRegionsCoresProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

