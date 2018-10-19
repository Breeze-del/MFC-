#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::onDraw(CDC * pDC)
{
	pDC->RoundRect(top.x, top.y, bottom.x, bottom.y, roundP.x, roundP.y);
}

void CRectangle::prepare(const CPoint location,int hNum,CDC *pDC)
{
	top.x = location.x - width;
	top.y = location.y - (hNum*this->height);
	bottom.x = location.x + width;
	bottom.y = top.y + height;
	onDraw(pDC);
}

void CRectangle::setNum(int num)
{
	this->num = num;
}

void CRectangle::prepare(const CPoint location, CDC *pDC)
{
	top.x = location.x - width;
	top.y = location.y - (num*this->height);
	bottom.x = location.x + width;
	bottom.y = top.y + height;
	this->point1 = top;
	this->point2=bottom;
	onDraw(pDC);
}

int CRectangle::getWidth()
{
	return this->width;
}
