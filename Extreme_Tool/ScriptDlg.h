#pragma once


// CScriptDlg ��ȭ �����Դϴ�.
#include "ComponentDlg.h"
#include "afxwin.h"

class CScriptDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CScriptDlg)

public:
	CScriptDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CScriptDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCRIPTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CMenu      m_CMenu1;
	CComboBox  m_cbScript;
	CListBox   m_List;

	bool	   m_bFocusList;

	int		   m_iScriptIdx;

public:
	afx_msg void OnAddScript();
	//afx_msg void OnSubComponentBnClicked();
	virtual void UpdateComponent(CGameObject* _pObj);
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();

	void UpdateList();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnScriptmenuDelete();
	afx_msg void OnLbnKillfocusList1();
	afx_msg void OnLbnSetfocusList1();
};
