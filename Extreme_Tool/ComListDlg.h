#pragma once
#include "afxwin.h"


// CComListDlg ��ȭ �����Դϴ�.

class CComListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CComListDlg)

public:
	CComListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CComListDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMLISTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbCom;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};
