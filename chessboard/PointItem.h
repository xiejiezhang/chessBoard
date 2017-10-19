#ifndef __POINTITEM_H
#define __POINTITEM_H

#include <winapifamily.h>
/**
 * 图中的每一点
 */
typedef struct __PointItem{
    CPoint      point;
	struct __PointItem *next;
	struct __PointItem *last;
}PointItem_t;

using namespace Gdiplus;
/**
 * 每一组线的属性
 */
typedef struct __PointsGroupAttr{
    Color c;
	float  width;
}PointsGroupAttr_t;

/**
 * 所有线的组
 */
typedef struct __PointItemGroup{
    PointItem_t       *ptr;
	PointsGroupAttr_t  attr;
	struct __PointItemGroup *next;
	struct __PointItemGroup *last;
}PointItemGroup_t;

#endif