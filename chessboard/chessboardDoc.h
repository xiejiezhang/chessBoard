
// chessboardDoc.h : CchessboardDoc 类的接口
//


#pragma once
#include"PointItem.h"

class CchessboardDoc : public CDocument
{
protected: // 仅从序列化创建
	CchessboardDoc();
	DECLARE_DYNCREATE(CchessboardDoc)

// 特性
public:
    PointItemGroup_t *m_groupHead;
	PointItemGroup_t *m_groupLast;
// 操作
public:
	void addPointsGroup(PointItem_t *pItems, Color c, float width);
	void removeGroup(PointItem_t *pItems);
	void addPointItem(CPoint p, Color c, float width);
	void removePointItem();
	void removeAllGroup();
	void addNewPointsGroup(CPoint p, Color c, float width);
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CchessboardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
