
// chessboardDoc.h : CchessboardDoc ��Ľӿ�
//


#pragma once
#include"PointItem.h"

class CchessboardDoc : public CDocument
{
protected: // �������л�����
	CchessboardDoc();
	DECLARE_DYNCREATE(CchessboardDoc)

// ����
public:
    PointItemGroup_t *m_groupHead;
	PointItemGroup_t *m_groupLast;
// ����
public:
	void addPointsGroup(PointItem_t *pItems, Color c, float width);
	void removeGroup(PointItem_t *pItems);
	void addPointItem(CPoint p, Color c, float width);
	void removePointItem();
	void removeAllGroup();
	void addNewPointsGroup(CPoint p, Color c, float width);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CchessboardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
