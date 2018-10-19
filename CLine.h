#pragma once
#include "CShape.h"
class CLine :
	public CShape
{
public:
	CLine(int x1, int y1, int x2, int y2) : CShape(x1, y1, x2, y2) {};
	CLine();
	~CLine();
	void onDraw(CDC *pDC);
};

