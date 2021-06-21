// AddAnimDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "AddAnimDlg.h"
#include "afxdialogex.h"

#include "PathMgr.h"

#include "GameObject.h"
#include "Animator.h"
#include "Animation_2D.h"

// CAddAnimDlg 대화 상자입니다.

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


// CAddAnimDlg 메시지 처리기입니다.



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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	INT iIDx = m_List.GetSelectionMark();

	if (-1 != iIDx)
	{
		m_strTexName = m_List.GetItemText(iIDx, 0);
		UpdateData(false);
	}

	*pResult = 0;
}

// CAddAnimDlg message handlers // 몇가지 프로시저를 가로채서 내가 셋팅 해 주기 위한 프로시저.
int CALLBACK Proc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	// 초기화 할때 메세지를 가로챔
	if (uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	return 0;
}

void CAddAnimDlg::OnBnClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 폴더 선택 다이얼로그
	BROWSEINFO br = {};

	br.lpfn = Proc; // 프로시저 콜백함수를 지정 해주어 시작경로를 설정 한다.

	CString strFolderInitPath = CPathMgr::GetResPath();
	strFolderInitPath += L"Texture\\Animation";
	br.lParam = (LPARAM)strFolderInitPath.GetBuffer();
	br.ulFlags = BIF_USENEWUI;		  // 디자인
	br.hwndOwner = m_hWnd;			 // 핸들 소유자 설정(부모)
	br.lpszTitle = L"폴더 선택";	 // 창 이름

	LPITEMIDLIST pidl = NULL;     // 종료 할 시 경로에 저장
	if ((pidl = SHBrowseForFolder(&br)) != NULL)  // 폴더 선택 창. (실행 시 경로를 찾아서 경로잡아준다)
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bContinue)
		m_bContinue = false;
	else
		m_bContinue = true;


	SetContinue(m_bContinue);
}

void CAddAnimDlg::SetContinue(BOOL _bContinue)
{
	// 단일 텍스쳐->
	if (m_bContinue)
	{
		// 활성화
		m_editTexCount.SendMessage(EM_SETREADONLY, 0, 0);

		// 비활성화
		m_editLT.SendMessage(EM_SETREADONLY, 1, 0);
		m_editRT.SendMessage(EM_SETREADONLY, 1, 0);
		m_editSizeX.SendMessage(EM_SETREADONLY, 1, 0);
		m_editSizeY.SendMessage(EM_SETREADONLY, 1, 0);
		m_editFrameCount.SendMessage(EM_SETREADONLY, 1, 0);
	}
	else //연속 텍스쳐->
	{
		// 비활성화
		m_editTexCount.SendMessage(EM_SETREADONLY, 1, 0);

		// 활성화
		m_editLT.SendMessage(EM_SETREADONLY, 0, 0);
		m_editRT.SendMessage(EM_SETREADONLY, 0, 0);
		m_editSizeX.SendMessage(EM_SETREADONLY, 0, 0);
		m_editSizeY.SendMessage(EM_SETREADONLY, 0, 0);
		m_editFrameCount.SendMessage(EM_SETREADONLY, 0, 0);
	}
}