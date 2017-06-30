#pragma once

struct TSeed 
{
	int x;
	int y;
};
struct TStore 
{
	int n;
	TSeed seed[1024];
};
class C_FillColor
{
public:
	C_FillColor();
	~C_FillColor();
	void BoundaryFill(CDC *pDC, int x, int y, COLORREF color, COLORREF cursor_color);
};

