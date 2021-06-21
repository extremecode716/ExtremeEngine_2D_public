#pragma once
#include "afxwin.h"

// CComponentView 폼 뷰입니다.

class CComponentDlg;
class CGameObject;

class CComponentView : public CFormView
{
	DECLARE_DYNCREATE(CComponentView)

protected:
	CComponentView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CComponentView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPONENTVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

private:
	CGameObject*	m_pTargetObj;
	CComponentDlg* m_arrDlg[(UINT)COMPONENT_TYPE::END];

public:
	void SetTarget(CGameObject* _pTarget) { m_pTargetObj = _pTarget; }
	void InitTarget();

public:
	void UpdateComponent(CGameObject* _pObj);
	void update();

	CButton m_bnAC;
	afx_msg void OnAddComBnClicked();

//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//virtual void OnInitialUpdate();

};


