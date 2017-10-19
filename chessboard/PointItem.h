#ifndef __POINTITEM_H
#define __POINTITEM_H

#include <winapifamily.h>
/**
 * ͼ�е�ÿһ��
 */
typedef struct __PointItem{
    CPoint      point;
	struct __PointItem *next;
	struct __PointItem *last;
}PointItem_t;

using namespace Gdiplus;
/**
 * ÿһ���ߵ�����
 */
typedef struct __PointsGroupAttr{
    Color c;
	float  width;
}PointsGroupAttr_t;

/**
 * �����ߵ���
 */
typedef struct __PointItemGroup{
    PointItem_t       *ptr;
	PointsGroupAttr_t  attr;
	struct __PointItemGroup *next;
	struct __PointItemGroup *last;
}PointItemGroup_t;

#endif