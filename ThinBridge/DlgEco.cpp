#include "stdafx.h"
#include "ThinBridge.h"
#include "DlgEco.h"
#include "afxdialogex.h"


IMPLEMENT_DYNCREATE(CDlgEco, CPropertyPage)

CDlgEco::CDlgEco()
	: CPropertyPage(CDlgEco::IDD)
{

}

CDlgEco::~CDlgEco()
{
}

void CDlgEco::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
}


BEGIN_MESSAGE_MAP(CDlgEco, CPropertyPage)
	ON_MESSAGE(ID_SETTING_OK,Set_OK)
	ON_BN_CLICKED(IDC_CHK_IE_CAP_TAB, &CDlgEco::OnBnClickedChkIeCapTab)
	ON_BN_CLICKED(IDC_CHK_IE_CAP_MEM, &CDlgEco::OnBnClickedChkIeCapMem)
	ON_BN_CLICKED(IDC_CHK_IE_CAP_CPU, &CDlgEco::OnBnClickedChkIeCapCpu)
END_MESSAGE_MAP()

static LPCTSTR gEcoCPUList[] = {
	_T("��"),
	_T("�ʏ�ȏ�"),
	_T("�ʏ�"),
	_T("�ʏ�ȉ�"),
	_T("��"),
};

BOOL CDlgEco::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	for(int i=0;i<5;i++)
	{
		m_Combo.AddString(gEcoCPUList[i]);
	}

	((CButton*)GetDlgItem(IDC_CHK_IE_CAP_TAB))->SetCheck(theApp.ResourceCAPConfMod.m_bTabCntCAP?1:0);
	SetDlgItemInt(IDC_EDIT_TAB_W,theApp.ResourceCAPConfMod.m_uiTabCntWARM);
	SetDlgItemInt(IDC_EDIT_TAB_M,theApp.ResourceCAPConfMod.m_uiTabCntMAX);

	CString strMsg;

	strMsg = theApp.ResourceCAPConfMod.m_strTab_WARM_Msg;
	strMsg.Replace(_T("\n"),_T("\r\n"));
	SetDlgItemText(IDC_EDIT_TAB_W_MSG,strMsg);

	strMsg = theApp.ResourceCAPConfMod.m_strTab_MAX_Msg;
	strMsg.Replace(_T("\n"),_T("\r\n"));
	SetDlgItemText(IDC_EDIT_TAB_M_MSG,strMsg);

	SetDlgItemInt(IDC_EDIT_TAB_WMT,theApp.ResourceCAPConfMod.m_uiTab_WARM_ShowTime);
	SetDlgItemInt(IDC_EDIT_TAB_MMT,theApp.ResourceCAPConfMod.m_uiTab_MAX_ShowTime);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	((CButton*)GetDlgItem(IDC_CHK_IE_CAP_MEM))->SetCheck(theApp.ResourceCAPConfMod.m_bMemUsageCAP?1:0);
	SetDlgItemInt(IDC_EDIT_MEM_W,theApp.ResourceCAPConfMod.m_uiMemWARM);
	SetDlgItemInt(IDC_EDIT_MEM_M,theApp.ResourceCAPConfMod.m_uiMemMAX);

	strMsg = theApp.ResourceCAPConfMod.m_strMem_WARM_Msg;
	strMsg.Replace(_T("\n"),_T("\r\n"));
	SetDlgItemText(IDC_EDIT_MEM_W_MSG,strMsg);

	strMsg = theApp.ResourceCAPConfMod.m_strMem_MAX_Msg;
	strMsg.Replace(_T("\n"),_T("\r\n"));
	SetDlgItemText(IDC_EDIT_MEM_M_MSG,strMsg);

	SetDlgItemInt(IDC_EDIT_MEM_WMT,theApp.ResourceCAPConfMod.m_uiMem_WARM_ShowTime);
	SetDlgItemInt(IDC_EDIT_MEM_MMT,theApp.ResourceCAPConfMod.m_uiMem_MAX_ShowTime);


	((CButton*)GetDlgItem(IDC_CHK_IE_CAP_CPU))->SetCheck(theApp.ResourceCAPConfMod.m_bCPUPriorityCAP?1:0);
	m_Combo.SetCurSel(theApp.ResourceCAPConfMod.m_uiCPUPriority);

	Change_TabState();
	Change_MemState();
	Change_CPUState();

	return FALSE;
}

LRESULT CDlgEco::Set_OK(WPARAM wParam, LPARAM lParam)
{
	BOOL bTabCntCAP = ((CButton*)GetDlgItem(IDC_CHK_IE_CAP_TAB))->GetCheck() == 1?TRUE:FALSE;
	if(bTabCntCAP)
	{
		//���̓`�F�b�N
		int iWndW = GetDlgItemInt(IDC_EDIT_TAB_W);
		if(2<=iWndW && iWndW <=99) 
		{
			theApp.ResourceCAPConfMod.m_uiTabCntWARM=iWndW;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE �^�u / �E�C���h�E���𐧌�����] [�x���\��]�̌������s���ł��B(�L���͈� 2-99)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}

		//���̓`�F�b�N
		int iWndM = GetDlgItemInt(IDC_EDIT_TAB_M);
		if(3<=iWndM && iWndM <=100) 
		{
			theApp.ResourceCAPConfMod.m_uiTabCntMAX=iWndM;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE �^�u / �E�C���h�E���𐧌�����] [�ő�l]�̌������s���ł��B(�L���͈� 3-100)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}

		if(iWndW >= iWndM)
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE �^�u / �E�C���h�E���𐧌�����]  [�x���\��]���������A[�ő�l]�̌�����傫�����ĉ������B"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}

		CString strMsg;
		GetDlgItemText(IDC_EDIT_TAB_W_MSG,strMsg);
		if(strMsg.IsEmpty())
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE �^�u / �E�C���h�E����]�x�����b�Z�[�W����͂��ĉ������B"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}
		strMsg.Replace(_T("\r\n"),_T("\n"));
		theApp.ResourceCAPConfMod.m_strTab_WARM_Msg=strMsg;

		strMsg.Empty();
		GetDlgItemText(IDC_EDIT_TAB_M_MSG,strMsg);
		if(strMsg.IsEmpty())
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE �^�u / �E�C���h�E����]���߃��b�Z�[�W����͂��ĉ������B"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}
		strMsg.Replace(_T("\r\n"),_T("\n"));
		theApp.ResourceCAPConfMod.m_strTab_MAX_Msg=strMsg;

		int iTM = GetDlgItemInt(IDC_EDIT_TAB_WMT);
		if(0<=iTM && iTM <=60) 
		{
			theApp.ResourceCAPConfMod.m_uiTab_WARM_ShowTime=iTM;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE �^�u / �E�C���h�E����] [�x�����b�Z�[�W�\���b��]�̎w�肪�s���ł��B(�L���͈� 0-60)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}
		iTM =0;
		iTM = GetDlgItemInt(IDC_EDIT_TAB_MMT);
		if(0<=iTM && iTM <=60) 
		{
			theApp.ResourceCAPConfMod.m_uiTab_MAX_ShowTime=iTM;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE �^�u / �E�C���h�E����] [���߃��b�Z�[�W�\���b��]�̎w�肪�s���ł��B(�L���͈� 0-60)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}
		theApp.ResourceCAPConfMod.m_bTabCntCAP=TRUE;
	}
	else
		theApp.ResourceCAPConfMod.m_bTabCntCAP=FALSE;


	BOOL bMemUsageCAP = ((CButton*)GetDlgItem(IDC_CHK_IE_CAP_MEM))->GetCheck() == 1?TRUE:FALSE;
	if(bMemUsageCAP)
	{
		//���̓`�F�b�N
		int iMemW = GetDlgItemInt(IDC_EDIT_MEM_W);
		if(100<=iMemW && iMemW <=1000) 
		{
			theApp.ResourceCAPConfMod.m_uiMemWARM=iMemW;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE ��������[�T�C�Y(�R�~�b�g �T�C�Y)�𐧌�����] [�x���\��]�̃������T�C�Y���s���ł��B(�L���͈� 100-1,000 MB)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}

		//���̓`�F�b�N
		int iMemM = GetDlgItemInt(IDC_EDIT_MEM_M);
		if(200<=iMemM && iMemM <=2000) 
		{
			theApp.ResourceCAPConfMod.m_uiMemMAX=iMemM;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE ��������[�T�C�Y(�R�~�b�g �T�C�Y)�𐧌�����] [�ő�l]�̃������T�C�Y���s���ł��B(�L���͈� 200-2,000 MB)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}

		if(iMemW >= iMemM)
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE ��������[�T�C�Y(�R�~�b�g �T�C�Y)�𐧌�����]  [�x���\��]�����A[�ő�l]��傫�����ĉ������B"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}

		CString strMsg;
		GetDlgItemText(IDC_EDIT_MEM_W_MSG,strMsg);
		if(strMsg.IsEmpty())
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE ��������[����]�x�����b�Z�[�W����͂��ĉ������B"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}
		strMsg.Replace(_T("\r\n"),_T("\n"));
		theApp.ResourceCAPConfMod.m_strMem_WARM_Msg=strMsg;

		strMsg.Empty();
		GetDlgItemText(IDC_EDIT_MEM_M_MSG,strMsg);
		if(strMsg.IsEmpty())
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE ��������[����]���߃��b�Z�[�W����͂��ĉ������B"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}
		strMsg.Replace(_T("\r\n"),_T("\n"));
		theApp.ResourceCAPConfMod.m_strMem_MAX_Msg=strMsg;

		int iTM = GetDlgItemInt(IDC_EDIT_MEM_WMT);
		if(0<=iTM && iTM <=60) 
		{
			theApp.ResourceCAPConfMod.m_uiMem_WARM_ShowTime=iTM;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE ��������[����] [�x�����b�Z�[�W�\���b��]�̎w�肪�s���ł��B(�L���͈� 0-60)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}
		iTM =0;
		iTM = GetDlgItemInt(IDC_EDIT_MEM_MMT);
		if(0<=iTM && iTM <=60) 
		{
			theApp.ResourceCAPConfMod.m_uiMem_MAX_ShowTime=iTM;
		}
		else
		{
			::MessageBox(this->m_hWnd,_T("[�S�ʐݒ�]-[���\�[�X�ݒ�]\n[IE ��������[����] [���߃��b�Z�[�W�\���b��]�̎w�肪�s���ł��B(�L���͈� 0-60)"),theApp.m_strThisAppName,MB_OK|MB_ICONERROR );
			return 1;
		}

		theApp.ResourceCAPConfMod.m_bMemUsageCAP=TRUE;
	}
	else
		theApp.ResourceCAPConfMod.m_bMemUsageCAP=FALSE;

	BOOL bCPUPriorityCAP = ((CButton*)GetDlgItem(IDC_CHK_IE_CAP_CPU))->GetCheck() == 1?TRUE:FALSE;
	int iID=0;
	iID = m_Combo.GetCurSel();
	if(bCPUPriorityCAP)
	{
		theApp.ResourceCAPConfMod.m_bCPUPriorityCAP=bCPUPriorityCAP;
		if(0<=iID && iID<=4)
			theApp.ResourceCAPConfMod.m_uiCPUPriority=iID;
		else
			theApp.ResourceCAPConfMod.m_uiCPUPriority=2;
	}
	else
	{
		theApp.ResourceCAPConfMod.m_bCPUPriorityCAP=FALSE;
	}

	return 0;
}

void CDlgEco::OnBnClickedChkIeCapTab()
{
	Change_TabState();
}

void CDlgEco::OnBnClickedChkIeCapMem()
{
	Change_MemState();
}

void CDlgEco::OnBnClickedChkIeCapCpu()
{
	Change_CPUState();
}

void CDlgEco::Change_TabState()
{
	BOOL bFlg=FALSE;
	if(((CButton*)GetDlgItem(IDC_CHK_IE_CAP_TAB))->GetCheck() == 1)
		bFlg=TRUE;
	else
		bFlg=FALSE;
	GetDlgItem(IDC_EDIT_TAB_W)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_TAB_M)->EnableWindow(bFlg);

	GetDlgItem(IDC_EDIT_TAB_W_MSG)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_TAB_M_MSG)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_TAB_WMT)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_TAB_MMT)->EnableWindow(bFlg);

}
void CDlgEco::Change_MemState()
{
	BOOL bFlg=FALSE;
	if(((CButton*)GetDlgItem(IDC_CHK_IE_CAP_MEM))->GetCheck() == 1)
		bFlg=TRUE;
	else
		bFlg=FALSE;
	GetDlgItem(IDC_EDIT_MEM_W)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_MEM_M)->EnableWindow(bFlg);

	GetDlgItem(IDC_EDIT_MEM_W_MSG)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_MEM_M_MSG)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_MEM_WMT)->EnableWindow(bFlg);
	GetDlgItem(IDC_EDIT_MEM_MMT)->EnableWindow(bFlg);
}
void CDlgEco::Change_CPUState()
{
	BOOL bFlg=FALSE;
	if(((CButton*)GetDlgItem(IDC_CHK_IE_CAP_CPU))->GetCheck() == 1)
		bFlg=TRUE;
	else
		bFlg=FALSE;
	m_Combo.EnableWindow(bFlg);
}
