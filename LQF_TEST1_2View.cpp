
// LQF_TEST1_2View.cpp : CLQF_TEST1_2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LQF_TEST1_2.h"
#endif

#include "LQF_TEST1_2Doc.h"
#include "LQF_TEST1_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLQF_TEST1_2View

IMPLEMENT_DYNCREATE(CLQF_TEST1_2View, CView)

BEGIN_MESSAGE_MAP(CLQF_TEST1_2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLQF_TEST1_2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CLQF_TEST1_2View::OnStart)
	ON_COMMAND(ID_32772, &CLQF_TEST1_2View::On32772)
	ON_COMMAND(ID_32773, &CLQF_TEST1_2View::OnDan)
END_MESSAGE_MAP()

// CLQF_TEST1_2View 构造/析构

CLQF_TEST1_2View::CLQF_TEST1_2View()
{
	// TODO: 在此处添加构造代码

}

CLQF_TEST1_2View::~CLQF_TEST1_2View()
{
}

BOOL CLQF_TEST1_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLQF_TEST1_2View 绘制
void CLQF_TEST1_2View::OnDraw(CDC* /*pDC*/)
{
	CLQF_TEST1_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	Hanoilmpl(4, 'A', 'B', 'C');
	pointR = route.begin();
	CDC *pDC = GetDC();
	init(pDC);
}


// CLQF_TEST1_2View 打印


void CLQF_TEST1_2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLQF_TEST1_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLQF_TEST1_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLQF_TEST1_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CLQF_TEST1_2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLQF_TEST1_2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLQF_TEST1_2View 诊断

#ifdef _DEBUG
void CLQF_TEST1_2View::AssertValid() const
{
	CView::AssertValid();
}

void CLQF_TEST1_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLQF_TEST1_2Doc* CLQF_TEST1_2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLQF_TEST1_2Doc)));
	return (CLQF_TEST1_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLQF_TEST1_2View 消息处理程序


void CLQF_TEST1_2View::OnTimer(UINT_PTR nIDEvent)
{
	onDrawFont();
	mynIDEvent = nIDEvent;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (animTime == 0) {
		if (totalC==4) {
			KillTimer(nIDEvent);
			return;
		}
		this->pointR++;
		animTime = 3;
	}
	// 动画第一步
	if (animTime == 3) {
		animTime--;
		this->st = pointR->first;
		this->ed = pointR->second;
		// 从A开始第一步
		if (st == 'A') {
			animFirst(A, townerTopA, townerA, totalA);
			if (ed == 'B') {
				int wid = A.top();
				A.pop();
				B.push(wid);
				totalA -= 1;
				totalB += 1;
			}
			else {
				int wid = A.top();
				A.pop();
				C.push(wid);
				totalA -= 1;
				totalC += 1;
			}
		}
		else if (st == 'B') {
			animFirst(B, townerTopB, townerB, totalB);
			if (ed == 'A') {
				int wid = B.top();
				B.pop();
				A.push(wid);
				totalB -= 1;
				totalA += 1;
			}
			else {
				int wid = B.top();
				B.pop();
				C.push(wid);
				totalB -= 1;
				totalC += 1;
			}
		}
		else if(st=='C')
		{
			animFirst(C, townerTopC, townerC, totalC);
			if (ed == 'A') {
				int wid = C.top();
				C.pop();
				A.push(wid);
				totalC -= 1;
				totalA += 1;
			}
			else {
				int wid = C.top();
				C.pop();
				B.push(wid);
				totalC -= 1;
				totalB += 1;
			}
		}
	}
	// 动画第二步
	else if (animTime == 2) {
		animTime--;
		if (ed == 'A') {
			animSecond(townerTopA);
		}
		else if(ed == 'B')
		{
			animSecond(townerTopB);
		}
		else
		{
			animSecond(townerTopC);
		}
	}
	else {
		animTime--;
		if (ed == 'A') {
			animThird(townerA, totalA);
		}
		else if (ed == 'B') {
			animThird(townerB, totalB);
		}
		else {
			animThird(townerC, totalC);
		}
	}
	CView::OnTimer(nIDEvent);
}

void CLQF_TEST1_2View::Hanoilmpl(int n, char A, char B, char C) {
	if (n == 1) {
		move(A, C);
	}
	else {
		Hanoilmpl(n - 1, A, C, B);//步骤1 按ACB数序执行N-1的汉诺塔移动
		move(A, C);             //步骤2   执行最大盘子移动
		Hanoilmpl(n - 1, B, A, C);//步骤3 按BAC数序执行N-1的汉诺塔移动
	}
}

void CLQF_TEST1_2View::move(char A, char C) {
	static int j = 0;
	j++;
	//printf("移动路线 &c ---> %c", A, C);
	route.push_back(std::pair<char, char>(A, C));
}
void CLQF_TEST1_2View::init(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(217, 217, 217));
	// 设置画笔
	CPen cTowerPen;
	cTowerPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&cTowerPen);
	// 画基本界面
	CLine lineOne(300, 100, 300, 400);
	CLine lineTwo(500, 100, 500, 400);
	CLine lineThree(700, 100, 700, 400);
	CLine land(200, 400, 800, 400);
	lineOne.onDraw(pDC);
	lineTwo.onDraw(pDC);
	lineThree.onDraw(pDC);
	land.onDraw(pDC);
	pDC->SelectObject(oldPen);
	// 初始化三个塔子底部坐标
	this->townerA = lineOne.getPoint2();
	this->townerB = lineTwo.getPoint2();
	this->townerC = lineThree.getPoint2();
	// 初始化三个动画顶部位置
	this->townerTopA = lineOne.getPoint1();
	this->townerTopB = lineTwo.getPoint1();
	this->townerTopC = lineThree.getPoint1();
	// 画矩形
	CBrush brush(RGB(255, 0, 0));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CRectangle roundRect1(50);
	roundRect1.setNum(4);
	CRectangle roundRect2(100);
	roundRect2.setNum(3);
	CRectangle roundRect3(150);
	roundRect3.setNum(2);
	CRectangle roundRect4(200);
	roundRect4.setNum(1);
	A.push(200);
	A.push(150);
	A.push(100);
	A.push(50);
	roundRect1.prepare(townerA, pDC);
	roundRect2.prepare(townerA, pDC);
	roundRect3.prepare(townerA, pDC);
	roundRect4.prepare(townerA, pDC);
	pDC->SelectObject(oldBrush);
	ReleaseDC(pDC);
	//animFirst(A, townerTopA, townerA, totalA);
	//animSecond(townerTopB);
	//animThird(townerB, 1);
}

void CLQF_TEST1_2View::animFirst(std::stack<int>& target, CPoint toPoint,CPoint prePoint,int num) {
	// 擦出上一个矩形
	CDC *pDC = GetDC();
	CPen cTowerPen;
	cTowerPen.CreatePen(PS_SOLID, 0, RGB(217, 217, 217));
	CPen* oldPen = pDC->SelectObject(&cTowerPen);
	CBrush brush(RGB(217, 217, 217));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	int rwid = target.top();
	CRectangle roundRect(rwid);
	roundRect.setNum(num);
	roundRect.prepare(prePoint, pDC);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	// 补全塔子
	recover(roundRect);
	// 距离顶部1个高度
	roundRect.setNum(1);
	CBrush brush1(RGB(255, 0, 0));
	CBrush *oldBrush1 = pDC->SelectObject(&brush1);
	roundRect.prepare(toPoint, pDC);
	ReleaseDC(pDC);
	// 绑定目标矩形
	this->targetR = new CRectangle(roundRect);
}

void CLQF_TEST1_2View::recover(CRectangle & rectangle)
{
	CPoint top, bottom;
	top.x = rectangle.getPoint1().x + rectangle.getWidth();
	top.y = rectangle.getPoint1().y;
	bottom.x = rectangle.getPoint2().x - rectangle.getWidth();
	bottom.y = rectangle.getPoint2().y;
	CDC *pDC = GetDC();
	CPen cTowerPen;
	cTowerPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&cTowerPen);
	pDC->MoveTo(top.x, top.y);
	pDC->LineTo(bottom.x, bottom.y);
	ReleaseDC(pDC);
}

void CLQF_TEST1_2View::animSecond(CPoint toPoint)
{
	// 擦出上一个矩形
	CDC *pDC = GetDC();
	CPen cTowerPen;
	cTowerPen.CreatePen(PS_SOLID, 0, RGB(217, 217, 217));
	CPen* oldPen = pDC->SelectObject(&cTowerPen);
	CBrush brush(RGB(217, 217, 217));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	this->targetR->onDraw(pDC);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	// 画出下一个位置矩形
	CBrush brush1(RGB(255, 0, 0));
	CBrush *oldBrush1 = pDC->SelectObject(&brush1);
	this->targetR->prepare(toPoint, pDC);
	ReleaseDC(pDC);
}

void CLQF_TEST1_2View::animThird(CPoint toPoint,int num)
{
	// 擦出上一个矩形
	CDC *pDC = GetDC();
	CPen cTowerPen;
	cTowerPen.CreatePen(PS_SOLID, 0, RGB(217, 217, 217));
	CPen* oldPen = pDC->SelectObject(&cTowerPen);
	CBrush brush(RGB(217, 217, 217));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	this->targetR->onDraw(pDC);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	// 画出下一个矩型
	this->targetR->setNum(num);
	CBrush brush1(RGB(255, 0, 0));
	CBrush *oldBrush1 = pDC->SelectObject(&brush1);
	this->targetR->prepare(toPoint, pDC);
	ReleaseDC(pDC);
}

void CLQF_TEST1_2View::oneStep()
{
	if (animTime == 0) {
		if (totalC == 4) {
			
			return;
		}
		this->pointR++;
		animTime = 3;
	}
	// 动画第一步
	if (animTime == 3) {
		animTime--;
		this->st = pointR->first;
		this->ed = pointR->second;
		// 从A开始第一步
		if (st == 'A') {
			animFirst(A, townerTopA, townerA, totalA);
			if (ed == 'B') {
				int wid = A.top();
				A.pop();
				B.push(wid);
				totalA -= 1;
				totalB += 1;
			}
			else {
				int wid = A.top();
				A.pop();
				C.push(wid);
				totalA -= 1;
				totalC += 1;
			}
		}
		else if (st == 'B') {
			animFirst(B, townerTopB, townerB, totalB);
			if (ed == 'A') {
				int wid = B.top();
				B.pop();
				A.push(wid);
				totalB -= 1;
				totalA += 1;
			}
			else {
				int wid = B.top();
				B.pop();
				C.push(wid);
				totalB -= 1;
				totalC += 1;
			}
		}
		else if (st == 'C')
		{
			animFirst(C, townerTopC, townerC, totalC);
			if (ed == 'A') {
				int wid = C.top();
				C.pop();
				A.push(wid);
				totalC -= 1;
				totalA += 1;
			}
			else {
				int wid = C.top();
				C.pop();
				B.push(wid);
				totalC -= 1;
				totalB += 1;
			}
		}
	}
	// 动画第二步
	else if (animTime == 2) {
		animTime--;
		if (ed == 'A') {
			animSecond(townerTopA);
		}
		else if (ed == 'B')
		{
			animSecond(townerTopB);
		}
		else
		{
			animSecond(townerTopC);
		}
	}
	else {
		animTime--;
		if (ed == 'A') {
			animThird(townerA, totalA);
		}
		else if (ed == 'B') {
			animThird(townerB, totalB);
		}
		else {
			animThird(townerC, totalC);
		}
	}
}

void CLQF_TEST1_2View::onDrawFont()
{
	CDC* pDC = GetDC();
	HDC dc = pDC->GetSafeHdc();
	CRect clientRect;
	GetClientRect(clientRect);

	int width = clientRect.Width();
	int height = clientRect.Height();
	int textRectWidth = width / 50 + width * 2 / 5;
	int textRectHeight = width / 50;
	CString times;
	int moveTimes = 0;

	SetTextColor(*pDC, RGB(0, 0, 0));
	SetBkMode(*pDC, TRANSPARENT);

	//moveTimes = needleMoveTimes[0] == 0 ? 14 : 14 + int(log10(needleMoveTimes[0]));
	CRect textRect = CRect(width / 3 - width / 4, height / 5 + height / 2, width / 3 + width / 50 + width / 5, height / 5 + height / 2 + textRectHeight);
	times.Format(_T("A根针上发生的总移动次数：%d"), totalA);
	DrawText(dc, times, moveTimes, textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	//moveTimes = needleMoveTimes[1] == 0 ? 14 : 14 + int(log10(needleMoveTimes[1]));
	textRect = CRect(width / 2 - width / 5, height / 5 + height / 2, width / 2 + width / 50 + width / 5, height / 5 + height / 2 + textRectHeight);
	times.Format(_T("B根针上发生的总移动次数：%d"), totalB);
	DrawText(dc, times, moveTimes, textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//moveTimes = needleMoveTimes[2] == 0 ? 14 : 14 + int(log10(needleMoveTimes[2]));
	textRect = CRect(width * 2 / 3, height / 5 + height / 2, width * 2 / 3 + width / 50 + width / 4, height / 5 + height / 2 + textRectHeight);
	times.Format(_T("C根针上发生的总移动次数：%d"), totalC);
	DrawText(dc, times, moveTimes, textRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);


}


void CLQF_TEST1_2View::OnStart()
{
	// TODO: 在此添加命令处理程序代码

	SetTimer(1, 500, NULL);
}


void CLQF_TEST1_2View::On32772()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(mynIDEvent);
}


void CLQF_TEST1_2View::OnDan()
{
	// TODO: 在此添加命令处理程序代码
	oneStep();
}
