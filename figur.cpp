#include "figur.h"
                          
double res[4][10] = {};
double e[4] = { 0, 0, 1, 0 };
double eq[4];

double Figure::product(double Px, double Py, double Ax, double Ay, double Bx, double By){
	return (Bx - Ax) * (Py - Ay) - (By - Ay) * (Px - Ax);
}

double* Figure::findCentre(double** mas, int n, int m) {
	double* centre = new double[3];
	for (int i = 0; i < m; i++) {
		centre[i] = 0;
		for (int j = 0; j < n; j++) {
			centre[i] += mas[j][i];
		}
		centre[i] = centre[i] / n;
	}
	return centre;
}

double** Figure::mm(double** masA, double** masB, int n1, int m1, int n2, int m2) {
	int max = m1;
	if (n1 > m1) max = n1;
	if (n2 > m1) max = n2;
	if (m2 > m1) max = m1;
	double** mulRes = new double* [max];
	for (int i = 0; i < max; i++)
	{
		mulRes[i] = new double[max];
	}

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			mulRes[i][j] = 0;
			for (int k = 0; k < m1; k++) {
				mulRes[i][j] += (masA[i][k] * masB[k][j]);
			}
		}
	}

	for (int i = 0; i < m1; i++) {
		delete[] masA[i];
	}
	delete[] masA;
	return mulRes;
}

void Figure::ContourDraw(HDC hdc, POINT* p, int n) {
	MoveToEx(hdc, p[0].x, p[0].y, NULL);
	for (int i = 0; i < n; i++) {
		LineTo(hdc, p[i].x, p[i].y);
	}
	LineTo(hdc, p[0].x, p[0].y);
}

double Figure::fill(HDC hdc, double x, double y, double x0) {
	double xleft;
	while (GetPixel(hdc, x - 1, y) != 0) {
		SetPixel(hdc, x, y, 0x0000FF00);
		x--;
	}
	xleft = x;
	x = x0 + 1;
	while (GetPixel(hdc, x, y) != 0) {
		SetPixel(hdc, x, y, 0x0000FF00);
		x++;
	}
	return xleft;
}

void Figure::Hatching(HDC hdc, POINT* p, int n) {
	POINT dot{};
	for (int i = 0; i < n; i++) {
		dot.x += p[i].x;
		dot.y += p[i].y;
	}
	dot.x /= n; dot.y /= n;
	stack<POINT>stk;
	stk.push(dot);
	double x = dot.x, y = dot.y;
	while (!stk.empty()) {
		x = stk.top().x, y = stk.top().y;
		double prod1 = product(x, y, p[0].x, p[0].y, p[1].x, p[1].y);
		double prod2 = product(x, y, p[1].x, p[1].y, p[2].x, p[2].y);;
		double prod3 = product(x, y, p[2].x, p[2].y, p[0].x, p[0].y);;
		double prod4 = 0;
		if (n == 4) {
		prod3 = product(x, y, p[2].x, p[2].y, p[3].x, p[3].y);
		prod4 = product(x, y, p[3].x, p[3].y, p[0].x, p[0].y);
		}
		if (prod1 < 0 || prod2 < 0 || prod3 < 0 || prod4 < 0) {
			if (!(prod1 < 0 && prod2 < 0 && prod3 < 0 && prod4 <= 0)) {
				break;
			}
		}
		stk.pop();

		if (GetPixel(hdc, x - 1, y) != 0 && GetPixel(hdc, x - 1, y) != 65280) {//точка слева
			SetPixel(hdc, x - 1, y, 0x0000FF00);
			dot.x = x - 1;
			dot.y = y;
			stk.push(dot);
		}

		if (GetPixel(hdc, x + 1, y) != 0 && GetPixel(hdc, x + 1, y) != 65280) {//точка справа
			SetPixel(hdc, x + 1, y, 0x0000FF00);
			dot.x = x + 1;
			dot.y = y;
			stk.push(dot);
		}

		if (GetPixel(hdc, x, y - 1) != 0 && GetPixel(hdc, x, y - 1) != 65280) {//точка сверху
			SetPixel(hdc, x, y - 1, 0x0000FF00);
			dot.x = x;
			dot.y = y - 1;
			stk.push(dot);
		}

		if (GetPixel(hdc, x, y + 1) != 0 && GetPixel(hdc, x, y + 1) != 65280) {//точка снизу
			SetPixel(hdc, x, y + 1, 0x0000FF00);
			dot.x = x;
			dot.y = y + 1;
			stk.push(dot);
		}
	}
}

void Figure::equationPlane(int numPlane, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
	res[0][numPlane] = ((y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - z1)) / 100;
	res[1][numPlane] = ((x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1)) / 100;
	res[2][numPlane] = ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 100;
	res[3][numPlane] = ((res[0][numPlane] * x1 + res[1][numPlane] * y1 + res[2][numPlane] * z1)) / 100;
}
