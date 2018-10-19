#pragma once
class CShape
{
public:
	CShape(int x1, int y1, int x2, int y2) {
		this->point1.x = x1;
		this->point1.y = y1;
		this->point2.x = x2;
		this->point2.y = y2;
	};
	CShape();
	virtual ~CShape();
	virtual void onDraw(CDC *pDC)=0;
	CPoint getPoint1();
	CPoint getPoint2();
	CPoint point1, point2;
};

