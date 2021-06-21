#pragma once


// CResDlg ��ȭ �����Դϴ�.
enum class RES_TYPE
{
	MESH,
	TEXTURE,
	MATERIAL,
	PREFAB,
	SOUND,
	CLONE,
	END
};


#include "TreeCtrlDlg.h"

class CResDlg : public CTreeCtrlDlg
{
	DECLARE_DYNAMIC(CResDlg)

public:
	CResDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CResDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESDLG };
#endif

private:
	HTREEITEM m_arrResRoot[(UINT)RES_TYPE::END];
	
	HTREEITEM m_hLBtnClickedItem;	 // ���� Ŭ���� ������
	HTREEITEM m_hRBtnClickedItem;     // ���� Ŭ���� ������

public:
	void UpdateTreeControl();
	virtual void Init();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnKeydownTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnResmenuDelete();
	virtual void OnOK();
	virtual void OnCancel();
};
