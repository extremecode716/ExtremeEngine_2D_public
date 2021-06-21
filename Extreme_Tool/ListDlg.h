#pragma once
#include "afxcmn.h"

// CListDlg 대화 상자입니다.
enum class RESOURCE_TYPE
{
	MESH,
	MATERIAL,
	TEXTURE,
	END,
};

class CGameObject;

class CListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListDlg)

	CGameObject* m_pTargetObj;

public:
	CListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CListDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl		m_ListCtrl;
	vector<CString> m_vecText;
	RESOURCE_TYPE	m_eType;



public:
	void InitTargetObj(CGameObject* _pTargetObj) {	m_pTargetObj = _pTargetObj; }
	void InitList(RESOURCE_TYPE _eType) { m_eType = _eType; }
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
