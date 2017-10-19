
// chessboardView.cpp : CchessboardView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "chessboard.h"
#endif

#include "chessboardDoc.h"
#include "chessboardView.h"
#include "PointItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;

// CchessboardView

IMPLEMENT_DYNCREATE(CchessboardView, CView)

BEGIN_MESSAGE_MAP(CchessboardView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CchessboardView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	//ON_WM_CONTEXTMENU()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_DW, &CchessboardView::OnEditDw)
	ON_COMMAND(ID_EDIT_DEL, &CchessboardView::On32773)
	ON_COMMAND(ID_EDIT_DA, &CchessboardView::OnEditDa)
END_MESSAGE_MAP()

// CchessboardView ����/����

CchessboardView::CchessboardView()
{
	// TODO: �ڴ˴����ӹ������
	m_isDraw = false;
	m_lastPoint.x = 0;
	m_lastPoint.y = 0;
	m_mode   = M_DRAW_W;
}

CchessboardView::~CchessboardView()
{

}

BOOL CchessboardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CchessboardView ����

void CchessboardView::OnDraw(CDC* pDC/*pDC*/)
{
	CchessboardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	HDC hdc = pDC->m_hDC;
	using namespace Gdiplus;
	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	Pen newPen(Color(0, 255, 255), 2);

	graphics.DrawLine(&newPen, 0, 0, 500, 500);
	

	// TODO: �ڴ˴�Ϊ�����������ӻ��ƴ���
	//drawAllPoint();
}




// CchessboardView ��ӡ


void CchessboardView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CchessboardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CchessboardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ���Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CchessboardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ���Ӵ�ӡ����е���������
}

void CchessboardView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CchessboardView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CchessboardView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CchessboardDoc *pDoc = GetDocument();

	if(m_isDraw) {
		m_lastPoint = point;
		if (pDoc->m_groupLast != NULL) {
			if (pDoc->m_groupLast->ptr != NULL) {
				pDoc->m_groupLast->ptr->last->point = point;
			}
		}
        pDoc->addPointItem(point, Gdiplus::Color(0, 255, 255), 2);//���һ��������
	} else {
	   if (pDoc->m_groupLast != NULL) {
           pDoc->addNewPointsGroup(point, Gdiplus::Color(0, 255, 255), 2);
		   pDoc->addPointItem(point, Gdiplus::Color(0, 255, 255), 2);//���һ��������
	   } else {
	      pDoc->addPointItem(point, Gdiplus::Color(0, 255, 255), 2);//ȷ�ϵ�
	      pDoc->addPointItem(point, Gdiplus::Color(0, 255, 255), 2);//���һ��������
	   }
	   m_isDraw    = true;
	   m_lastPoint = point;
	}
	drawAllPoint();

}

void CchessboardView::OnMouseMove(UINT nFlags, CPoint point)
{
	 CchessboardDoc *pDoc = GetDocument();

	if (m_isDraw) {
	
		if (pDoc->m_groupLast != NULL) {
			if (pDoc->m_groupLast->ptr != NULL) {
				pDoc->m_groupLast->ptr->last->point = point;
			}
		}
		drawAllPoint();
	}


}

void CchessboardView::OnRButtonDown(UINT nFlags, CPoint point)
{
	//m_isDraw = false;
	//ɾ�������һ���ڵ�
	if (m_isDraw) {
		CchessboardDoc *pDoc = GetDocument();
		pDoc->removePointItem();
		drawAllPoint();
		m_isDraw = false;
	}
}

void CchessboardView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    m_isDraw = false;
}

BOOL CchessboardView::OnEraseBkgnd(CDC* pDC)  
{ 
 	 return TRUE; 
} 
void CchessboardView::drawPointGroup(CDC* pDC, PointItemGroup_t *pGroup)
{

	if (pGroup != NULL) {
	    HDC hdc = pDC->m_hDC;
		using namespace Gdiplus;
	    Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeAntiAlias);
		Pen newPen(pGroup->attr.c, pGroup->attr.width);
		PointItem_t *pItem = pGroup->ptr;
		PointItem_t *pEnd  = pItem->last;
		while((pItem != pItem->next) && (pEnd != pItem)) {
		    graphics.DrawLine(&newPen, pItem->point.x, pItem->point.y, (pItem->next->point.x), (pItem->next->point.y));
			pItem = pItem->next;
		}

	}
}
void CchessboardView::drawAllPoint()
{
	 CDC *pDC = GetDC();
	 CMemDC dcMem(*pDC,this);
	 CDC& dc = dcMem.GetDC();
	 HDC hdc = dc.m_hDC;
	 using namespace Gdiplus;
	 Graphics graphics(hdc);
	 graphics.SetSmoothingMode(SmoothingModeAntiAlias);
     graphics.Clear(Gdiplus::Color(255, 255, 255));
	 CchessboardDoc *pDoc = GetDocument();

	 PointItemGroup_t *p_groupHead = pDoc->m_groupHead, *p_temp;
	 p_temp = p_groupHead;
	 while (p_temp) {
		 drawPointGroup(&dc, p_temp);
	     p_temp = p_temp->next;
	 }
}

void CchessboardView::OnLButtonUp(UINT nFlags, CPoint point)
{

}

// CchessboardView ���

#ifdef _DEBUG
void CchessboardView::AssertValid() const
{
	CView::AssertValid();
}

void CchessboardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CchessboardDoc* CchessboardView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CchessboardDoc)));
	return (CchessboardDoc*)m_pDocument;
}
#endif //_DEBUG



// CchessboardView ��Ϣ��������


void CchessboardView::OnEditDw()
{
	// TODO: �ڴ�����������������
	m_mode = M_DRAW_W;
	//SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(NULL , IDC_CROSS));
	//SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(AfxGetResourceHandle(), CString("pen_24px_1188125_easyicon.net.ico")));
	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(AfxGetResourceHandle() , MAKEINTRESOURCE(IDB_PEN_16)));

}


void CchessboardView::On32773()
{
	// TODO: �ڴ�����������������
	m_mode = M_DEL;
	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(NULL , IDC_CROSS));
}


void CchessboardView::OnEditDa()
{
	// TODO: �ڴ�����������������
	m_mode = M_DRAW_A;
	
	//SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(NULL , IDC_CROSS));
	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursorFromFile(CString("pen_24px_1148416_easyicon.net.ico")));
	//SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(this->Get , MAKEINTRESOURCE(IDI_CURSOR_PEN16)));
	

}