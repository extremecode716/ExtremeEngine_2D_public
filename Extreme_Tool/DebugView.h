#pragma once
#include "afxwin.h"



// CDebugView �� ���Դϴ�.

class CDebugView : public CFormView
{
	DECLARE_DYNCREATE(CDebugView)

protected:
	CDebugView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CDebugView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEBUGVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	CBrush  m_Brush;

public:
	void AddLog(DWORD_PTR _pLog);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_LogBox;
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


