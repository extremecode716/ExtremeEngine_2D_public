#pragma once


// CColliderDlg ��ȭ �����Դϴ�.
#include "ComponentDlg.h"
#include "afxwin.h"


class CColliderDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CColliderDlg)

public:
	CColliderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CColliderDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLIDERDLG };
#endif
public:
	virtual void UpdateComponent(CGameObject* _pObj);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
