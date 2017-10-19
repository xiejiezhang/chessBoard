
// chessboardView.h : CchessboardView 类的接口
//

#pragma once
#include "PointItem.h"

enum DRAW_MODE{M_DRAW_W, M_DRAW_A, M_DEL};
class CchessboardView : public CView
{
protected: // 仅从序列化创建
	CchessboardView();
	DECLARE_DYNCREATE(CchessboardView)

// 特性
public:
	CchessboardDoc* GetDocument() const;

// 操作
public:
	void drawAllPoint();
	void drawPointGroup(CDC* pDC, PointItemGroup_t *);
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
	virtual ~CchessboardView();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC) ;
	DECLARE_MESSAGE_MAP()

private:
	bool m_isDraw;
	CPoint m_lastPoint; 
	DRAW_MODE  m_mode;
public:
	afx_msg void OnEditDw();
	afx_msg void On32773();
	afx_msg void OnEditDa();
};

#ifndef _DEBUG  // chessboardView.cpp 中的调试版本
inline CchessboardDoc* CchessboardView::GetDocument() const
   { return reinterpret_cast<CchessboardDoc*>(m_pDocument); }
#endif

