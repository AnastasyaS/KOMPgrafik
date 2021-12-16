#pragma once
#include "figur.h"

class Prism : public Figure {
private:
	double** prism;
	POINT shadow[6];
public:
	Prism();//конструктор
	Prism(const Prism& copy);//конструктор копирования
	void Draw(HDC);
	void DrawShadow(HDC hdc, RECT rect);
	bool CheckShadowOverlay();
	//приближение/отдаление
	void scale(double Sx, double Sy, double Sz);
	//вращение по осям
	void turnX(double alpha);
	void turnY(double alpha);
	void turnZ(double alpha);
	void setPlanePrism();
	//движение по направлениям
	void moveUp(int a);
	void moveDown(int a);
	void moveLeft(int a);
	void moveRight(int a);
	//
	double** GetPrism();
	~Prism();//очистка
};
