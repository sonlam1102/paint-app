#pragma once
#include"stdafx.h"
class Screen
{
	COLORREF **scr;
public:
	Screen();
	void getScreen(CDC *pDC);
	void setScreen(CDC *pDC);
	void release();
};