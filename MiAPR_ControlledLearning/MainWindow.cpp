#include "stdafx.h"
#include "MainWindow.h"


MainWindow::MainWindow() : Window(MainWndProc, _T("MAINWINDOW"), _T("Контролируемое обучение"), WS_OVERLAPPEDWINDOW, 800, 600, nullptr)
{
	hMenu = LoadMenu(WindowManager::GetHInstance(), MAKEINTRESOURCE(IDC_MIAPR_CONTROLLEDLEARNING));
	SetMenu(hWnd, hMenu);
	regions_cores_count = 10;
	image_vectors_count = 10000;
	Init();
}


MainWindow::~MainWindow()
{
	ClearData();
}

void MainWindow::ClearData()
{
	for (int i = image_vector_list.size() - 1; i >= 0; --i)
	{
		delete(image_vector_list[i]);
		image_vector_list.pop_back();
	}

	if (controlled_learning != nullptr)
	{
		delete(controlled_learning);
		controlled_learning = nullptr;
	}
}

void MainWindow::Show()
{
	Window::Show();
}

void MainWindow::Hide()
{
	Window::Hide();
}

void MainWindow::SetInitialData(int regions_cores_count, int image_vectors_count)
{
	this->regions_cores_count = regions_cores_count;
	this->image_vectors_count = image_vectors_count;
	Init();
}

void MainWindow::Init()
{
	ClearData();

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	long height = 800;
	long width = 600;

	image_vector_list = DrawingLogic::GenerateRandomImageVectorList(image_vectors_count, height, width);

	vector<ImageVector*> core_list;
	
	for (int i = 0; i < regions_cores_count; ++i)
	{
		ImageVector* temp_vector = ImageVector::GetRandomImageVector(height, width);
		core_list.push_back(temp_vector);
	}	

	controlled_learning = new ControlledLearningLogic(core_list, &image_vector_list);

	InvalidateRect(hWnd, NULL, FALSE);
}

void MainWindow::DrawImageVectorList(HDC hdc)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	DrawingLogic::Drawing(hdc, clientRect, controlled_learning);
}

void MainWindow::PerformNextStep()
{
	controlled_learning->PerformNextStepPackingRegions();
	InvalidateRect(hWnd, NULL, FALSE);
}

void MainWindow::PerformAllSteps()
{		
	EnableMenuItem(hMenu, IDM_DEFINECORES, MF_DISABLED);
	EnableMenuItem(hMenu, IDM_NEXTSTEP, MF_DISABLED);
	EnableMenuItem(hMenu, IDM_PERFORM_ALLSTEPS, MF_DISABLED);
	
	unsigned int hWaitingUninstallProgramThread = _beginthreadex(NULL, 0, PerformAllStepsThreadFunc, this, 0, NULL);
}

unsigned __stdcall MainWindow::PerformAllStepsThreadFunc(void* param)
{
	MainWindow *thisWindow = (MainWindow*)param;
	ControlledLearningLogic* controlled_learning = thisWindow->controlled_learning;

	while (!controlled_learning->IsFormRegionsCompleted())
	{
		thisWindow->PerformNextStep();
	}

	MessageBox(thisWindow->hWnd, _T("Completed"), _T("Information"), MB_OK);

	EnableMenuItem(thisWindow->hMenu, IDM_DEFINECORES, MF_ENABLED);
	EnableMenuItem(thisWindow->hMenu, IDM_NEXTSTEP, MF_ENABLED);
	EnableMenuItem(thisWindow->hMenu, IDM_PERFORM_ALLSTEPS, MF_ENABLED);

	return 0;
}


static MainWindow *mainWindow = (MainWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::MAIN));

LRESULT CALLBACK MainWindow::MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 800;
		lpMMI->ptMinTrackSize.y = 600;
		lpMMI->ptMaxTrackSize.x = 800;
		lpMMI->ptMaxTrackSize.y = 600;
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{		
		case IDM_NEXTSTEP:
			mainWindow->PerformNextStep();
			break;
		case IDM_PERFORM_ALLSTEPS:
			mainWindow->PerformAllSteps();
			break;
		case IDM_ABOUT:			
			DialogManager::GetInstance()->ShowDialog(DIALOG_TYPE::ABOUT, hWnd);
			break;
		case IDM_DEFINECORES:
			DialogManager::GetInstance()->ShowDialog(DIALOG_TYPE::CHOOSECORES, hWnd);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{		
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...

		mainWindow->DrawImageVectorList(hdc);						

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

