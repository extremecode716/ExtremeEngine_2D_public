#pragma once
#include "afxwin.h"



// CButtonView �� ���Դϴ�.
class CGameObject;

class CButtonView : public CFormView
{
	DECLARE_DYNCREATE(CButtonView)

protected:
	CButtonView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CButtonView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUTTONVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	CString m_strPathName;

	CGameObject*  m_pCameraObj;

public:
	void update();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_PlayButton;
	CButton m_PauseButton;
	CButton m_StopButton;
	afx_msg void OnBnClickedPlayButton();
	afx_msg void OnBnClickedPauseButton();
	afx_msg void OnBnClickedStopButton();
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


