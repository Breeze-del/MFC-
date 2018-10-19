#pragma once
#include "CShape.h"
class CRectangle :
	public CShape
{
public:
	CRectangle();
	CRectangle(int width) :width(width/2) {
		//默认圆角为10
		roundP.x = 10;
		roundP.y = 10;
	}
	CRectangle(int x1, int y1, int x2, int y2, int width) : CShape(x1, y1, x2, y2),width(width) {
		//默认圆角为10
		roundP.x = 10;
		roundP.y = 10;
	};
	~CRectangle();
	void onDraw(CDC *pDC);
	void prepare(const CPoint location,int height,CDC *pDC);
	void setNum(int num);
	void prepare(const CPoint location, CDC * pDC);
	int getWidth();
private:
	CPoint roundP;
	CPoint top, bottom;
	int width;// 矩形的宽度
	int height = 25; // 矩形高度
	int num;// 距离底部多少个高度
};

