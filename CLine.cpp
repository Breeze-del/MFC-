#include "stdafx.h"
#include "CLine.h"


CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::onDraw(CDC * pDC)
{
	pDC->MoveTo(this->point1.x, this->point1.y);
	pDC->LineTo(this->point2.x, this->point2.y);
}
