#pragma once


// CAnimatorDlg ��ȭ �����Դϴ�.
#include "ComponentDlg.h"
#include "afxwin.h"
#include "Animator.h"

class CAnimatorDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CAnimatorDlg)

public:
	CAnimatorDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAnimatorDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATORDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CMenu             m_CMenu;

	vector<tAnimPair> m_vecAnim;
	BOOL	  m_bRepeat;
	CComboBox m_cbAnim;
	bool m_bFocus_cb;
	int  m_iCurAnimIdx;

	CEdit m_EditTerm;
	bool  m_bFocus_Term;
	
public:
	virtual void UpdateComponent(CGameObject* _pObj);
	virtual void PostNcDestroy();
	afx_msg void OnAddBnClicked();
	afx_msg void OnBnClickedAnimRepeatCheck();
	afx_msg void OnCbnKillfocus();
	afx_msg void OnCbnSelchange();
	afx_msg void OnCbnSetfocus();
	afx_msg void OnSubComponentBnClicked();
	virtual BOOL OnInitDialog();
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnSetfocusAnimTerm();
	afx_msg void OnEnKillfocusAnimTerm();
	afx_msg void OnEnChangeAnimTerm();
};
