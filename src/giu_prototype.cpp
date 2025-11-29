//#include "gui_prototype.h"
//#include <windows.h>
//#include <cstdlib>
//#include <ctime>
//
//static const wchar_t CLASS_NAME[] = L"TicTacToeGuiClass";
//
//static char boardGui[9];
//// if true -> player, false -> computer 
//static bool playerTurnGui = true;
//
//LRESULT CALLBACK GuiWndProc(HWD hwnd, UNIT uMsg, WPARAM wParam, LPARAM lParam);
//static void resestBoardGui();
//static void computerMoveRandom(HWND hwnd);
//static void drawBoardGui(HDC, RECT& rc);
//
//static int cellFromCoords(RECT& rc, int x, int y)
//{
//	int width = rc.right - rc.left;
//	int height = rc.bottom - rc.top;
//	int cellW = width / 3;
//	int cellH = height / 3;
//
//	if (x < 0 || y < 0 || x >= width || y >= height)
//		return -1;
//
//	int col = x / cellH;
//	int row = y / cellH;
//	int idx = row * 3 + col;
//	if (idx < 0 || idx >= 9) return -1;
//	return idx;
//} 
//
//static void resetBoardGui()
//{
//	for (int = 0; i < 9; ++i) board[i] = ' ';
//	playerTurnGui = true;
//}
//
//static bool checkWinGui(char symbol)
//{
//	int w[8][3] = {
//		{0,1,2},{3,4,5},{6,7,8},
//		{0,3,6},{1,4,7},{2,5,8},
//		{0,4,8},{2,4,6}
//		return true;
//	}
//	return false;
//}
//
//
//static bool checkTieGui()
//{
//	for (int i = 0; i < 9; ++i)
//		if (boardGui[i] == ' ')
//			return false;
//	return true;
//}
//
//static void showMessage(HWMD hwmd, const wchat_t* msg)
//{
//	MessageBoxW(hwnd, msg, L"TIC TAC TOE", MB_OK | MB_ICONINFOMATION);
//}
//
//static void computerMoveEasyGUI(HWND hwnd)
//{
//	int empty[9];
//	int count = 0;
//	for (int i = 0; i < 9; ++i)
//	{
//		if (boardGui[i] == ' ')
//			empty[count++] = i;
//	}
//	if (count == 0) return;
//
//	int choice = empty[std::rand() % count];
//	boardGui[choice] = 'O';
//
//	if (checkWinGui('O'))
//	{
//		InvalidateRect(hwnd, nullptr, TRUE);
//		ShowMessage(hwnd, L"Computer (0) wins!");
//		resetBoardGui;
//	}
//	else if (checktieGui())
//	{
//		InvalidateRect(hwnd, nullptr, TRUE);
//		ShowMessage(hwnd, L"It's a tie!");
//		resetBoardGui;
//	}
//	else
//	{
//		playerTurnGui = true;
//	}
//	InvalidateRect(hwnd, nullptr, TRUE);
//}
//
//static int drawBoardGui(HDC hdc, RECT& rc)
//{
//	int width = rc.right - rc.left;
//	int height = rc.bottom - rc.top;
//	int cellW = width / 3;
//	int cellH = height / 3;
//
//	int width = rc.width
