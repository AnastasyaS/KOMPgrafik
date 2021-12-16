#include"Prism.h"
#include"piramida.h"
#include "Floor.h"

Pyramid* pyramid = new Pyramid();
Prism* prism = new Prism();
Floor* FLoor = new Floor();
int rectRight = 0, rectLeft = 0, rectUp = 0, rectDown = 0;

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int mCmdShow) {// входа
	MSG msg{}; //сообщения
	HWND hwnd{}; //дескриптор
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(COLOR_INACTIVECAPTION));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
		HDC hdc, hCmpDC;
		PAINTSTRUCT ps;
		HBITMAP hBmp;
		RECT Rect{};
		switch (uMsg) {
		case WM_PAINT:
		{//буфер кадра
			GetClientRect(hWnd, &Rect);
			rectRight = Rect.right, rectLeft = Rect.left, rectUp = Rect.top, rectDown = Rect.bottom;
			hdc = BeginPaint(hWnd, &ps);
			hCmpDC = CreateCompatibleDC(hdc);//для двойной буферизации
			hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left, Rect.bottom - Rect.top);
			SelectObject(hCmpDC, hBmp);
			LOGBRUSH br;//закраска фона
			br.lbStyle = BS_SOLID;
			br.lbColor = 0x00aaff;
			HBRUSH brush;
			brush = CreateBrushIndirect(&br);
			FillRect(hCmpDC, &Rect, brush);
			SelectObject(hdc, brush);
			FLoor->Draw(hCmpDC, Rect, *pyramid, *prism);
			pyramid->DrawShadow(hCmpDC, Rect);
			pyramid->Draw(hCmpDC);
			prism->DrawShadow(hCmpDC, Rect);
			prism->Draw(hCmpDC);
			DeleteObject(brush);
			SetStretchBltMode(hdc, COLORONCOLOR);
			BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, hCmpDC, 0, 0, SRCCOPY);
			DeleteDC(hCmpDC);
			DeleteObject(hBmp);
			hCmpDC = NULL;
			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_KEYDOWN:
		{
			switch (wParam) {
			case VK_RIGHT:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					if (prism->GetPrism()[0][0] > rectRight - 10 || prism->GetPrism()[1][0] > rectRight - 10 || prism->GetPrism()[2][0] > rectRight - 10 ||
						prism->GetPrism()[3][0] > rectRight - 10 || prism->GetPrism()[4][0] > rectRight - 10 || prism->GetPrism()[5][0] > rectRight - 10) {
						return 0;
					}
					prism->moveRight(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					if (pyramid->GetPyramid()[0][0] > rectRight - 10 || pyramid->GetPyramid()[1][0] > rectRight - 10 || pyramid->GetPyramid()[2][0] > rectRight - 10 ||
						pyramid->GetPyramid()[3][0] > rectRight - 10 || pyramid->GetPyramid()[4][0] > rectRight - 10) {
						return 0;
					}
					pyramid->moveRight(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;
			
			case VK_LEFT:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					if (prism->GetPrism()[0][0] < rectLeft + 10 || prism->GetPrism()[1][0] < rectLeft + 10 || prism->GetPrism()[2][0] < rectLeft + 10 ||
						prism->GetPrism()[3][0] < rectLeft + 10 || prism->GetPrism()[4][0] < rectLeft + 10 || prism->GetPrism()[5][0] < rectLeft + 10) {
						return 0;
					}
					prism->moveLeft(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					if (pyramid->GetPyramid()[0][0] < rectLeft + 10 || pyramid->GetPyramid()[1][0] < rectLeft + 10 || pyramid->GetPyramid()[2][0] < rectLeft + 10 ||
						pyramid->GetPyramid()[3][0] < rectLeft + 10 || pyramid->GetPyramid()[4][0] < rectLeft + 10) {
						return 0;
					}
					pyramid->moveLeft(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;

			case VK_UP:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					if (prism->GetPrism()[0][1] < rectUp + 10 || prism->GetPrism()[1][1] < rectUp + 10 || prism->GetPrism()[2][1] < rectUp + 10 ||
						prism->GetPrism()[3][1] < rectUp + 10 || prism->GetPrism()[4][1] < rectUp + 10 || prism->GetPrism()[5][1] < rectUp + 10) {
						return 0;
					}
					prism->moveUp(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					if (pyramid->GetPyramid()[0][1] < rectUp + 10 || pyramid->GetPyramid()[1][1] < rectUp + 10 || pyramid->GetPyramid()[2][1] < rectUp + 10 ||
						pyramid->GetPyramid()[3][1] < rectUp + 10 || pyramid->GetPyramid()[4][1] < rectUp + 10) {
						return 0;
					}
					pyramid->moveUp(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;

			case VK_DOWN:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					if (prism->GetPrism()[0][1] > rectDown - 10 || prism->GetPrism()[1][1] > rectDown - 10 || prism->GetPrism()[2][1] > rectDown - 10 ||
						prism->GetPrism()[3][1] > rectDown - 10 || prism->GetPrism()[4][1] > rectDown - 10 || prism->GetPrism()[5][1] > rectDown - 10 ||
						prism->CheckShadowOverlay()) {
						return 0;
					}
					prism->moveDown(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					if (pyramid->GetPyramid()[0][1] > rectDown - 10 || pyramid->GetPyramid()[1][1] > rectDown - 10 || pyramid->GetPyramid()[2][1] > rectDown - 10 ||
						pyramid->GetPyramid()[3][1] > rectDown - 10 || pyramid->GetPyramid()[4][1] > rectDown - 10 || pyramid->CheckShadowOverlay()) {
						return 0;
					}
					pyramid->moveDown(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;

			case int('X'):
			{{
					if (GetAsyncKeyState(VK_CONTROL)) {
						if (prism->CheckShadowOverlay()) {
							return 0;
						}
						prism->turnX(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						if (pyramid->CheckShadowOverlay()) {
							return 0;
						}
						pyramid->turnX(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('Y'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						if (prism->CheckShadowOverlay()) {
							return 0;
						}
						prism->turnY(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						if (pyramid->CheckShadowOverlay()) {
							return 0;
						}
						pyramid->turnY(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('Z'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						if (prism->CheckShadowOverlay()) {
							return 0;
						}
						prism->turnZ(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						if (pyramid->CheckShadowOverlay()) {
							return 0;
						}
						pyramid->turnZ(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('W'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						if (prism->CheckShadowOverlay()) {
							return 0;
						}
						prism->scale(1.15, 1.15, 1.15);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						if (pyramid->CheckShadowOverlay()) {
							return 0;
						}
						pyramid->scale(1.15, 1.15, 1.15);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('S'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						prism->scale(0.85, 0.85, 0.85);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						pyramid->scale(0.85, 0.85, 0.85);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;
			}}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	//if'ы на обработку сообщений
	{if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	if (hwnd = CreateWindow(wc.lpszClassName, L"Компьютерная графика КР", WS_OVERLAPPEDWINDOW, 0, 0, 1400, 800, nullptr, nullptr, wc.hInstance, nullptr), hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE; }
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hwnd);
	//цикл обработки сообщений
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//возврат точки входа
	return static_cast<int>(msg.wParam);
}
