#pragma once
#include "afxcmn.h"

// CListDlg ��ȭ �����Դϴ�.
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
	CListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CListDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
