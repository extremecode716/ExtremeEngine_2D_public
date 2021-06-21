#pragma once
#include "afxwin.h"


// CComListDlg 대화 상자입니다.

class CComListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CComListDlg)

public:
	CComListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CComListDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMLISTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbCom;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};
