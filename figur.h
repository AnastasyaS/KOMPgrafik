#pragma once
#pragma comment(linker, "/STACK:99999999999")
#include<Windows.h>
#include <iostream>
#include<stack>


using namespace std;

#define M 4
#define N 5
#define P 3.141592653589793

extern double res[4][10];
extern double e[4];
extern double eq[4];//уравнение для пола

class Figure
{
public:
	
	double* findCentre(double** mas, int n, int m);//вычисление центра
	
	double fill(HDC, double x, double y, double x0);//заливка

	double product(double Px, double Py, double Ax, double Ay, double Bx, double By);
	//перемножение матриц
	double** mm(double** masA, double** masB, int, int, int, int);
	void ContourDraw(HDC, POINT* p, int);// контур
	void Hatching(HDC, POINT* p, int);
	void equationPlane(int numPlane, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);// уравнение плоскости

	virtual void turnX(double alpha) = 0;
};

