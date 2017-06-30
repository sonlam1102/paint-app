
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PaintApp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_BARDRAW, &CMainFrame::OnViewBardraw)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_POS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//tạo status bar	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_POS, SBPS_NORMAL, 180);

	//tạo color bar ở dưới 
	if (!m_wndColorToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED)
		|| !m_wndColorToolBar.LoadToolBar(IDR_COLOR_TOOLBAR))
	{
		return -1;
	}
	m_wndColorToolBar.SetBarStyle(m_wndColorToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);
	m_wndColorToolBar.SetButtonStyle(1, m_wndColorToolBar.GetButtonStyle(1) | TBBS_WRAPPED);
	
	m_wndColorToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndColorToolBar, AFX_IDW_DOCKBAR_BOTTOM);
	SetColumns(9, m_wndColorToolBar);
	
	//tạo Draw toolbar bên tay trái 
	if (!m_wndDrawToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED)
		|| !m_wndDrawToolBar.LoadToolBar(IDR_DRAW_TOOLBAR))
	{
		return -1;
	}
	m_wndDrawToolBar.SetBarStyle(m_wndDrawToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);
	m_wndDrawToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_LEFT);
	DockControlBar(&m_wndDrawToolBar, AFX_IDW_DOCKBAR_LEFT);
	SetColumns(2, m_wndDrawToolBar);

	// penstyles tool bar 
	if (!m_wndPenToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED)
		|| !m_wndPenToolBar.LoadToolBar(IDR_PEN_TOOLBAR))
	{
		return -1;
	}
	m_wndPenToolBar.SetBarStyle(m_wndPenToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);
	m_wndPenToolBar.SetButtonStyle(1, m_wndPenToolBar.GetButtonStyle(1) | TBBS_WRAPPED);
	m_wndPenToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndPenToolBar, AFX_IDW_DOCKBAR_RIGHT);
	SetColumns(1, m_wndPenToolBar);

	
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnViewBardraw()
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::SetColumns(int nCols, CToolBar& tbToolBox)
{
	int nColumns = nCols;
	int nCount = tbToolBox.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		UINT nStyle = tbToolBox.GetButtonStyle(i);
		BOOL bWrap = (((i + 1) % nColumns) == 0);
		if (bWrap)
			nStyle |= TBBS_WRAPPED;
		else
			nStyle &= ~TBBS_WRAPPED;
		tbToolBox.SetButtonStyle(i, nStyle);
	}
	RecalcLayout();  Invalidate();
}

