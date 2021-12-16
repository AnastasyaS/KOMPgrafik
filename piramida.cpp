#include "piramida.h"

Pyramid::Pyramid() {
	pyramid = new double* [5];
	for (int i = 0; i < 5; i++) {
		pyramid[i] = new double[4];
	}
	//               x				      y				       z
	pyramid[0][0] = 150, pyramid[0][1] = 350, pyramid[0][2] = 200, pyramid[0][3] = 1;//перед
	pyramid[1][0] = 100, pyramid[1][1] = 400, pyramid[1][2] = 300, pyramid[1][3] = 1;//лево низ
	pyramid[2][0] = 100, pyramid[2][1] = 300, pyramid[2][2] = 300, pyramid[2][3] = 1;//лево верх
	pyramid[3][0] = 200, pyramid[3][1] = 300, pyramid[3][2] = 300, pyramid[3][3] = 1;//право верх
	pyramid[4][0] = 200, pyramid[4][1] = 400, pyramid[4][2] = 300, pyramid[4][3] = 1;//право низ

}

Pyramid::Pyramid(const Pyramid& copy) {
	pyramid = new double* [5];
	for (int i = 0; i < 5; i++) {
		pyramid[i] = new double[4];
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			pyramid[i][j] = copy.pyramid[i][j];
		}
	}
}

void Pyramid::Draw(HDC hdc) {
	//структуры 2d фигур пирамиды
	POINT tr1[3] = { {pyramid[0][0],pyramid[0][1]},
					{pyramid[1][0],pyramid[1][1] },//левый треугольник
					{pyramid[2][0],pyramid[2][1] } };//1
	POINT tr2[3] = { {pyramid[0][0],pyramid[0][1] },
					{pyramid[4][0],pyramid[4][1] },//правый треугольник
					{pyramid[3][0],pyramid[3][1] } };//2
	POINT kv1[4] = { {pyramid[1][0],pyramid[1][1] },
					{pyramid[2][0],pyramid[2][1] },
					{pyramid[3][0],pyramid[3][1] },//основание
					{pyramid[4][0],pyramid[4][1] } };//3
	POINT tr3[3] = { {pyramid[0][0],pyramid[0][1] },
					{pyramid[1][0],pyramid[1][1] },//нижний треугольник
					{pyramid[4][0],pyramid[4][1] } };//4
	POINT tr4[3] = { {pyramid[0][0],pyramid[0][1] },
					{pyramid[2][0],pyramid[2][1] },//верхний треугольник
					{pyramid[3][0],pyramid[3][1] } };//5

	setPlanePyr(); 
	double c[5]{}; 
	e[0] = 0, e[1] = 0, e[2] = 1, e[3] = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			c[i] += e[j] * res[j][i];
		}
		if (c[i] > 0) {
			switch (i) {
			case 0:
				ContourDraw(hdc, tr1,3);
				Hatching(hdc, tr1, 3);
				break;
			case 1:
				ContourDraw(hdc, tr2, 3);
				Hatching(hdc, tr2, 3);
				break;
			case 2:
				ContourDraw(hdc, kv1, 4);
				Hatching(hdc, kv1, 4);
				break;
			case 3:
				ContourDraw(hdc, tr3, 3);
				Hatching(hdc, tr3, 3);
				break;
			case 4:
				ContourDraw(hdc, tr4, 3);
				Hatching(hdc, tr4, 3);
				break;
			default:
				continue;
			}
		}
	}
}

void Pyramid::DrawShadow(HDC hdc, RECT rect){
	// x = pyramid[x]; y = eq[1]*t+pyramid[y]; z = eq[2]*t + pyramid[z]
// 
//		y - pyramid[y]		   z - pyramid[z]
// t =		-----------    t =  -----------
//			eq[1]					eq[2]
// 
// y = eq[1]t + ppyramid[y]   z = eq[2]t + pyramid[z]
// 
// eq[1](eq[1]*t+pyramid[y]) - eq[2](eq[2]*t + pyramid[z]) - eq[3] = 0
// 
// eq[1]*eq[1]*t+eq[1]pyramid[y] - eq[2]*eq[2]*t + eq[2]pyramid[z] - eq[3] = 0
// 
// t = (-eq[1]pyr[y]-eq[2]pyr[z]+eq[3])/(eq[1] * eq[1]- eq[2] *eq[2])
	double yshadow[5];
	for (int i = 0; i < 5; i++) {
		yshadow[i] = (-(eq[2] * (eq[2] * (((eq[1] * pyramid[i][1] + eq[2] * pyramid[i][2] + eq[3]) / (eq[1] * eq[1] - eq[2] * eq[2])) / 10)
			+ pyramid[i][2])) - eq[3]) / eq[1];
		shadow[i].x = pyramid[i][0], shadow[i].y = rect.bottom + yshadow[i];
	}
	HBRUSH brush;
	brush = CreateSolidBrush(0x00);
	SelectObject(hdc, brush);
	POINT tr1[3] = { {shadow[0].x,shadow[0].y},
					{shadow[1].x,shadow[1].y },//левый треугольник
					{shadow[2].x,shadow[2].y } };//1
	Polygon(hdc, tr1, 3);
	POINT tr2[3] = { {shadow[0].x,shadow[0].y },
					{shadow[4].x,shadow[4].y },//правый треугольник
					{shadow[3].x,shadow[3].y } };//2
	Polygon(hdc, tr2, 3);
	POINT kv1[4] = { {shadow[1].x,shadow[1].y },
					{shadow[2].x,shadow[2].y },
					{shadow[3].x,shadow[3].y },//основание
					{shadow[4].x,shadow[4].y } };//3
	Polygon(hdc, kv1, 4);
	POINT tr3[3] = { {shadow[0].x,shadow[0].y },
					{shadow[1].x,shadow[1].y },//нижний треугольник
					{shadow[4].x,shadow[4].y } };//4
	Polygon(hdc, tr3, 3);
	POINT tr4[3] = { {shadow[0].x,shadow[0].y },
					{shadow[2].x,shadow[2].y },//верхний треугольник
					{shadow[3].x,shadow[3].y } };//5
	Polygon(hdc, tr4, 3);
	DeleteObject(brush);
}

bool Pyramid::CheckShadowOverlay() {
	if (pyramid[0][1] > shadow[0].y || pyramid[1][1] > shadow[1].y || pyramid[2][1] > shadow[2].y || pyramid[3][1] > shadow[3].y || pyramid[4][1] > shadow[4].y) {
		return true;
	}
	return false;
}

void Pyramid::scale(double Sx, double Sy, double Sz){
	double** scale = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		scale[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);
	
	scale[0][0] = Sx, scale[0][1] = 0,  scale[0][2] = 0, scale[0][3] = 0;
	scale[1][0] = 0,  scale[1][1] = Sy, scale[1][2] = 0, scale[1][3] = 0;
	scale[2][0] = 0,  scale[2][1] = 0,  scale[2][2] = Sz, scale[2][3] = 0;
	scale[3][0] = c[0] * (1 - Sx), scale[3][1] = c[1] * (1 - Sy), scale[3][2] = c[2] * (1 - Sz), scale[3][3] = 1;
	pyramid = mm(pyramid, scale, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] scale[i];
	}
	delete[] scale, c;
}

void Pyramid::turnX(double alpha){
	double** angle = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);

	angle[0][0] = cos(alpha * P / 180), angle[0][1] = sin(alpha * P / 180), angle[0][2] = 0, angle[0][3] = 0;
	angle[1][0] = -sin(alpha * P / 180), angle[1][1] = cos(alpha * P / 180), angle[1][2] = 0, angle[1][3] = 0;
	angle[2][0] = 0, angle[2][1] = 0, angle[2][2] = 1, angle[2][3] = 0;
	angle[3][0] = c[0] * (1 - cos(alpha * P /180)) + c[1] * sin(alpha * P / 180),
		angle[3][1] = c[1] * (1 - cos(alpha * P / 180)) - c[0] * sin(alpha * P / 180), angle[3][2] = 0, angle[3][3] = 1;
	pyramid = mm(pyramid, angle, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Pyramid::turnY(double alpha){
	double** angle = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);

	angle[0][0] = cos(alpha * P / 180), angle[0][1] = 0, angle[0][2] = sin(alpha * P / 180), angle[0][3] = 0;
	angle[1][0] = 0, angle[1][1] = 1, angle[1][2] = 0, angle[1][3] = 0;
	angle[2][0] = -sin(alpha * P / 180), angle[2][1] = 0, angle[2][2] = cos(alpha * P / 180), angle[2][3] = 0;
	angle[3][0] = c[0] * (1 - cos(alpha * P / 180)) + c[2] * sin(alpha * P / 180), angle[3][1] = 0, angle[3][2] = c[2] * (1 - cos(alpha * P / 180)) - c[0] * sin(alpha * P / 180), angle[3][3] = 1;
	pyramid = mm(pyramid, angle, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Pyramid::turnZ(double alpha){
	double** angle = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);

	angle[0][0] = 1, angle[0][1] = 0, angle[0][2] = 0, angle[0][3] = 0;
	angle[1][0] = 0, angle[1][1] = cos(alpha * P / 180), angle[1][2] = sin(alpha * P / 180), angle[1][3] = 0;
	angle[2][0] = 0, angle[2][1] = -sin(alpha * P / 180), angle[2][2] = cos(alpha * P / 180), angle[2][3] = 0;
	angle[3][0] = 0, angle[3][1] = c[1] * (1 - cos(alpha * P / 180)) + c[2] * sin(alpha * P / 180), angle[3][2] = c[2] * (1 - cos(alpha * P / 180)) - c[1] * sin(alpha * P / 180), angle[3][3] = 1;
	pyramid = mm(pyramid, angle, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Pyramid::setPlanePyr() {
	equationPlane(0, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[1][0], pyramid[1][1], pyramid[1][2], pyramid[2][0], pyramid[2][1], pyramid[2][2]);
	equationPlane(1, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[3][0], pyramid[3][1], pyramid[3][2], pyramid[4][0], pyramid[4][1], pyramid[4][2]);
	equationPlane(2, pyramid[1][0], pyramid[1][1], pyramid[1][2], pyramid[3][0], pyramid[3][1], pyramid[3][2], pyramid[2][0], pyramid[2][1], pyramid[2][2]);
	equationPlane(3, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[4][0], pyramid[4][1], pyramid[4][2], pyramid[1][0], pyramid[1][1], pyramid[1][2]);
	equationPlane(4, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[2][0], pyramid[2][1], pyramid[2][2], pyramid[3][0], pyramid[3][1], pyramid[3][2]);
}

void Pyramid::moveUp(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][1] -= a;
	}
}

void Pyramid::moveDown(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][1] += a;
	}
}

void Pyramid::moveLeft(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][0] -= a;
	}
}

void Pyramid::moveRight(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][0] += a;
	}
}

double** Pyramid::GetPyramid() {
	return this->pyramid;
}

Pyramid::~Pyramid(){
	for (int i = 0; i < 4; i++) {
		delete[] Pyramid::pyramid[i];
	}
	delete[] Pyramid::pyramid;
}
