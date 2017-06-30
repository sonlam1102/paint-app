#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "PaintApp.h"
#include "C_Line.h"
#include "C_Regtangle.h"
#include "C_Circle.h"
#include "C_Square.h"
#include "C_FillColor.h"
#include "C_Elip.h"

#endif
const int numUndo = 4;
//For save and open Action
#include <atlimage.h>
#include <Gdiplusimaging.h>

#include "PaintAppDoc.h"
#include "PaintAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \ on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
#endif

//const int backupTimes = 100;
//const int bitmapSize = 500;
const CSize bgSize = (1288, 604);
const int wWidth = 1288;
const int wHeight = 604;

IMPLEMENT_DYNCREATE(CPaintAppView, CView)

BEGIN_MESSAGE_MAP(CPaintAppView, CView)
	// Standard printing commands
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_POS, &CPaintAppView::OnUpdateIndicatorPos)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	

#pragma region Edit Command
	ON_COMMAND(ID_EDIT_UNDO, &CPaintAppView::OnUndo)
	ON_COMMAND(ID_EDIT_CUT, &CPaintAppView::OnMove)
	ON_COMMAND(ID_EDIT_COPY, &CPaintAppView::OnCopy)
	ON_COMMAND(ID_EDIT_DELETE, &CPaintAppView::OnDelete)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CPaintAppView::OnEraseAll)	

	ON_COMMAND(ID_BTN_SELECTION, &CPaintAppView::OnSelect)
	ON_UPDATE_COMMAND_UI(ID_BTN_SELECTION, &CPaintAppView::OnSelectUpdate)
#pragma endregion

#pragma region Draw Command
	ON_COMMAND(ID_BTN_LINE, &CPaintAppView::OnLine)
	ON_UPDATE_COMMAND_UI(ID_BTN_LINE, &CPaintAppView::OnLineUpdate)

	ON_COMMAND(ID_BTN_ERASE, &CPaintAppView::OnErase)
	ON_UPDATE_COMMAND_UI(ID_BTN_ERASE, &CPaintAppView::OnEraseUpdate)
	
	ON_COMMAND(ID_BTN_SQUARE, &CPaintAppView::OnSquare)
	ON_UPDATE_COMMAND_UI(ID_BTN_SQUARE, &CPaintAppView::OnSquareUpdate)

	ON_COMMAND(ID_BTN_ELIP, &CPaintAppView::OnElip)
	ON_UPDATE_COMMAND_UI(ID_BTN_ELIP, &CPaintAppView::OnElipUpdate)

	ON_COMMAND(ID_BTN_CIRCLE, &CPaintAppView::OnCircle)
	ON_UPDATE_COMMAND_UI(ID_BTN_CIRCLE, &CPaintAppView::OnCircleUpdate)
	ON_COMMAND(ID_BTN_REGTANGLE, &CPaintAppView::OnRectangle)
	ON_UPDATE_COMMAND_UI(ID_BTN_REGTANGLE, &CPaintAppView::OnRectangleUpdate)
	
	ON_COMMAND(ID_BTN_FILL_COLOR, &CPaintAppView::OnFillColor)
	ON_UPDATE_COMMAND_UI(ID_BTN_FILL_COLOR, &CPaintAppView::OnFillColorUpdate)

	ON_COMMAND(ID_BTN_PENCIL, &CPaintAppView::OnPencil)
	ON_UPDATE_COMMAND_UI(ID_BTN_PENCIL, &CPaintAppView::OnPencilUpdate)

	ON_COMMAND(ID_BTN_BRUSH, &CPaintAppView::OnBrush)
	ON_UPDATE_COMMAND_UI(ID_BTN_BRUSH, &CPaintAppView::OnBrushUpdate)
#pragma endregion

#pragma region PenStyle Command
	ON_COMMAND(ID_BTN_SMALL, &CPaintAppView::OnPencilSmallSize)
	ON_UPDATE_COMMAND_UI(ID_BTN_SMALL, &CPaintAppView::OnPencilSmallSizeUpdate)

	ON_COMMAND(ID_BTN_MEDIUM, &CPaintAppView::OnPencilMediumSize)
	ON_UPDATE_COMMAND_UI(ID_BTN_MEDIUM, &CPaintAppView::OnPencilMediumSizeUpdate)

	ON_COMMAND(ID_BTN_LARGE, &CPaintAppView::OnPencilLargeSize)
	ON_UPDATE_COMMAND_UI(ID_BTN_LARGE, &CPaintAppView::OnPencilLargeSizeUpdate)

	ON_COMMAND(ID_BTN_VERYLARGE, &CPaintAppView::OnPencilVeryLargeSize)
	ON_UPDATE_COMMAND_UI(ID_BTN_VERYLARGE, &CPaintAppView::OnPencilVeryLargeSizeUpdate)
#pragma endregion

#pragma region Color Command
	ON_COMMAND(ID_BTN_RED, &CPaintAppView::OnRed)
	ON_COMMAND(ID_BTN_BLUE, &CPaintAppView::OnBlue)
	ON_COMMAND(ID_BTN_GREEN, &CPaintAppView::OnGreen)
	ON_COMMAND(ID_BTN_0255255, &CPaintAppView::OnBtn0255255)
	ON_COMMAND(ID_BTN_0128128, &CPaintAppView::OnBtn0128128)
	ON_COMMAND(ID_BTN_12800, &CPaintAppView::OnBtn12800)
	ON_COMMAND(ID_BTN_1281280, &CPaintAppView::OnBtn1281280)
	ON_COMMAND(ID_BTN_BLACK, &CPaintAppView::OnBlack)
	ON_COMMAND(ID_BTN_GRAY, &CPaintAppView::OnGray)
	ON_COMMAND(ID_BTN_PINK, &CPaintAppView::OnPink)
	ON_COMMAND(ID_BTN_WHITE, &CPaintAppView::OnWhite)
	ON_COMMAND(ID_BTN_YELLOW, &CPaintAppView::OnYellow)
	ON_COMMAND(ID_BTN_ORANGE, &CPaintAppView::OnOrange)
	ON_COMMAND(ID_BTN_DIALOG_COLOR, &CPaintAppView::OnDialogColor)
	ON_UPDATE_COMMAND_UI(ID_BTN_PINK, &CPaintAppView::OnPinkUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_ORANGE, &CPaintAppView::OnOrangeUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_RED, &CPaintAppView::OnRedUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_GREEN, &CPaintAppView::OnGreenUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_0128128, &CPaintAppView::OnBtn0128128Update)
	ON_UPDATE_COMMAND_UI(ID_BTN_0255255, &CPaintAppView::OnBtn0255255Update)
	ON_UPDATE_COMMAND_UI(ID_BTN_12800, &CPaintAppView::OnBtn12800Update)
	ON_UPDATE_COMMAND_UI(ID_BTN_1281280, &CPaintAppView::OnBtn1281280Update)
	ON_UPDATE_COMMAND_UI(ID_BTN_BLACK, &CPaintAppView::OnBlackUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_BLUE, &CPaintAppView::OnBlueUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_GRAY, &CPaintAppView::OnGrayUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_WHITE, &CPaintAppView::OnWhiteUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_YELLOW, &CPaintAppView::OnYellowUpdate)
	ON_COMMAND(ID_BTN_1280128, &CPaintAppView::OnBtn1280128)
	ON_UPDATE_COMMAND_UI(ID_BTN_1280128, &CPaintAppView::OnBtn1280128Update)
	ON_COMMAND(ID_BTN_128128128, &CPaintAppView::OnBtn128128128)
	ON_UPDATE_COMMAND_UI(ID_BTN_128128128, &CPaintAppView::OnBtn128128128Update)
	ON_COMMAND(ID_BTN_00128, &CPaintAppView::OnBtn00128)
	ON_UPDATE_COMMAND_UI(ID_BTN_00128, &CPaintAppView::OnBtn00128Update)
	ON_COMMAND(ID_BTN_01280, &CPaintAppView::OnBtn01280)
	ON_UPDATE_COMMAND_UI(ID_BTN_01280, &CPaintAppView::OnBtn01280Update)
#pragma endregion

#pragma region File Command
	ON_COMMAND(ID_FILE_SAVE, &CPaintAppView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CPaintAppView::OnFileOpen)
#pragma endregion

	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPaintAppView construction/destruction

CPaintAppView::CPaintAppView()
{
	MakeDefaultApp();
}

CPaintAppView::~CPaintAppView()
{
}

BOOL CPaintAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CPaintAppView drawing
void CPaintAppView::OnDraw(CDC* pDC)
{
	CPaintAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->BitBlt(0, 0, wWidth, wHeight, &m_VDC, 0, 0, SRCCOPY);
	
}

// CPaintAppView diagnostics

#ifdef _DEBUG
void CPaintAppView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintAppDoc* CPaintAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintAppDoc)));
	return (CPaintAppDoc*)m_pDocument;
}

#endif //_DEBUG

#pragma region Class Method
void CPaintAppView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	GetClientRect(&m_rect);
	CClientDC dc(this);
	
	m_BG.CreateCompatibleDC(&dc);
	m_bmpBG.CreateCompatibleBitmap(&dc, wWidth, wHeight);
	m_BG.SelectObject(&m_bmpBG);

	m_VDC.CreateCompatibleDC(&dc);
	m_bmpVDC.CreateCompatibleBitmap(&dc, wWidth, wHeight);
	m_VDC.SelectObject(&m_bmpVDC);

	m_BG.FillSolidRect(0, 0, wWidth, wHeight, RGB(255, 255, 255));
	m_VDC.FillSolidRect(0, 0, wWidth, wHeight, RGB(255, 255, 255));
	hBitmap = ::CreateCompatibleBitmap(m_BG, bgSize.cx, bgSize.cy);
	
}
void CPaintAppView::OnUpdateIndicatorPos(CCmdUI *pCmdUI)
{
	CString strPos;
	strPos.Format(_T("Location of Cursor(X: %d,Y: %d)"), CursorLocation.x, CursorLocation.y);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(strPos);
}
void CPaintAppView::ShowLocationMove(CDC *pDC, CPoint m_point)
{
	pDC->SetPixel(m_point, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x, m_point.y + 1, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x, m_point.y - 1, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x + 1, m_point.y, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x - 1, m_point.y, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x + 1, m_point.y + 1, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x - 1, m_point.y - 1, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x + 1, m_point.y - 1, RGB(255, 0, 0));
	pDC->SetPixel(m_point.x - 1, m_point.y + 1, RGB(255, 0, 0));
}
void CPaintAppView::OnDestroy()
{
	CView::OnDestroy();
	m_BG.DeleteDC();
	m_VDC.DeleteDC();
	m_bmpBG.DeleteObject();
	m_bmpVDC.DeleteObject();
	for (int i = 0; i < vtAction.size(); i++)
		vtAction[i].release();
	vtAction.clear();
}
void CPaintAppView::removeSelected(CPoint x)
{
	int tempX = x.x;
	int tempY = x.y;
	for (int i = 0; i <= select_row; i++)
	{
		tempX = x.x;
		for (int j = 0; j <= select_column; j++)
		{
			m_BG.SetPixel(tempX, tempY, RGB(255, 255, 255));
			tempX++;
		}
		tempY++;
	}
}
#pragma endregion

#pragma region MOUSE EVENT
void CPaintAppView::OnLButtonDown(UINT nFlags, CPoint point)
{

	m_point_s = m_point_f = point;
	if (dType == FILL_COLOR)
	{
		addAction();
		C_FillColor *p1 = new C_FillColor;
		p1->BoundaryFill(&m_BG, m_point_s.x, m_point_s.y, cCurrentColor, m_BG.GetPixel(point));
		delete p1;
	}
	if (dType == MOVE)
	{
		addAction();
		int tempX = point.x;
		int tempY = point.y;
		for (int i = 0; i <= select_row; i++)
		{
			tempX = point.x;
			for (int j = 0; j <= select_column; j++)
			{
				m_BG.SetPixel(tempX, tempY, selectArea[i][j]);
				tempX++;
			}
			tempY++;
		}
		removeSelected(temp_s);
		temp_s = point;
	}
	if (dType == COPY)
	{
		addAction();
		int tempX = point.x;
		int tempY = point.y;
		for (int i = 0; i <= select_row; i++)
		{
			tempX = point.x;
			for (int j = 0; j <= select_column; j++)
			{
				m_BG.SetPixel(tempX, tempY, selectArea[i][j]);
				tempX++;
			}
			tempY++;
		}		
		temp_s = point;
	}
	if (dType == DEL)
	{
		addAction();
		removeSelected(temp_s);
		temp_s = point;
	}
	CView::OnLButtonDown(nFlags, point);
}
void CPaintAppView::OnLButtonUp(UINT nFlags, CPoint point)
{		
		m_point_f = point;
		switch (dType)
		{
		case (LINE) :
		{
			addAction();
			C_Line *p1 = new C_Line;
			p1->DrawLine(&m_BG, m_point_s, m_point_f, cCurrentColor);
			delete p1;
			break;
		}
		case (REGTANGLE) :
		{
			addAction();
			C_Regtangle *p1 = new C_Regtangle;
			p1->DrawRectangle(&m_BG, m_point_s, m_point_f, cCurrentColor);
			delete p1;
			break;
		}
		case(CIRCLE) :
		{
			addAction();
			m_point_mid.x = (m_point_s.x + m_point_f.x) / 2;
			m_point_mid.y = (m_point_s.y + m_point_f.y) / 2;
			iRadius = sqrt((float)(m_point_f.x - m_point_mid.x)*(m_point_f.x - m_point_mid.x) + (float)(m_point_f.y - m_point_mid.y)*(m_point_f.y - m_point_mid.y));
			C_Circle *p1 = new C_Circle;
			p1->DrawCircle(&m_BG, m_point_mid, iRadius, cCurrentColor);
			delete p1;
			break;
		}
		case (SQUARE) :
		{
			addAction();
			C_Square *p1 = new C_Square;
			p1->Draw_Square(&m_BG, m_point_s, m_point_f, cCurrentColor);
			delete p1;
			break;
		}

		case(ELIP) :
		{
			addAction();
			C_Elip *el = new C_Elip;
			el->DrawElip(&m_BG, m_point_s, m_point_f, cCurrentColor);
			delete el;
			break;
		}
		case (ERASE_ALL) :
		{
			addAction();
			m_BG.FillSolidRect(0, 0, wWidth, wHeight, RGB(255, 255, 255));
			break;
		}
		case (SELECT) :
		{
			selectArea = new COLORREF*[select_row];
			for (int i = 0; i <= select_row; i++)
				selectArea[i] = new COLORREF[select_column];
			int tempX = temp_s.x;
			int tempY = temp_s.y;
			for (int i = 0; i <= select_row; i++)
			{
				tempX = temp_s.x;
				for (int j = 0; j <= select_column; j++)
				{
					selectArea[i][j] = m_BG.GetPixel(tempX, tempY);
					tempX++;
				}
				tempY++;
			}
			break;
		}

		default:
			break;
		}
			
	m_VDC.BitBlt(0, 0, wWidth, wHeight, &m_BG, 0, 0, SRCCOPY);
	Invalidate(false);
	CView::OnLButtonUp(nFlags, point);
}

void CPaintAppView::OnMouseMove(UINT nFlags, CPoint point)
{
	CursorLocation = point;
	oldPoint = m_point_f;
	if (nFlags && MK_LBUTTON )
	{			
		m_point_f = point;
		m_VDC.BitBlt(0, 0, wWidth, wHeight, &m_BG, 0, 0, SRCCOPY);
		switch (dType)
		{
		case (LINE):
		{
			ShowLocationMove(&m_VDC, m_point_s);
			ShowLocationMove(&m_VDC, point);
			C_Line *p1 = new C_Line;
			p1->DrawLine(&m_VDC, m_point_s, point, cCurrentColor);
			delete p1;
			break;
		}
		case (PENCIL):
		{
			ShowLocationMove(&m_VDC, point);			
			C_Line *line = new C_Line;
			line->DrawLine(&m_BG, oldPoint, point, cCurrentColor);
			oldPoint = point;
			delete line;
			break;
		}
		case (BRUSH) :
		{
			ShowLocationMove(&m_VDC, point);
			m_BG.FillSolidRect(point.x,point.y,brushStyles,brushStyles, cCurrentColor);
			break;
		}
		case (REGTANGLE):
		{
			ShowLocationMove(&m_VDC, m_point_s);
			ShowLocationMove(&m_VDC, point);
			C_Regtangle *p1 = new C_Regtangle;
			p1->DrawRectangle(&m_VDC, m_point_s, point, cCurrentColor);
			delete p1;
			break;
		}
		case(CIRCLE) :
		{
			ShowLocationMove(&m_VDC, m_point_s);
			ShowLocationMove(&m_VDC, point);
			m_point_mid.x = (m_point_s.x + m_point_f.x) / 2;
			m_point_mid.y = (m_point_s.y + m_point_f.y) / 2;
			ShowLocationMove(&m_VDC, m_point_mid);
			iRadius = sqrt((float)(m_point_f.x - m_point_mid.x)*(m_point_f.x - m_point_mid.x) + (float)(m_point_f.y - m_point_mid.y)*(m_point_f.y - m_point_mid.y));
			C_Circle *p1 = new C_Circle;
			p1->DrawCircle(&m_VDC, m_point_mid, iRadius, cCurrentColor);
			delete p1;
			break;
		}
		case (SQUARE) :
		{
			ShowLocationMove(&m_VDC, m_point_s);
			ShowLocationMove(&m_VDC, point);
			C_Square *p1 = new C_Square;
			p1->Draw_Square(&m_VDC, m_point_s, m_point_f, cCurrentColor);
			delete p1;
			break;
		}
		case (ELIP):
		{
			ShowLocationMove(&m_VDC, m_point_s);
			ShowLocationMove(&m_VDC, point);
			C_Elip *el = new C_Elip;
			el->DrawElip(&m_VDC, m_point_s, m_point_f, cCurrentColor);
			delete el;
			break;
		}
		case (ERASE) :
		{
			ShowLocationMove(&m_VDC, point);
			m_BG.FillSolidRect(point.x, point.y, brushStyles, brushStyles, RGB(255, 255, 255));
			break;
		}
		case (SELECT) :
		{
			ShowLocationMove(&m_VDC, m_point_s);
			ShowLocationMove(&m_VDC, point);
			C_Regtangle *p1 = new C_Regtangle;
			p1->DrawRectangle(&m_VDC, m_point_s, point, (0,0,0));
			select_column = abs((point.x - m_point_s.x));
			select_row = abs((point.y - m_point_s.y));
			temp_s = m_point_s;
			temp_f = m_point_f;
			delete p1; 
			break;
		}
		default:
			break;
		}
		
		Invalidate(false);
	}
	CView::OnMouseMove(nFlags, point);
}
#pragma endregion


#pragma region Drawing Tool
void CPaintAppView::OnLine()
{
	dType = LINE;
}
void CPaintAppView::OnLineUpdate(CCmdUI *pCmdUI)
{
	if (dType == LINE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnSquare()
{
	dType = SQUARE;
}
void CPaintAppView::OnSquareUpdate(CCmdUI *pCmdUI)
{
	if (dType == SQUARE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnCircle()
{
	dType = CIRCLE;
}
void CPaintAppView::OnCircleUpdate(CCmdUI *pCmdUI)
{
	if (dType == CIRCLE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnRectangle()
{
	dType = REGTANGLE;
}
void CPaintAppView::OnRectangleUpdate(CCmdUI *pCmdUI)
{
	if (dType == REGTANGLE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnElip()
{
	dType = ELIP;
}
void CPaintAppView::OnElipUpdate(CCmdUI *pCmdUI)
{
	if (dType == ELIP)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPaintAppView::OnFillColor()
{
	dType = FILL_COLOR;
}
void CPaintAppView::OnFillColorUpdate(CCmdUI *pCmdUI)
{
	if (dType == FILL_COLOR)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnPencil()
{
	addAction();
	dType = PENCIL;
}
void CPaintAppView::OnPencilUpdate(CCmdUI *pCmdUI)
{
	if (dType == PENCIL)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBrush()
{
	addAction();
	dType = BRUSH;
}
void CPaintAppView::OnBrushUpdate(CCmdUI *pCmdUI)
{
	if (dType == BRUSH)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPaintAppView::OnErase()
{
	addAction();
	dType = ERASE;
}
void CPaintAppView::OnDelete()
{
	addAction();
	dType = DEL;
}
void CPaintAppView::OnEraseUpdate(CCmdUI *pCmdUI)
{
	if (dType == ERASE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
#pragma endregion 


#pragma region Edit Tool
void CPaintAppView::OnEraseAll()
{
	dType = NONE;
	dType = ERASE_ALL;
}
void CPaintAppView::OnMove()
{
	dType = MOVE;
}
void CPaintAppView::OnCopy()
{
	dType = COPY;
}

void CPaintAppView::OnSelect()
{
	dType = SELECT;
}
void CPaintAppView::OnSelectUpdate(CCmdUI *pCmdUI)
{
	if (dType == SELECT)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
#pragma endregion


#pragma region Color Tool
void CPaintAppView::MakeDefaultApp()
{
	cCurrentColor = RGB(0, 0, 0);
}
void CPaintAppView::OnRed()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(255, 0, 0);
}

void CPaintAppView::OnBlue()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(0, 0, 255);
}

void CPaintAppView::OnGreen()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(0, 255, 0);
}

void CPaintAppView::OnBtn0255255()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(0, 255, 255);
}

void CPaintAppView::OnBtn0128128()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(0, 128, 128);
}

void CPaintAppView::OnBtn12800()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(128, 0, 0);
}

void CPaintAppView::OnBtn1281280()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(128, 128, 0);
}

void CPaintAppView::OnBlack()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(0, 0, 0);
}

void CPaintAppView::OnGray()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(128, 128, 128);
}

void CPaintAppView::OnPink()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(255, 0, 255);
}

void CPaintAppView::OnWhite()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(255, 255, 255);
}

void CPaintAppView::OnYellow()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(255, 255, 0);
}
void CPaintAppView::OnOrange()
{
	cCurrentColor = RGB(255, 69, 0);
}
void CPaintAppView::OnPinkUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(255, 0, 255))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnRedUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(255, 0, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnGreenUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(0, 255, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn0128128Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(0, 128, 128))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn0255255Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(0, 255, 255))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn12800Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(128, 0, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn1281280Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(128, 128, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBlackUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(0, 0, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBlueUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(0, 0, 255))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnGrayUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(128, 128, 128))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnWhiteUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(255, 255, 255))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnYellowUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(255, 255, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn1280128()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(128, 0, 128);
}
void CPaintAppView::OnBtn1280128Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(128, 0, 128))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn128128128()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(192, 192, 192);
}
void CPaintAppView::OnBtn128128128Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(192, 192, 192))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn00128()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(0, 0, 128);
}
void CPaintAppView::OnBtn00128Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(0, 0, 128))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnBtn01280()
{
	// TODO: Add your command handler code here
	cCurrentColor = RGB(0, 128, 0);
}
void CPaintAppView::OnBtn01280Update(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(0, 128, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnOrangeUpdate(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (cCurrentColor == RGB(255, 69, 0))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnDialogColor()
{
	// TODO: Add your command handler code here
	CColorDialog p1;
	int iRes = p1.DoModal();
	if (iRes == IDOK)
	{
		cCurrentColor = p1.GetColor();
	}
}
#pragma endregion


#pragma region File Action
void CPaintAppView::OnFileSave()
{
	CFileDialog saveFile(FALSE, L"*.bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, L"bitmap(*.bmp)|*.bmp||");
	if (saveFile.DoModal() == IDOK)
	{
		FileName = saveFile.GetPathName();
		CImage image;
		image.Create(wWidth,wHeight, 32);

		for (int i = 0; i < wWidth; i++)
			for (int j = 0; j < wHeight; j++)
				image.SetPixel(i, j, m_BG.GetPixel(i, j));
		image.Save(_T("" + FileName));
	}
}

void CPaintAppView::OnFileOpen()
{
	CFileDialog openFile(TRUE, L"*.bmp", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, L"bitmap(*.bmp)|*.bmp||");
	if (openFile.DoModal() == IDOK)
	{		
		FileName = openFile.GetPathName();

		CImage image;
		image.Load(_T("" + FileName));
		for (int i = 0; i < image.GetWidth(); i++)
			for (int j = 0; j < image.GetHeight(); j++)
				m_BG.SetPixel(i, j, image.GetPixel(i, j));	
	}
}
#pragma endregion


#pragma region Undo Action
void CPaintAppView::OnUndo()
{
	dType = NONE;
	setUndoAction();
}
void CPaintAppView::addAction()
{
	int count = vtAction.size();
	if (count < numUndo)
	{
		Screen scr;
		scr.getScreen(&m_BG);
		vtAction.push_back(scr);
	}
	else
	{
		vtAction[0].release();
		vtAction.erase(vtAction.begin());
		Screen scr;
		scr.getScreen(&m_BG);
		vtAction.push_back(scr);
	}
}
void CPaintAppView::setUndoAction()
{
	if (vtAction.size()>0)
	{
		Screen scr;
		scr = vtAction[vtAction.size() - 1];
		scr.setScreen(&m_BG);
		vtAction[vtAction.size() - 1].release();
		vtAction.pop_back();
	}
}
#pragma endregion


#pragma region PenStyles
void CPaintAppView::OnPencilSmallSize()
{
	this->brushStyles = 4;
	this->tag = -1;
}
void CPaintAppView::OnPencilSmallSizeUpdate(CCmdUI *pCmdUI)
{
	if (tag == -1 && (dType == BRUSH || dType == ERASE))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnPencilMediumSize()
{
	this->brushStyles = 6;
	this->tag = 1;
}
void CPaintAppView::OnPencilMediumSizeUpdate(CCmdUI *pCmdUI)
{
	if (tag == 1 && (dType == BRUSH || dType == ERASE))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnPencilLargeSize()
{
	this->brushStyles = 8;
	this->tag = 2;
}
void CPaintAppView::OnPencilLargeSizeUpdate(CCmdUI *pCmdUI)
{
	if (tag == 2 && (dType == BRUSH || dType == ERASE))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
void CPaintAppView::OnPencilVeryLargeSize()
{
	this->brushStyles = 10;
	this->tag = 3;
}
void CPaintAppView::OnPencilVeryLargeSizeUpdate(CCmdUI *pCmdUI)
{
	if (tag == 3 && (dType == BRUSH || dType == ERASE))
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
#pragma endregion