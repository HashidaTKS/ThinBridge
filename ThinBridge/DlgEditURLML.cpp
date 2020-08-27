#include "stdafx.h"
#include "ThinBridge.h"
#include "DlgEditURLML.h"
#include "afxdialogex.h"
#include "DlgMsgBox.h"

IMPLEMENT_DYNAMIC(CDlgEditURLML, CDialogEx)

CDlgEditURLML::CDlgEditURLML(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEditURLML::IDD, pParent)
{

}

CDlgEditURLML::~CDlgEditURLML()
{
}

void CDlgEditURLML::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CDlgEditURLML, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDlgEditURLML::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgEditURLML::OnBnClickedOk)
	ON_WM_ACTIVATE()
	ON_WM_NCACTIVATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CDlgEditURLML::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

BOOL CDlgEditURLML::bValidData()
{
	BOOL bRet=FALSE;
	CString strText;
	CString strValidData;
	m_Edit.GetWindowText(strText);

	m_strArrayResult.RemoveAll();
	m_strArrayResult_Enable.RemoveAll();

	CStringArray strArray;
	CMapStringToPtr strMapDupChk;
	int iCnt=0;
	int iCntMax=0;
	void* dwpLineIndex={0};
	DWORD dwLine=0;
	CString strTempLine;
	CString strTempLineOrg;

	CString strErrMsg;
	CString strErrMsgLine;
	int iErrCnt=0;

	SBUtil::Split_TrimBlank(strArray,strText,_T("\r\n"));
	strText.Empty();

	//�d���Ƌ֑������`�F�b�N
	iCntMax = strArray.GetCount();
	BOOL bEnable=TRUE;

	for(iCnt=0;iCnt < iCntMax;iCnt++)
	{
		bEnable=TRUE;
		strTempLine.Empty();
		strTempLineOrg.Empty();
		strTempLine = strArray.GetAt(iCnt);
		strTempLineOrg = strTempLine;
		strText+=strTempLine;
		strText+="\r\n";

		//�擪�̃n�C�t��-�`�F�b�N
		if(strTempLine.Find(_T("-"))==0)
		{
			strErrMsgLine.Format(_T("�֑��F%d�s�ڂ̃f�[�^[%s]�́A�擪���n�C�t���L��'-'����n�܂邽�ߐݒ�ł��܂���B\r\n"),iCnt+1,strTempLine);
			strErrMsg+=strErrMsgLine;
			iErrCnt++;
			continue;
		}
		//�擪��#�`�F�b�N
		if(strTempLine.Find(_T("#"))==0)
		{
			//#�����Ȃ��ꍇ�́A���߁B
			if(strTempLine.GetLength()==1)
			{
				strErrMsgLine.Format(_T("�֑��F%d�s�ڂ̃f�[�^[%s]�́A#�L���ׁ݂̂̈A�ݒ�ł��܂���B\r\n"),iCnt+1,strTempLine);
				strErrMsg+=strErrMsgLine;
				iErrCnt++;
				continue;
			}
			else
				bEnable=FALSE;
		}
		//�擪��;�`�F�b�N
		if(strTempLine.Find(_T(";"))==0)
		{
			//#�����Ȃ��ꍇ�́A���߁B
			if(strTempLine.GetLength()==1)
			{
				strErrMsgLine.Format(_T("�֑��F%d�s�ڂ̃f�[�^[%s]�́A;�L���ׁ݂̂̈A�ݒ�ł��܂���B\r\n"),iCnt+1,strTempLine);
				strErrMsg+=strErrMsgLine;
				iErrCnt++;
				continue;
			}
			else
				bEnable=FALSE;
		}

		//comment���폜���Ēǉ�����B
		if(!bEnable)
		{
			strTempLine=strTempLine.Mid(1);
		}

		//�d���`�F�b�N
		if(strMapDupChk.Lookup(strTempLine,dwpLineIndex))
		{
			dwLine=0;
			dwLine = (DWORD)dwpLineIndex;
			//Lookup�o�����ꍇ�́A�d�����Ă���B
			strErrMsgLine.Format(_T("�d���F%d�s�ڂ̃f�[�^[%s]�́A%d�s�ڂɊ��ɓo�^����Ă��܂��B\r\n"),iCnt+1,strTempLine,dwLine+1);
			strErrMsg+=strErrMsgLine;
			iErrCnt++;
		}
		//�d�������B
		else
		{
			dwLine=iCnt;
			dwpLineIndex = (void*)dwLine;
			strMapDupChk.SetAt(strTempLine,dwpLineIndex);
			m_strArrayResult.Add(strTempLine);
			if(bEnable)
				m_strArrayResult_Enable.Add(_T("��"));
			else
				m_strArrayResult_Enable.Add(_T("�|"));
			strValidData+=strTempLineOrg;
			strValidData+=_T("\r\n");
		}
	}
	if(!strErrMsg.IsEmpty())
	{
		CString strErrMsgResult;
		strErrMsgResult.Format(_T("�y�f�[�^�G���[�z\r\n��%d�̃G���[������܂��B\r\n�X�V�Ɏ��s���܂����B�f�[�^���C�����ĉ������B\r\n=====================================================================\r\n%s====================================================================="),iErrCnt,strErrMsg);
		CDlgMsgBox MsgBox;
		MsgBox.m_strMsg=strErrMsgResult;
		if(IDOK==MsgBox.DoModal())
		{
			int iRet = 0;
			iRet = ::MessageBox(this->m_hWnd,_T("�f�[�^�G���[�������I�ɏC�����܂����H\n\n���u�͂��v��I������ƃG���[�̔������Ă���s���폜���܂��B\n���ɖ߂����Ƃ͂ł��܂���B"),theApp.m_strThisAppName,MB_ICONQUESTION | MB_YESNO|MB_DEFBUTTON2);
			if(iRet == IDYES)
			{
				//�O�ׂ̈ɂ�����x�_�������B
				iRet = 0;
				iRet = ::MessageBox(this->m_hWnd,_T("�f�[�^�G���[�̎����C�������s���܂��B"),theApp.m_strThisAppName,MB_ICONASTERISK | MB_YESNO|MB_DEFBUTTON2);
				if(iRet == IDYES)
					strText=strValidData;
			}
		}
		m_SelPosS=0;
		m_SelPosE=0;
		m_Edit.SetFocus();
		m_Edit.SetWindowText(strText);
		m_Edit.PostMessage(EM_SETSEL, (WPARAM)m_SelPosS, (LPARAM)m_SelPosE);
		return FALSE;
	}
	else
	{
		m_strEditData = strText;
		bRet = TRUE;
	}
	return bRet;
}

void CDlgEditURLML::OnBnClickedOk()
{
	int iRet=0;
	iRet = ::MessageBox(this->m_hWnd,_T("�ݒ���X�V���܂����H\n���󔒍s�́A�����I�ɐ؂�l�߂��܂��B"),theApp.m_strThisAppName,MB_ICONQUESTION | MB_OKCANCEL);
	if(iRet == IDCANCEL)
		return;

	//�d���Ƌ֑������`�F�b�N
	if(bValidData())
	{
		CDialogEx::OnOK();
	}
}

BOOL CDlgEditURLML::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	bFirstFlg = TRUE;
	m_SelPosS=0;
	m_SelPosE=0;
	m_Edit.LimitText(1024*1024*5);
	m_Edit.SetFocus();
	m_Edit.SetWindowText(m_strEditData);
	if(!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle);
	return FALSE;
}
void CDlgEditURLML::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}


BOOL CDlgEditURLML::PreTranslateMessage(MSG* pMsg)
{
	ASSERT(pMsg != NULL);
	ASSERT_VALID(this);
	ASSERT(m_hWnd != NULL);
	CString strLine;

	if (pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
		{
			//OnCancel();
			return TRUE;
		}
	}
	if(pMsg->hwnd==m_Edit.m_hWnd)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if(pMsg->wParam == 'A')
			{
				if(::GetKeyState(VK_CONTROL)<0)
				{
					m_Edit.PostMessage(EM_SETSEL, (WPARAM)0, (LPARAM)-1);
					return TRUE;
				}
			}
		}
		if(pMsg->message == WM_MOUSEMOVE
		||pMsg->message  == WM_LBUTTONDOWN
		||pMsg->message  == WM_KEYDOWN
		||pMsg->message  == WM_KEYUP
		||pMsg->message  == WM_LBUTTONDOWN
		)
		{
			DWORD dwStart=0, dwEnd=0;
			DWORD dwCursorPos=0;
			DWORD dwLineIndex=0;
			CPoint   pt;
			LRESULT lr={0};
			dwCursorPos = m_Edit.SendMessage(EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
			if (pMsg->message == WM_MOUSEMOVE && dwStart == dwEnd)
				return lr;
			lr = CDialogEx::PreTranslateMessage(pMsg);

			dwLineIndex = m_Edit.SendMessage(EM_LINEFROMCHAR,-1,0);
			strLine.Format(_T("%d�s"),dwLineIndex+1);
			SetDlgItemText(IDC_STATIC_LINE,strLine);
			return lr;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDlgEditURLML::OnNcActivate(BOOL bActive)
{
	if(bActive)
	{
		if(bFirstFlg)
		{
			bFirstFlg = FALSE;
		}
		else
			m_Edit.PostMessage(EM_SETSEL, (WPARAM)m_SelPosS, (LPARAM)m_SelPosE);
	}
	else
	{
		m_Edit.GetSel(m_SelPosS,m_SelPosE);
	}
	return CDialogEx::OnNcActivate(bActive);
}


void CDlgEditURLML::OnPaint()
{
	CPaintDC dc(this);
}


