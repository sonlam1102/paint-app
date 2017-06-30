#include "stdafx.h"
#include "C_FillColor.h"
#include <stack>

using namespace std;

C_FillColor::C_FillColor()
{
}
C_FillColor::~C_FillColor()
{
}
void C_FillColor::BoundaryFill(CDC *pDC, int x, int y, COLORREF color, COLORREF cursor_color)
{
	stack <CPoint> t1;
	if (pDC->GetPixel(x, y) != cursor_color)
		return;
	t1.push(CPoint(x, y));
	pDC->SetPixel(x, y, color);
	while (!t1.empty())
	{
		x = t1.top().x;
		y = t1.top().y;
		t1.pop();
		if ((pDC->GetPixel(x + 1, y) == cursor_color))
		{
			pDC->SetPixel(x + 1, y, color);
			t1.push(CPoint(x + 1, y));
		}
		//hướng bên trái
		if ((pDC->GetPixel(x - 1, y) == cursor_color))
		{
			pDC->SetPixel(x - 1, y, color);
			t1.push(CPoint(x - 1, y));
		}
		//hướng trên 
		if ((pDC->GetPixel(x, y + 1) == cursor_color))
		{
			pDC->SetPixel(x, y + 1, color);
			t1.push(CPoint(x, y + 1));
		}
		//hướng dưới
		if ((pDC->GetPixel(x, y - 1) == cursor_color))
		{
			pDC->SetPixel(x, y - 1, color);
			t1.push(CPoint(x, y - 1));
		}
	}
}
void Push(TStore &store, int x, int y)
{
	store.seed[store.n].x = x;
	store.seed[store.n].y = y;
	store.n++;
}

void Pop(TStore &store, int &x, int &y)
{
	store.n--;
	x = store.seed[store.n].x;
	y = store.seed[store.n].y;
}

int IsEmpty(TStore &store)
{
	return (store.n == 0);
}
