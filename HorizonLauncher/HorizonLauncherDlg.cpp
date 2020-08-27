
// HorizonLauncherDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "HorizonLauncher.h"
#include "HorizonLauncherDlg.h"
#include "afxdialogex.h"
#include "DlgURL.h"
#include "locale.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHorizonLauncherDlg �_�C�A���O




CHorizonLauncherDlg::CHorizonLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHorizonLauncherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHorizonLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHorizonLauncherDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHorizonLauncherDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHorizonLauncherDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CHorizonLauncherDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHorizonLauncherDlg ���b�Z�[�W �n���h���[

BOOL CHorizonLauncherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	int iKeyCombination=0;
	iKeyCombination=theApp.m_iKeyCombination;

	((CButton*)GetDlgItem(IDC_CHK_SHIFT))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_CTRL))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_ALT))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_LEFT))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_UP))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_RIGHT))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_DOWN))->SetCheck(0);

	if((iKeyCombination&KEY_COMB_SHIFT)==KEY_COMB_SHIFT)
		((CButton*)GetDlgItem(IDC_CHK_SHIFT))->SetCheck(1);
	if((iKeyCombination&KEY_COMB_CTRL)==KEY_COMB_CTRL)
		((CButton*)GetDlgItem(IDC_CHK_CTRL))->SetCheck(1);
	if((iKeyCombination&KEY_COMB_ALT)==KEY_COMB_ALT)
		((CButton*)GetDlgItem(IDC_CHK_ALT))->SetCheck(1);
	if((iKeyCombination&KEY_COMB_LEFT)==KEY_COMB_LEFT)
		((CButton*)GetDlgItem(IDC_CHK_LEFT))->SetCheck(1);
	if((iKeyCombination&KEY_COMB_UP)==KEY_COMB_UP)
		((CButton*)GetDlgItem(IDC_CHK_UP))->SetCheck(1);
	if((iKeyCombination&KEY_COMB_RIGHT)==KEY_COMB_RIGHT)
		((CButton*)GetDlgItem(IDC_CHK_RIGHT))->SetCheck(1);
	if((iKeyCombination&KEY_COMB_DOWN)==KEY_COMB_DOWN)
		((CButton*)GetDlgItem(IDC_CHK_DOWN))->SetCheck(1);

	SetDlgItemText(IDC_EDIT_VHOST,theApp.m_strServerName);
	SetDlgItemText(IDC_EDIT_VAPP,theApp.m_strAppName);

	return FALSE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CHorizonLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CHorizonLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHorizonLauncherDlg::OnBnClickedOk()
{
	int iRet=0;
	iRet = ::MessageBox(this->m_hWnd,_T("�ݒ��ۑ����܂����H"),theApp.m_strExeNameNoExt,MB_ICONQUESTION | MB_OKCANCEL);
	if(iRet == IDCANCEL)
		return;

	CString strServerName;
	CString strAppName;

	GetDlgItemText(IDC_EDIT_VHOST,strServerName);
	GetDlgItemText(IDC_EDIT_VAPP,strAppName);

	strServerName.TrimLeft();
	strServerName.TrimRight();
	strAppName.TrimLeft();
	strAppName.TrimRight();
	if(strServerName.IsEmpty())
	{
		CString strMsg=_T("Connection�T�[�o�[����͂��ĉ������B");
		::MessageBox(NULL,strMsg,theApp.m_strExeNameNoExt,MB_ICONERROR);
		GetDlgItem(IDC_EDIT_VHOST)->SetFocus();
		return;
	}
	if(strAppName.IsEmpty())
	{
		CString strMsg=_T("�A�v��������͂��ĉ������B");
		::MessageBox(NULL,strMsg,theApp.m_strExeNameNoExt,MB_ICONERROR);
		GetDlgItem(IDC_EDIT_VAPP)->SetFocus();
		return;
	}
	theApp.m_strServerName = strServerName;
	theApp.m_strAppName = strAppName;

	DWORD dSetting=0;
	if(((CButton*)GetDlgItem(IDC_CHK_SHIFT))->GetCheck()==1)
		dSetting = dSetting | KEY_COMB_SHIFT;
	if(((CButton*)GetDlgItem(IDC_CHK_CTRL))->GetCheck()==1)
		dSetting = dSetting | KEY_COMB_CTRL;
	if(((CButton*)GetDlgItem(IDC_CHK_ALT))->GetCheck()==1)
		dSetting = dSetting | KEY_COMB_ALT;
	if(((CButton*)GetDlgItem(IDC_CHK_LEFT))->GetCheck()==1)
		dSetting = dSetting | KEY_COMB_LEFT;
	if(((CButton*)GetDlgItem(IDC_CHK_UP))->GetCheck()==1)
		dSetting = dSetting | KEY_COMB_UP;
	if(((CButton*)GetDlgItem(IDC_CHK_RIGHT))->GetCheck()==1)
		dSetting = dSetting | KEY_COMB_RIGHT;
	if(((CButton*)GetDlgItem(IDC_CHK_DOWN))->GetCheck()==1)
		dSetting = dSetting | KEY_COMB_DOWN;
	DWORD iKeyCombination=dSetting;
	theApp.m_iKeyCombination=iKeyCombination;

	_wsetlocale(LC_ALL, _T("jpn")); 
	CStdioFile out;
	if(out.Open(theApp.m_strSetting_FileFullPath,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone))
	{
		//ServerName
		CString strWriteData;
		strWriteData.Format(_T("ServerName=%s\n"),theApp.m_strServerName);
		out.WriteString(strWriteData);

		//AppName
		strWriteData.Format(_T("AppName=%s\n"),theApp.m_strAppName);
		out.WriteString(strWriteData);

		//�\�������L�[�R���r�l�[�V����
		strWriteData.Format(_T("KeyCombination=%d\n"),theApp.m_iKeyCombination);
		out.WriteString(strWriteData);
		out.Close();
	}
	else
	{
		CString strSaveMsg;
		strSaveMsg.Format(_T("�ݒ�t�@�C���̕ۑ��Ɏ��s���܂����B\n\n�ʂ̃v���O�������t�@�C�����J���Ă��邩�A�����������s�����Ă��܂��B����������ł��܂���B�t�@�C������Ă���Ď��s���Ă��������B\n\n%s"),theApp.m_strSetting_FileFullPath);
		::MessageBox(this->m_hWnd,strSaveMsg,theApp.m_strExeNameNoExt,MB_OK|MB_ICONERROR );
	}
//	CDialogEx::OnOK();
}


void CHorizonLauncherDlg::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnCancel();
}


void CHorizonLauncherDlg::OnBnClickedButton1()
{
	CString strServerName;
	CString strAppName;

	GetDlgItemText(IDC_EDIT_VHOST,strServerName);
	GetDlgItemText(IDC_EDIT_VAPP,strAppName);

	strServerName.TrimLeft();
	strServerName.TrimRight();
	strAppName.TrimLeft();
	strAppName.TrimRight();

	if(strServerName.IsEmpty())
	{
		CString strMsg=_T("Connection�T�[�o�[����͂��ĉ������B");
		::MessageBox(NULL,strMsg,theApp.m_strExeNameNoExt,MB_ICONERROR);
		GetDlgItem(IDC_EDIT_VHOST)->SetFocus();
		return;
	}

	if(strAppName.IsEmpty())
	{
		CString strMsg=_T("�A�v��������͂��ĉ������B");
		::MessageBox(NULL,strMsg,theApp.m_strExeNameNoExt,MB_ICONERROR);
		GetDlgItem(IDC_EDIT_VAPP)->SetFocus();
		return;
	}

	CDlgURL Dlg;
	Dlg.DoModal();
	CString strURL;
	strURL=Dlg.m_strURL;
	theApp.CustomBrowserStart(strServerName,strAppName,strURL);
}
