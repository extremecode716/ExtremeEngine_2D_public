// AddAnimDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "AddAnimDlg.h"
#include "afxdialogex.h"

#include "PathMgr.h"

#include "GameObject.h"
#include "Animator.h"
#include "Animation_2D.h"

// CAddAnimDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddAnimDlg, CDialogEx)

CAddAnimDlg::CAddAnimDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDANIMDLG, pParent)
	, m_strTexName(_T(""))
	, m_strAnimName(_T(""))
	, m_bContinue(TRUE)
{
}

CAddAnimDlg::~CAddAnimDlg()
{
}

void CAddAnimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT1, m_strTexName);
	DDX_Text(pDX, IDC_EDIT2, m_strAnimName);
	DDX_Check(pDX, IDC_CHECK1, m_bContinue);
	DDX_Control(pDX, IDC_EDIT3, m_editTexCount);
	DDX_Control(pDX, IDC_EDIT4, m_editLT);
	DDX_Control(pDX, IDC_EDIT5, m_editRT);
	DDX_Control(pDX, IDC_EDIT7, m_editSizeX);
	DDX_Control(pDX, IDC_EDIT8, m_editSizeY);
	DDX_Control(pDX, IDC_EDIT10, m_editFrameCount);

}


BEGIN_MESSAGE_MAP(CAddAnimDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CAddAnimDlg::OnNMClickList)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddAnimDlg::OnBnClicked)
	ON_BN_CLICKED(IDC_CHECK1, &CAddAnimDlg::OnContinueBnClicked)
END_MESSAGE_MAP()


// CAddAnimDlg �޽��� ó�����Դϴ�.



BOOL CAddAnimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_editTexCount.SendMessage(EM_SETREADONLY, 1, 0);

	SetContinue(m_bContinue);
	return TRUE;
}

void CAddAnimDlg::OnOK()
{
	if (NULL != m_pTarget && m_strTexName.Compare(L""))
	{
		UpdateData(true);

		tDescInfo info = {};
		info.strTexName = m_strTexName;
		info.strAnimName = m_strAnimName;
		info.iContinue = m_bContinue;

		CString str;
		if (m_bContinue)
		{
			m_editTexCount.GetWindowTextW(str);
			info.iFrameCount = _wtoi(str);
		}
		else
		{
			m_editFrameCount.GetWindowTextW(str);
			info.iFrameCount = _wtoi(str);

			m_editLT.GetWindowTextW(str);
			info.vLeftTop.x = (float)_wtof(str);

			m_editRT.GetWindowTextW(str);
			info.vLeftTop.y = (float)_wtof(str);

			m_editSizeX.GetWindowTextW(str);
			info.vSize.x = (float)_wtof(str);

			m_editSizeY.GetWindowTextW(str);
			info.vSize.y = (float)_wtof(str);
		}
		m_pTarget->Animator()->LoadAnimation_2D(&info, m_strFolderPath.GetBuffer());
	}

	CDialogEx::OnOK();
}

void CAddAnimDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	INT iIDx = m_List.GetSelectionMark();

	if (-1 != iIDx)
	{
		m_strTexName = m_List.GetItemText(iIDx, 0);
		UpdateData(false);
	}

	*pResult = 0;
}

// CAddAnimDlg message handlers // ��� ���ν����� ����ä�� ���� ���� �� �ֱ� ���� ���ν���.
int CALLBACK Proc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	// �ʱ�ȭ �Ҷ� �޼����� ����è
	if (uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	return 0;
}

void CAddAnimDlg::OnBnClicked()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ���� ���� ���̾�α�
	BROWSEINFO br = {};

	br.lpfn = Proc; // ���ν��� �ݹ��Լ��� ���� ���־� ���۰�θ� ���� �Ѵ�.

	CString strFolderInitPath = CPathMgr::GetResPath();
	strFolderInitPath += L"Texture\\Animation";
	br.lParam = (LPARAM)strFolderInitPath.GetBuffer();
	br.ulFlags = BIF_USENEWUI;		  // ������
	br.hwndOwner = m_hWnd;			 // �ڵ� ������ ����(�θ�)
	br.lpszTitle = L"���� ����";	 // â �̸�

	LPITEMIDLIST pidl = NULL;     // ���� �� �� ��ο� ����
	if ((pidl = SHBrowseForFolder(&br)) != NULL)  // ���� ���� â. (���� �� ��θ� ã�Ƽ� �������ش�)
	{
		wchar_t buffer[MAX_PATH];
		if (SHGetPathFromIDList(pidl, buffer))
			m_strFolderPath = buffer;
	}

	WIN32_FIND_DATA tData = {};

	HANDLE hHandle = FindFirstFile(wstring(m_strFolderPath + L"\\" + L"*.*").c_str(), &tData);

	m_List.DeleteAllItems();
	int iIDx = 0;

	do
	{
		CString strEXT = CPathMgr::GetExt(tData.cFileName);

		if (strEXT != L".png" && strEXT != L".jpg" && strEXT != L".jpeg" && strEXT != L".bmp" && strEXT != L".gif")
			continue;

		m_List.InsertItem(iIDx++, tData.cFileName);

	} while (FindNextFile(hHandle, &tData));

	FindClose(hHandle);
}


void CAddAnimDlg::OnContinueBnClicked()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_bContinue)
		m_bContinue = false;
	else
		m_bContinue = true;


	SetContinue(m_bContinue);
}

void CAddAnimDlg::SetContinue(BOOL _bContinue)
{
	// ���� �ؽ���->
	if (m_bContinue)
	{
		// Ȱ��ȭ
		m_editTexCount.SendMessage(EM_SETREADONLY, 0, 0);

		// ��Ȱ��ȭ
		m_editLT.SendMessage(EM_SETREADONLY, 1, 0);
		m_editRT.SendMessage(EM_SETREADONLY, 1, 0);
		m_editSizeX.SendMessage(EM_SETREADONLY, 1, 0);
		m_editSizeY.SendMessage(EM_SETREADONLY, 1, 0);
		m_editFrameCount.SendMessage(EM_SETREADONLY, 1, 0);
	}
	else //���� �ؽ���->
	{
		// ��Ȱ��ȭ
		m_editTexCount.SendMessage(EM_SETREADONLY, 1, 0);

		// Ȱ��ȭ
		m_editLT.SendMessage(EM_SETREADONLY, 0, 0);
		m_editRT.SendMessage(EM_SETREADONLY, 0, 0);
		m_editSizeX.SendMessage(EM_SETREADONLY, 0, 0);
		m_editSizeY.SendMessage(EM_SETREADONLY, 0, 0);
		m_editFrameCount.SendMessage(EM_SETREADONLY, 0, 0);
	}
}