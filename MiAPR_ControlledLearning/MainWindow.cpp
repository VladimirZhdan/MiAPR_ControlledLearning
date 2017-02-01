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

	image_vector_list = DrawingLogic::GenerateRandomImageVectorList(1000, 800, 600);	
}

void MainWindow::DrawImageVectorList(HDC hdc)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	DrawingLogic::Drawing(hdc, clientRect, image_vector_list);
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
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
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

