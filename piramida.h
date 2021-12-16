#pragma once
#include"figur.h"

class Pyramid : public Figure {
private:
	double** pyramid;
	POINT shadow[5];
public:
	
	Pyramid();//конструктор по умолчанию
	Pyramid(const Pyramid &copy);//конструктор копирования
	//отрисовка
	void Draw(HDC);
	void DrawShadow(HDC hdc, RECT rect);
	bool CheckShadowOverlay();
	//приближение/отдаление
	void scale(double Sx, double Sy, double Sz);
	//вращение
	void turnX(double alpha);
	void turnY(double alpha);
	void turnZ(double alpha);
	void setPlanePyr();//матрица объёмом пирамиды
	
	void moveUp(int a);//движение по направлениям
	void moveDown(int a);
	void moveLeft(int a);
	void moveRight(int a);
	
	double** GetPyramid();
	~Pyramid();//очистка
};
