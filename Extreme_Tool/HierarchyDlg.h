#pragma once


// CHierarchyDlg ��ȭ �����Դϴ�.
#include "TreeCtrlDlg.h"
#include "afxcmn.h"


class CGameObject;

class CHierarchyDlg : public CTreeCtrlDlg
{
	DECLARE_DYNAMIC(CHierarchyDlg)

public:
	CHierarchyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHierarchyDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIERARCHYDLG };
#endif

private:
	bool				m_bDragMouseResDlg; // ResDlg�� �巡�� ����
	CGameObject*		m_pDragGameObj;     // �巡�� ���� ������Ʈ

	HTREEITEM			m_hDragItem;		// �巡�� ���� ������
	HTREEITEM			m_hTargetItem;		// ������ ������
	HTREEITEM			m_hLBtnClickedItem;   // ���� Ŭ���� ������
	HTREEITEM			m_hRBtnClickedItem;   // ���� Ŭ���� ������

private:
	void UpdateTreeControl();
	void AddGameObject(CGameObject* _pObj, HTREEITEM _hParent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuAddprefab();
	afx_msg void OnMenuDelete();
	afx_msg void OnTvnKeydownTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
	virtual void OnCancel();
};
