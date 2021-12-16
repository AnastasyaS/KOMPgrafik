#include "Floor.h"

Floor::Floor() {
	floor = new double* [4];
	for (int i = 0; i < 4; i++) {
		floor[i] = new double[4];
	}
}

void Floor::Draw(HDC hdc, RECT rect, Pyramid pyramid, Prism prism) {
	//               x				      y				       z
	floor[0][0] = rect.left, floor[0][1] = rect.bottom - 550, floor[0][2] = 500, floor[0][3] = 1;//лево верх
	floor[1][0] = rect.left, floor[1][1] = rect.bottom, floor[1][2] = 0, floor[1][3] = 1;//лево низ
	floor[2][0] = rect.right, floor[2][1] = rect.bottom, floor[2][2] = 0, floor[2][3] = 1;//право низ
	floor[3][0] = rect.right, floor[3][1] = rect.bottom - 550, floor[3][2] = 500, floor[3][3] = 1;//право верх

	POINT kv[4] = { {floor[0][0],floor[0][1]},
				{floor[1][0],floor[1][1] },
				{floor[2][0],floor[2][1] },
				{floor[3][0],floor[3][1] } };

	HBRUSH brush;
	brush = CreateSolidBrush(0xf536e2);
	SelectObject(hdc, brush);
	Polygon(hdc, kv, 4);// отрисовка пола
	DeleteObject(brush);

	double x1 = floor[0][0], y1 = floor[0][1] + 450, z1 = floor[0][2],
		x2 = floor[1][0], y2 = floor[1][1], z2 = floor[1][2],
		x3 = floor[2][0], y3 = floor[2][1], z3 = floor[2][2];

	eq[0] = ((y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - z1)) / 100;;
	eq[1] = ((x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1)) / 100;
	eq[2] = ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 100;
	eq[3] = ((eq[0] * x1 + eq[1] * y1 + eq[2] * z1)) / 100;
}

void Floor::turnX(double alpha) {

}

Floor::~Floor() {
	for (int i = 0; i < 4; i++) {
		delete[] this->floor[i];
	}
	delete[] this->floor;
}
