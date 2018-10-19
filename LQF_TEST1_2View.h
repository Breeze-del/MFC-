
// LQF_TEST1_2View.h : CLQF_TEST1_2View 类的接口
//

#pragma once

#include"CLine.h"
#include"CRectangle.h"
#include<stack>
#include<vector>
class CLQF_TEST1_2View : public CView
{
protected: // 仅从序列化创建
	CLQF_TEST1_2View();
	DECLARE_DYNCREATE(CLQF_TEST1_2View)

// 特性
public:
	CLQF_TEST1_2Doc* GetDocument() const;

// 操作
public:
	void Hanoilmpl(int n, char A, char B, char C);
	void move(char A, char C);
	void init(CDC *pDC);
	// 动画第一步
	void animFirst(std::stack<int>& target, CPoint toPoint, CPoint prePoint, int num);
	// 补全塔子
	void recover( CRectangle& rectangle);
	// 动画第二步
	void animSecond(CPoint toPoint);
	// 动画第三步
	void animThird(CPoint toPoint,int num);
	// 动画单步执行
	void oneStep();
	// 写字
	void onDrawFont();
private:
	// 三个塔子的底部坐标
	CPoint townerA, townerB, townerC;
	// 三个塔子顶部 也就是动画第一步到达的坐标位置
	CPoint townerTopA, townerTopB, townerTopC;

	int totalA=4, totalB=0, totalC=0; // 统计塔子里矩形个数
	std::stack<int> A,B,C; // 放塔子里的矩形宽度
	CRectangle* targetR; // 目标矩形
	int animTime =3; // 表示正在进行动画的第几步
	// 移动的路线
	std::vector<std::pair<char, char>> route;
	std::vector<std::pair<char, char>>::iterator pointR;
	char st, ed;
	UINT_PTR mynIDEvent;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLQF_TEST1_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStart();
	afx_msg void On32772();
	afx_msg void OnDan();
};

#ifndef _DEBUG  // LQF_TEST1_2View.cpp 中的调试版本
inline CLQF_TEST1_2Doc* CLQF_TEST1_2View::GetDocument() const
   { return reinterpret_cast<CLQF_TEST1_2Doc*>(m_pDocument); }
#endif

