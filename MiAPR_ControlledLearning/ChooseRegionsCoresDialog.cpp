#include "stdafx.h"
#include "ChooseRegionsCoresDialog.h"


ChooseRegionsCoresDialog::ChooseRegionsCoresDialog(HWND hWndParent) : Dialog(ChooseRegionsCoresProc, IDD_CHOOSECORES, hWndParent)
{

}


ChooseRegionsCoresDialog::~ChooseRegionsCoresDialog()
{

}

INT_PTR ChooseRegionsCoresDialog::ChooseRegionsCoresProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hTrach_cores_count;
	static int cores_count = 1;
	static HWND hTrach_vectors_count;
	static int vectors_count = 1000;
	int wmId;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		//CORES_COUNT
		hTrach_cores_count = GetDlgItem(hDlg, IDC_SLIDER_CORESCOUNT);
		SetDlgItemInt(hDlg, IDC_STATIC_CORESCOUNT, cores_count, 0);
		SendMessage(hTrach_cores_count, TBM_SETRANGEMIN, 0, 1);
		SendMessage(hTrach_cores_count, TBM_SETRANGEMAX, 0, 10);
		SendMessage(hTrach_cores_count, TBM_SETPOS, TRUE, cores_count);
		//VECTORS_COUNT
		hTrach_vectors_count = GetDlgItem(hDlg, IDC_SLIDER_VECTORSCOUNT);
		SetDlgItemInt(hDlg, IDC_STATIC_VECTORSCOUNT, vectors_count, 0);
		SendMessage(hTrach_vectors_count, TBM_SETRANGEMIN, 0, 1000);
		SendMessage(hTrach_vectors_count, TBM_SETRANGEMAX, 0, 15000);
		SendMessage(hTrach_vectors_count, TBM_SETPOS, TRUE, vectors_count);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			WindowManager::GetInstance()->SetInitialData(cores_count, vectors_count);
			EndDialog(hDlg, LOWORD(wParam));			
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
		return (INT_PTR)TRUE;
		break;
	case WM_HSCROLL:
		//CORES_COUNT
		cores_count = LOWORD(SendMessage(hTrach_cores_count, TBM_GETPOS, 0, 0));
		SetDlgItemInt(hDlg, IDC_STATIC_CORESCOUNT, cores_count, 0);
		//VECTORS_COUNT
		vectors_count = LOWORD(SendMessage(hTrach_vectors_count, TBM_GETPOS, 0, 0));
		SetDlgItemInt(hDlg, IDC_STATIC_VECTORSCOUNT, vectors_count, 0);

		InvalidateRect(hDlg, NULL, TRUE);
		break;
	}
	return (INT_PTR)FALSE;
}
