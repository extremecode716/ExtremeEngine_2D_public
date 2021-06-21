#pragma once


// CColliderDlg 대화 상자입니다.
#include "ComponentDlg.h"
#include "afxwin.h"


class CColliderDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CColliderDlg)

public:
	CColliderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CColliderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLIDERDLG };
#endif
public:
	virtual void UpdateComponent(CGameObject* _pObj);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual void PostNcDestroy();
public:
	CEdit   m_arrEdit[2][3];
	bool    m_bFocus[2][3];
	DECLARE_MESSAGE_MAP()

	afx_msg void OnEnSetfocus(UINT _id);
	afx_msg void OnEnKillfocus(UINT _id);
	afx_msg void OnEnChange(UINT _id);
	afx_msg void OnSubComponentBnClicked();
};
