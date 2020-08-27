
// CustomLauncherDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "CustomLauncher.h"
#include "CustomLauncherDlg.h"
#include "afxdialogex.h"
#include "DlgURL.h"
#include "locale.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCustomLauncherDlg �_�C�A���O




CCustomLauncherDlg::CCustomLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustomLauncherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCustomLauncherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCustomLauncherDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCustomLauncherDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomLauncherDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCustomLauncherDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCustomLauncherDlg ���b�Z�[�W �n���h���[

BOOL CCustomLauncherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
//	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
//	ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != NULL)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

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

	SetDlgItemText(IDC_EDIT1,theApp.m_strCommand1);
	SetDlgItemText(IDC_EDIT2,theApp.m_strCommand2);

	return FALSE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CCustomLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CCustomLauncherDlg::OnPaint()
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
HCURSOR CCustomLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCustomLauncherDlg::OnBnClickedOk()
{
	int iRet=0;
	iRet = ::MessageBox(this->m_hWnd,_T("�ݒ��ۑ����܂����H"),theApp.m_strExeNameNoExt,MB_ICONQUESTION | MB_OKCANCEL);
	if(iRet == IDCANCEL)
		return;

	CString strCommand1;
	CString strCommand2;

	GetDlgItemText(IDC_EDIT1,strCommand1);
	GetDlgItemText(IDC_EDIT2,strCommand2);

	strCommand1.TrimLeft();
	strCommand1.TrimRight();
	if(strCommand1.IsEmpty())
	{
		CString strMsg=_T("�R�}���h���C��1����͂��ĉ������B");
		::MessageBox(NULL,strMsg,theApp.m_strExeNameNoExt,MB_ICONERROR);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		return;
	}

	strCommand2.TrimLeft();
	strCommand2.TrimRight();
	theApp.m_strCommand1=strCommand1;
	theApp.m_strCommand2=strCommand2;


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
		//command1
		CString strWriteData;
		strWriteData.Format(_T("Command1=%s\n"),theApp.m_strCommand1);
		out.WriteString(strWriteData);

		//command2
		strWriteData.Format(_T("Command2=%s\n"),theApp.m_strCommand2);
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


void CCustomLauncherDlg::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnCancel();
}


void CCustomLauncherDlg::OnBnClickedButton1()
{
	CString strCommand1;
	CString strCommand2;

	GetDlgItemText(IDC_EDIT1,strCommand1);
	GetDlgItemText(IDC_EDIT2,strCommand2);

	strCommand1.TrimLeft();
	strCommand1.TrimRight();
	if(strCommand1.IsEmpty())
	{
		CString strMsg=_T("�R�}���h���C��1����͂��ĉ������B");
		::MessageBox(NULL,strMsg,theApp.m_strExeNameNoExt,MB_ICONERROR);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		return;
	}
	strCommand2.TrimLeft();
	strCommand2.TrimRight();


	CDlgURL Dlg;
	Dlg.DoModal();
	CString strURL;
	strURL=Dlg.m_strURL;
	theApp.CustomBrowserStart(strCommand1,strCommand2,strURL);
}


void CCustomLauncherDlg::OnBnClickedButton2()
{
	CString szFilter;
	szFilter=_T("���s�t�@�C��(*.exe)|*.exe|�S�Ẵt�@�C��(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter,this);
	CString strTitle;
	strTitle=_T("�J��");
	fileDlg.m_ofn.lpstrTitle = strTitle.GetBuffer(0);
	if (fileDlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDIT1,fileDlg.GetPathName());
	}
}
