
// chessboardDoc.cpp : CchessboardDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CchessboardDoc ����/����

CchessboardDoc::CchessboardDoc()
{
	// TODO: �ڴ����һ���Թ������
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
	
	//ɾ����������е�
	if (pTmp == NULL) {
	   return;
	}
	if (pTmp->next == pTmp) {
	   //����ֻ��һ��
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
	//ɾ������
	while (pTmpGroup) {
		if (pTmpGroup->ptr == pItems) {
		   pDelGroup = pTmpGroup;
		   break;
		}
		pTmpGroup = pTmpGroup->next;
	}

	if (pDelGroup != NULL) {
		if (pDelGroup->last != NULL) {
			//��������б��ͷ
		    pDelGroup->last->next = pDelGroup->next;
		} else {
		   //���б��ͷ�������
		   m_groupHead = pDelGroup->next;
		}
		if (pDelGroup->next != NULL) {
			//��������б�β��
		    pDelGroup->next->last = pDelGroup->last;
		} else {
		   //���б��β�������
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
		//����һ���ߣ�����ӵ����ߵ����һ��
		pNowGroupHead = m_groupLast->ptr;
		pNowGroupHead->last->next =  pNew;
		pNew->last = pNowGroupHead->last;
		pNew->next = pNowGroupHead;
		pNowGroupHead->last = pNew;
		//���¸�������ԣ������µĵ��������
		m_groupLast->attr.c     = c;
		m_groupLast->attr.width = width;
	} else {
	    //û�д���һ���ߣ����¼�һ����
		addPointsGroup(pNew, c, width, type);
	}
}
void CchessboardDoc::removePointItem()
{
	PointItem_t *pNowGroupHead = NULL, *pDel = NULL;
	if (m_groupLast != NULL) {
		pNowGroupHead = m_groupLast->ptr;
		//����һ���ߣ���ɾ�������ߵ����һ����
		if (pNowGroupHead == pNowGroupHead->last) {
		    //�������ֻ����һ���㣬����Ҫ��ɾ���õ㣬Ȼ��ɾ������
			delete pNowGroupHead;
			pNowGroupHead = NULL;

			PointItemGroup_t *pDelGroup = m_groupLast;
			if (pDelGroup != NULL) {
				if (pDelGroup->last != NULL) {
					//��������б��ͷ
					pDelGroup->last->next = pDelGroup->next;
				} else {
				   //���б��ͷ�������
				   m_groupHead = pDelGroup->next;
				}
				if (pDelGroup->next != NULL) {
					//��������б�β��
					pDelGroup->next->last = pDelGroup->last;
				} else {
				   //���б��β�������
					m_groupLast = pDelGroup->last;
				}
				delete pDelGroup;
		   }
		} else {
			//���������ڶ����
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
		//ɾ������
		while (pTmpGroup) {
			removeGroup(pTmpGroup->ptr);
			/*
			pDelGroup = pTmpGroup;
			if (pDelGroup->last != NULL) {
				//��������б��ͷ
				pDelGroup->last->next = pDelGroup->next;
			} else {
			   //���б��ͷ�������
			   m_groupHead = pDelGroup->next;
			}
			if (pDelGroup->next != NULL) {
				//��������б�β��
				pDelGroup->next->last = pDelGroup->last;
			} else {
			   //���б��β�������
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
			   //����ֻ��һ��
				continue;
			} else {
				do {
					pLast = pTmp;
					pTmp = pTmp->next;
					//�ж��ж�б��
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
		//����ֻ��һ��
		return false;
	} else {
		//���ɾ���ĵ��ڶϵ磬��ֱ��ɾ��
	}
}

BOOL CchessboardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CchessboardDoc ���л�

void CchessboardDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CchessboardDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CchessboardDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CchessboardDoc ���

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


// CchessboardDoc ����
