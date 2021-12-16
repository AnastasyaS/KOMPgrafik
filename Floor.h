#pragma once
#include "figur.h"
#include "Prism.h"
#include "piramida.h"

class Floor : public Figure{
private:
	double** floor;
public:
	Floor();//констрктор
	void Draw(HDC hdc, RECT rect, Pyramid, Prism);
	void turnX(double alpha);
	~Floor();//деструктор
};

