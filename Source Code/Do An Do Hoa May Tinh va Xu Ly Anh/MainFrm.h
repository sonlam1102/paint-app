#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void SetColumns(int nCols, CToolBar &tbToolBox);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CStatusBar        m_wndStatusBar;   //Thanh Status
	CToolBar		  m_wndDrawToolBar;  //Thanh Draw
	CToolBar		  m_wndColorToolBar;  //Thanh chọn màu
	CToolBar		  m_wndPenToolBar;  //Thanh nét vẽ

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnViewBardraw();
};