
// chessboardDoc.cpp : CchessboardDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "chessboard.h"
#endif

#include "chessboardDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CchessboardDoc

IMPLEMENT_DYNCREATE(CchessboardDoc, CDocument)

BEGIN_MESSAGE_MAP(CchessboardDoc, CDocument)
END_MESSAGE_MAP()


// CchessboardDoc 构造/析构

CchessboardDoc::CchessboardDoc()
{
	// TODO: 在此添加一次性构造代码
	m_groupHead = NULL;
	m_groupLast = NULL;
}

CchessboardDoc::~CchessboardDoc()
{
	removeAllGroup();
}

void CchessboardDoc::addPointsGroup(PointItem_t *pItems, Color c, float width, POINT_TYPE type)
{
	if (pItems != NULL) {
		PointItemGroup_t *pNew = new PointItemGroup_t;
		pNew->next = NULL;
		pNew->last = NULL;
		pNew->attr.c = c;
		pNew->attr.width = width;
		pNew->ptr = pItems;
		if (m_groupHead != NULL) {
			m_groupLast->next = pNew;
			pNew->last        = m_groupLast;
		} else {
		   m_groupHead = pNew;
		}
		m_groupLast = pNew;
	}
}

void CchessboardDoc::addNewPointsGroup(CPoint p, Color c, float width, POINT_TYPE type)
{
    PointItem_t *pItems = new PointItem_t;
	pItems->next = pItems;
	pItems->last = pItems;
	pItems->point = p;
	addPointsGroup(pItems, c, width,type);
}

void CchessboardDoc::removeGroup(PointItem_t *pItems)
{
	PointItem_t *pTmp = pItems, *pDel = NULL;
	
	//删掉该组的所有点
	if (pTmp == NULL) {
	   return;
	}
	if (pTmp->next == pTmp) {
	   //该组只有一点
		delete pTmp;
	} else {
		do {
		    pDel = pTmp;
			pTmp = pTmp->next;
			pTmp->last = pDel->last;
			pDel->last->next = pDel->next; 
			delete pDel;
		} while(pTmp->next != pTmp);
		delete pTmp;
	}


	PointItemGroup_t *pTmpGroup = m_groupHead, *pDelGroup = NULL;
	//删掉该组
	while (pTmpGroup) {
		if (pTmpGroup->ptr == pItems) {
		   pDelGroup = pTmpGroup;
		   break;
		}
		pTmpGroup = pTmpGroup->next;
	}

	if (pDelGroup != NULL) {
		if (pDelGroup->last != NULL) {
			//如果不在列表表头
		    pDelGroup->last->next = pDelGroup->next;
		} else {
		   //在列表表头，则更新
		   m_groupHead = pDelGroup->next;
		}
		if (pDelGroup->next != NULL) {
			//如果不在列表尾出
		    pDelGroup->next->last = pDelGroup->last;
		} else {
		   //在列表表尾，则更新
		    m_groupLast = pDelGroup->last;
		}
		delete pDelGroup;
	}
}
void CchessboardDoc::addPointItem(CPoint p, Color c, float width, POINT_TYPE type)
{
	PointItem_t *pNowGroupHead = NULL;

	PointItem_t *pNew = new PointItem_t;
	pNew->next = pNew;
	pNew->last = pNew;
	pNew->point = p;
	if (m_groupLast != NULL) {
		//存在一组线，则添加到这线的最后一个
		pNowGroupHead = m_groupLast->ptr;
		pNowGroupHead->last->next =  pNew;
		pNew->last = pNowGroupHead->last;
		pNew->next = pNowGroupHead;
		pNowGroupHead->last = pNew;
		//更新该组的属性，按最新的点的属性走
		m_groupLast->attr.c     = c;
		m_groupLast->attr.width = width;
	} else {
	    //没有存在一组线，则新加一组线
		addPointsGroup(pNew, c, width, type);
	}
}
void CchessboardDoc::removePointItem()
{
	PointItem_t *pNowGroupHead = NULL, *pDel = NULL;
	if (m_groupLast != NULL) {
		pNowGroupHead = m_groupLast->ptr;
		//存在一组线，则删掉到这线的最后一个点
		if (pNowGroupHead == pNowGroupHead->last) {
		    //如果该组只存在一个点，则需要先删掉该点，然后删掉该组
			delete pNowGroupHead;
			pNowGroupHead = NULL;

			PointItemGroup_t *pDelGroup = m_groupLast;
			if (pDelGroup != NULL) {
				if (pDelGroup->last != NULL) {
					//如果不在列表表头
					pDelGroup->last->next = pDelGroup->next;
				} else {
				   //在列表表头，则更新
				   m_groupHead = pDelGroup->next;
				}
				if (pDelGroup->next != NULL) {
					//如果不在列表尾出
					pDelGroup->next->last = pDelGroup->last;
				} else {
				   //在列表表尾，则更新
					m_groupLast = pDelGroup->last;
				}
				delete pDelGroup;
		   }
		} else {
			//如果该组存在多个点
			pDel          = m_groupLast->ptr->last;

			pDel->last->next = pDel->next;
			pDel->next->last = pDel->last;
			delete pDel;
		}
	}
}

void  CchessboardDoc::removeAllGroup()
{
    PointItemGroup_t *pTmpGroup = m_groupHead, *pDelGroup = NULL;
	while(m_groupHead) {
		//删掉该组
		while (pTmpGroup) {
			removeGroup(pTmpGroup->ptr);
			/*
			pDelGroup = pTmpGroup;
			if (pDelGroup->last != NULL) {
				//如果不在列表表头
				pDelGroup->last->next = pDelGroup->next;
			} else {
			   //在列表表头，则更新
			   m_groupHead = pDelGroup->next;
			}
			if (pDelGroup->next != NULL) {
				//如果不在列表尾出
				pDelGroup->next->last = pDelGroup->last;
			} else {
			   //在列表表尾，则更新
				m_groupLast = pDelGroup->last;
			}
			delete pDelGroup;
			*/
		}
	}
}

bool CchessboardDoc::isInLine( CPoint *pA, CPoint *pB, CPoint c)
{
	bool ret = false;
	float origin , test1, test2;
	if ((pA == NULL ) || (pB == NULL)) {
	   return ret;
	}
	if ((pA->y == pB->y) || (pA->y == c.y) || (pB->y == c.y)) {
		if ((pA->y == c.y) && (pA->y == pB->y)) {
		    ret = true;
		}
	} else {
		origin =  (pA->x - pB->x) / (pA->y - pB->y);
		test1  =  (c.x - pA->x) / (c.y - pA->y);
		test2  =  (c.x - pB->x) / (c.y - pB->y);
		if ((origin == test1) && (origin == test2)) {
		      ret = true;
		}
	}
	return ret;
}
bool CchessboardDoc::isPointInLine(PointItem_t *pItems, CPoint *pA, CPoint *pB, CPoint c)
{
    PointItemGroup_t *pTmpGroup = m_groupHead, *pDelGroup = NULL;
    PointItem_t      *pNowGroupHead = NULL, *pTmp = NULL, *pLast = NULL;

	if ((pA == NULL ) || (pB == NULL) || (pItems == NULL)) {
	   return false;
	}
	if(m_groupHead) {
		while (pTmpGroup) {
			pNowGroupHead = pTmpGroup->ptr;
			
			pTmp          = pNowGroupHead;
			if (pTmp == NULL){
			    continue;
			}
			if (pTmp->next == pTmp) {
			   //该组只有一点
				continue;
			} else {
				do {
					pLast = pTmp;
					pTmp = pTmp->next;
					//判断判断斜率
					if(isInLine(&(pTmp->point), &(pLast->point), c) == true) {
					   pItems = pLast;
					   *pA    = pLast->point;
					   *pB    = pTmp->point;
					   return true;
					}
				} while(pTmp->next != pNowGroupHead);
	
			}
			pTmpGroup = pTmpGroup->next;
		}
	}
	return false; 
}
//bool isDelPoint(PointItem_t *pItems, CPoint *pA);
bool CchessboardDoc::isDelLine(PointItem_t *pItems, CPoint *pA, CPoint *pB)
{
    PointItem_t      *pNowGroupHead = NULL, *pTmp = NULL, *pLast = NULL;
    pTmp          = pNowGroupHead;
	if (pTmp == NULL){
		return false;
	}
	if (pTmp->next == pTmp) {
		//该组只有一点
		return false;
	} else {
		//如果删掉的点在断电，则直接删掉
	}
}

BOOL CchessboardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CchessboardDoc 序列化

void CchessboardDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CchessboardDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CchessboardDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CchessboardDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CchessboardDoc 诊断

#ifdef _DEBUG
void CchessboardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CchessboardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CchessboardDoc 命令
