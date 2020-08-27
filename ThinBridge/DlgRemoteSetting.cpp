#include "stdafx.h"
#include "ThinBridge.h"
#include "DlgRemoteSetting.h"
#include "afxdialogex.h"


IMPLEMENT_DYNCREATE(CDlgRemoteSetting, CPropertyPage)

CDlgRemoteSetting::CDlgRemoteSetting()
	: CPropertyPage(CDlgRemoteSetting::IDD)
{

}

CDlgRemoteSetting::~CDlgRemoteSetting()
{
}

void CDlgRemoteSetting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRemoteSetting, CPropertyPage)
END_MESSAGE_MAP()


BOOL CDlgRemoteSetting::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	SetDlgItemText(IDC_STATIC,_T("�����[�g�u���E�U�[��ݒ肵�܂��B\n\n  �EMicrosoft RDP\n\n  �EVMware Horizon\n\n  �ECitrix XenApp\n\n\n�����̃c���[����ݒ肷�鍀�ڂ�I�����ĉ������B"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

IMPLEMENT_DYNCREATE(CDlgRemoteSettingRD,CDlgRemoteSetting)
BOOL CDlgRemoteSettingRD::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CString strText;
	strText = _T("���_�C���N�g����URL��ݒ肵�܂��B\n\n");
	strText +=_T("  �EMicrosoft RDP\n\n");
	strText +=_T("  �EVMware Horizon\n\n");
	strText +=_T("  �ECitrix XenApp\n\n");
	strText +=_T("  �EMozilla Firefox\n\n");
	strText +=_T("  �EGoogle Chrome\n\n");
	strText +=_T("  �EMicrosoft Edge\n\n");
	strText +=_T("  �E�w��u���E�U�[01-20\n\n");
	strText +=_T("\n�����̃c���[����ݒ肷�鍀�ڂ�I�����ĉ������B");

	SetDlgItemText(IDC_STATIC,strText);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}


IMPLEMENT_DYNCREATE(CDlgRemoteSettingGEN,CDlgRemoteSetting)
BOOL CDlgRemoteSettingGEN::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	SetDlgItemText(IDC_STATIC,_T("�S�ʐݒ�\n\n  �EURL���_�C���N�g�S�ʐݒ�\n\n  �E���\�[�X�ݒ�\n\n\n�����̃c���[����ݒ肷�鍀�ڂ�I�����ĉ������B"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
