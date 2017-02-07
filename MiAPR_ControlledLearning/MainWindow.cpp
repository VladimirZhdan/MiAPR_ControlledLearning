#include "stdafx.h"
#include "MainWindow.h"


MainWindow::MainWindow() : Window(MainWndProc, _T("MAINWINDOW"), _T("Контролируемое обучение"), WS_OVERLAPPEDWINDOW, 800, 600, nullptr)
{
	hMenu = LoadMenu(WindowManager::GetHInstance(), MAKEINTRESOURCE(IDC_MIAPR_CONTROLLEDLEARNING));
	SetMenu(hWnd, hMenu);
	Init();
}


MainWindow::~MainWindow()
{
	for (int i = image_vector_list.size() - 1; i >= 0; --i)
	{
		delete(image_vector_list[i]);
		image_vector_list.pop_back();
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

void MainWindow::Init()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	image_vector_list = DrawingLogic::GenerateRandomImageVectorList(4000, 800, 600);	

	vector<ImageVector*> core_list;
	
	POINT point1;
	point1.x = 100;
	point1.y = 100;

	ImageVector* new_core1 = new ImageVector(point1);

	core_list.push_back(new_core1);

	POINT point2;
	point2.x = 500;
	point2.y = 400;

	ImageVector* new_core2 = new ImageVector(point2);

	core_list.push_back(new_core2);


	POINT point3;
	point3.x = 700;
	point3.y = 100;

	ImageVector* new_core3 = new ImageVector(point3);

	core_list.push_back(new_core3);

	controlled_learning = new ControlledLearningLogic(core_list, &image_vector_list);	
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
	InvalidateRect(hWnd, NULL, TRUE);
}

void MainWindow::PerformAllSteps()
{		
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
		case IDM_DEFINECORES:
			// Установить статус начала выполнения
			break;
		case IDM_NEXTSTEP:
			mainWindow->PerformNextStep();
			break;
		case IDM_PERFORM_ALLSTEPS:
			mainWindow->PerformAllSteps();
			break;
		case IDM_ABOUT:
			DialogManager::GetInstance()->ShowDialog(DIALOG_TYPE::ABOUT, hWnd);
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

