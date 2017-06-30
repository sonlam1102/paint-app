#pragma once

#include"Definition.h"
#include"Screen.h"
#include<vector>
using namespace std;

class CPaintAppView : public CView
{
protected: // create from serialization only
	CPaintAppView();
	DECLARE_DYNCREATE(CPaintAppView)

// Attributes
public:
	CPaintAppDoc* GetDocument() const;

	//Các thiết bị đồ họa GDI
	CRect m_rect;
	CDC m_BG;
	CBitmap m_bmpBG;
	CDC m_VDC;
	CBitmap m_bmpVDC;
	void OnInitialUpdate();

	//vị trí con trỏ chuột ở các sự kiện click và màu, độ đậm, chế độ vẽ  tại thời điểm hiện tại 
	CPoint m_point_s;
	CPoint m_point_f;
	CPoint m_point_mid;
	float iRadius;
	COLORREF cCurrentColor;
	DRAWMODE dType;

	//Undo
	vector<Screen>vtAction;

	//Selection
	COLORREF **selectArea;
	int select_row, select_column;
	CPoint temp_s, temp_f;	

	//file name 
	CString FileName;
	HBITMAP hBitmap;

	//vị trí con trỏ chuột 
	CPoint CursorLocation;
	
	//dùng cho cọ vẽ
	int brushStyles = 4;
	int tag = -1;

	CPoint oldPoint = (0, 0);

	CDC *DC_Copy;
	CRect m_rect_value;

// Operations
public:
	void MakeDefaultApp();
	void ShowLocationMove(CDC *pDC, CPoint m_point);
	void removeSelected(CPoint x);
	void addAction();
	void setUndoAction();

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	
// Implementation
public:
	virtual ~CPaintAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateIdrIndicatorPos(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorPos(CCmdUI *pCmdUI);

	afx_msg void OnLine();   //Duong Thang
	afx_msg void OnLineUpdate(CCmdUI *pCmdUI);  //

	afx_msg void OnSquare();  //Square
	afx_msg void OnSquareUpdate(CCmdUI *pCmdUI);

	afx_msg void OnCircle();  //Circle
	afx_msg void OnCircleUpdate(CCmdUI *pCmdUI);

	afx_msg void OnRectangle();  //Rectangle
	afx_msg void OnRectangleUpdate(CCmdUI *pCmdUI);

	afx_msg void OnElip();
	afx_msg void OnElipUpdate(CCmdUI *pCmdUI);

	afx_msg void OnFillColor();   //Fill Color
	afx_msg void OnFillColorUpdate(CCmdUI *pCmdUI);

	afx_msg void OnDialogColor();   
	
	afx_msg void OnErase();   //Erase 
	afx_msg void OnEraseUpdate(CCmdUI *pCmdUI);

	afx_msg void OnEraseAll();   //Erase All

	//Colors 
	afx_msg void OnRed();
	afx_msg void OnBlue();
	afx_msg void OnGreen();
	afx_msg void OnBtn0255255();
	afx_msg void OnBtn0128128();
	afx_msg void OnBtn12800();
	afx_msg void OnBtn1281280();
	afx_msg void OnBlack();
	afx_msg void OnGray();
	afx_msg void OnPink();
	afx_msg void OnWhite();
	afx_msg void OnYellow();
	afx_msg void OnOrange();
	afx_msg void OnOrangeUpdate(CCmdUI *pCmdUI);
	afx_msg void OnPinkUpdate(CCmdUI *pCmdUI);
	afx_msg void OnRedUpdate(CCmdUI *pCmdUI);
	afx_msg void OnGreenUpdate(CCmdUI *pCmdUI);
	afx_msg void OnBtn0128128Update(CCmdUI *pCmdUI);
	afx_msg void OnBtn0255255Update(CCmdUI *pCmdUI);
	afx_msg void OnBtn12800Update(CCmdUI *pCmdUI);
	afx_msg void OnBtn1281280Update(CCmdUI *pCmdUI);
	afx_msg void OnBlackUpdate(CCmdUI *pCmdUI);
	afx_msg void OnBlueUpdate(CCmdUI *pCmdUI);
	afx_msg void OnGrayUpdate(CCmdUI *pCmdUI);
	afx_msg void OnWhiteUpdate(CCmdUI *pCmdUI);
	afx_msg void OnYellowUpdate(CCmdUI *pCmdUI);
	afx_msg void OnBtn1280128();
	afx_msg void OnBtn1280128Update(CCmdUI *pCmdUI);
	afx_msg void OnBtn128128128();
	afx_msg void OnBtn128128128Update(CCmdUI *pCmdUI);
	afx_msg void OnBtn00128();
	afx_msg void OnBtn00128Update(CCmdUI *pCmdUI);
	afx_msg void OnBtn01280();
	afx_msg void OnBtn01280Update(CCmdUI *pCmdUI);
	
	afx_msg void OnSelectUpdate(CCmdUI *pCmdUI);  //Select Object

	afx_msg void OnMove();  //Di chuyen
	afx_msg void OnCopy(); //Copy
	afx_msg void OnDelete();  //Delete Object

	afx_msg void OnSelect();     //Chon

	afx_msg void OnPencil();    //but ve
	afx_msg void OnPencilUpdate(CCmdUI *pCmdUI);

	afx_msg void OnBrush();    //co ve
	afx_msg void OnBrushUpdate(CCmdUI *pCmdUI);

	afx_msg void OnPencilSmallSize();    //net ve nho
	afx_msg void OnPencilSmallSizeUpdate(CCmdUI *pCmdUI);

	afx_msg void OnPencilMediumSize();    //net ve vua
	afx_msg void OnPencilMediumSizeUpdate(CCmdUI *pCmdUI);

	afx_msg void OnPencilLargeSize();    //net ve dam
	afx_msg void OnPencilLargeSizeUpdate(CCmdUI *pCmdUI);

	afx_msg void OnPencilVeryLargeSize();    //net rat ve dam
	afx_msg void OnPencilVeryLargeSizeUpdate(CCmdUI *pCmdUI);

	afx_msg void OnFileSave();      //Save File
	afx_msg void OnFileOpen();		//Open File

	afx_msg void OnUndo();	//Undo

	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in PaintAppView.cpp
inline CPaintAppDoc* CPaintAppView::GetDocument() const
   { return reinterpret_cast<CPaintAppDoc*>(m_pDocument); }
#endif

