// ListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "ListDlg.h"
#include "afxdialogex.h"


#include "GameObject.h"
#include "ResMgr.h"
#include "Mesh.h"
#include "Material.h"


// CListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CListDlg, CDialogEx)

CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTDLG, pParent)
	, m_pTargetObj(NULL)
{

}

CListDlg::~CListDlg()
{
}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CListDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CListDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CListDlg 메시지 처리기입니다.
BOOL CListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (RESOURCE_TYPE::MESH == m_eType)
	{
		map<wstring, CResPtr<CMesh>>& mapMesh = CResMgr::GetInst()->GetMeshMap();
		map<wstring, CResPtr<CMesh>>::iterator iter = mapMesh.begin();

		m_vecText.reserve(mapMesh.size());

		for (int i = 0; iter != mapMesh.end(); ++iter, ++i)
		{
			m_vecText.push_back(iter->first.c_str());

			LVITEM tItem = {};
			tItem.iItem = i;
			tItem.pszText = m_vecText[i].GetBuffer();
			CRes* pRes = iter->second;
			tItem.lParam = (LPARAM)pRes;
			tItem.mask = LVIF_TEXT | LVIF_PARAM;

			m_ListCtrl.InsertItem(&tItem);
		}

	}
	else if (RESOURCE_TYPE::TEXTURE == m_eType)
	{
		map<wstring, CResPtr<CTexture>>& textMtrl = CResMgr::GetInst()->GetTextureMap();
		map<wstring, CResPtr<CTexture>>::iterator iter = textMtrl.begin();

		m_vecText.reserve(textMtrl.size());

		for (int i = 0; iter != textMtrl.end(); ++iter, ++i)
		{
			m_vecText.push_back(iter->first.c_str());

			LVITEM tItem = {};
			tItem.iItem = i;
			tItem.pszText = m_vecText[i].GetBuffer();
			CRes* pRes = iter->second;
			tItem.lParam = (LPARAM)pRes;
			tItem.mask = LVIF_TEXT | LVIF_PARAM;

			m_ListCtrl.InsertItem(&tItem);
		}
	}
	else if (RESOURCE_TYPE::MATERIAL == m_eType)
	{
		map<wstring, CResPtr<CMaterial>>& mapMtrl = CResMgr::GetInst()->GetMtrlMap();
		map<wstring, CResPtr<CMaterial>>::iterator iter = mapMtrl.begin();

		m_vecText.reserve(mapMtrl.size());

		for (int i = 0; iter != mapMtrl.end(); ++iter, ++i)
		{
			m_vecText.push_back(iter->first.c_str());

			LVITEM tItem = {};
			tItem.iItem = i;
			tItem.pszText = m_vecText[i].GetBuffer();
			CRes* pRes = iter->second;
			tItem.lParam = (LPARAM)pRes;
			tItem.mask = LVIF_TEXT | LVIF_PARAM;

			m_ListCtrl.InsertItem(&tItem);
		}
	}

	return TRUE;
}

void CListDlg::OnOK()
{
	int iIdx = m_ListCtrl.GetSelectionMark();

	if (-1 == iIdx)
	{

	}
	else
	{
		LPARAM lp = m_ListCtrl.GetItemData(iIdx);
		EndDialog(lp);
	}
}



void CListDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	EndDialog(NULL);
}

void CListDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnOK();

	*pResult = 0;
}
