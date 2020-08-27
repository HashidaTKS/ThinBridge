
// CustomLauncher.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "CustomLauncher.h"
#include "CustomLauncherDlg.h"
#include "locale.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCustomLauncherApp

BEGIN_MESSAGE_MAP(CCustomLauncherApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCustomLauncherApp �R���X�g���N�V����

CCustomLauncherApp::CCustomLauncherApp()
{
	m_iKeyCombination=0;
}


// �B��� CCustomLauncherApp �I�u�W�F�N�g�ł��B

CCustomLauncherApp theApp;


// CCustomLauncherApp ������

BOOL CCustomLauncherApp::InitInstance()
{
	//pn.exe /Qlaunch "Farm1:iexplore.exe" /param:"URL"


	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls={0};
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
//	SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));

	TCHAR szPath[MAX_PATH+1]={0};
	TCHAR szDrive[_MAX_DRIVE]={0};
	TCHAR szDir[_MAX_DIR]={0};
	TCHAR szFileName[_MAX_FNAME]={0};
	TCHAR szExt[_MAX_EXT]={0};
	GetModuleFileName(AfxGetInstanceHandle(),szPath,MAX_PATH);
	_tsplitpath_s(szPath, szDrive,_MAX_DRIVE, szDir,_MAX_DIR, szFileName,_MAX_FNAME, szExt,_MAX_EXT); 

	m_strExeFullPath=szPath;
	m_strExeNameNoExt = szFileName;

	//�ݒ�f�[�^�̃��[�h
	m_strSetting_FileFullPath = szDrive;
	m_strSetting_FileFullPath += szDir;
	m_strSetting_FileFullPath += m_strExeNameNoExt;
	m_strSetting_FileFullPath += _T(".conf");
	this->ReadSetting();

	CString strMsg;
	CString Command1;
	CString Command2;
	//�R�}���h���C������B
	if(m_lpCmdLine[0] != '\0')
	{
		//�p�����[�^��1����
		if(__argc ==2)
		{
			Command1 = CString(__wargv[1]);
			Command1.Replace(_T("\""),_T(""));
			Command1.TrimLeft();
			Command1.TrimRight();

			if(!Command1.IsEmpty())
			{
				//URL��FilePath�̏ꍇ�́A�����I��m_CommandParam�Ƃ���B
				if(SBUtil::IsURL(Command1))
				{
					m_CommandParam=Command1;
				}
				//filepath
				else if(Command1.Find(_T(":"))==1)
				{
					m_CommandParam=Command1;
				}
				//-�́A�I�v�V����
				else if(Command1.Find(_T("-"))==0)
				{
					m_OptionParam=Command1;
				}
				// /�́A�I�v�V����
				else if(Command1.Find(_T("/"))==0)
				{
					m_OptionParam=Command1;
				}
			}
		}
		//�R�}���h���C����3�ȏ�A0�Ԃ́AEXE�p�X
		else if(__argc>=3)
		{
			Command1 = CString(__wargv[1]);
			Command2 = CString(__wargv[2]);
			Command1.Replace(_T("\""),_T(""));
			Command1.TrimLeft();
			Command1.TrimRight();

			Command2.Replace(_T("\""),_T(""));
			Command2.TrimLeft();
			Command2.TrimRight();

			if(!Command1.IsEmpty())
			{
				//URL��FilePath�̏ꍇ�́A�����I��m_CommandParam�Ƃ���B
				if(SBUtil::IsURL(Command1))
				{
					m_CommandParam=Command1;
				}
				//filepath
				else if(Command1.Find(_T(":"))==1)
				{
					m_CommandParam=Command1;
				}
			}
			if(!Command2.IsEmpty())
			{
				//URL��FilePath�̏ꍇ�́A�����I��m_CommandParam�Ƃ���B
				if(SBUtil::IsURL(Command2))
				{
					m_CommandParam=Command2;
				}
				else
				{
					m_OptionParam=Command2;
				}
			}
		}
		//.conf��Command1������ꍇ�B	
		if(!m_strCommand1.IsEmpty())
		{
			this->CustomBrowserStart(m_strCommand1,m_strCommand2,m_CommandParam);;
		}
		//Command Line�Ȃ�
		else
		{
			strMsg.Format(_T("%s"),_T("�N���p�̃R�}���h1���Z�b�g����Ă��܂���B"));
			::MessageBox(NULL,strMsg,m_strExeNameNoExt,MB_ICONERROR);
		}
	}
	else
	{
		CCustomLauncherDlg dlg;
		//�\����������Ă���ꍇ
		if(m_iKeyCombination)
		{
			strMsg.Format(_T("%s\n%s"),_T("���̋@�\�ւ̃A�N�Z�X�́A�V�X�e���Ǘ��҂ɂ�萧������Ă��܂��B "),_T("This Feature has been disabled by your administrator."));
			::MessageBox(NULL,strMsg,m_strExeNameNoExt,MB_ICONERROR);
			//Key�L�[�R���r�l�[�V��������v�����ꍇ�́A�ݒ��ʂ�\������B
			if(bValidKeyCombi())
			{
				m_pMainWnd = &dlg;
				dlg.DoModal();
			}
		}
		else
		{
			m_pMainWnd = &dlg;
			dlg.DoModal();
		}
	}
	return FALSE;
}

void CCustomLauncherApp::CustomBrowserStart(CString strCommand1,CString strCommand2,CString strURL)
{
	CString IEcmd;
	IEcmd=_T("");
	if(!strCommand2.IsEmpty())
	{
		strCommand2.Replace(_T("<URL>"),strURL);
		IEcmd.Format(_T("\"%s\" %s"),strCommand1,strCommand2);
	}
	else
	{
		IEcmd.Format(_T("\"%s\""),strCommand1);
	}
	CString strPathQ;
	strPathQ.Format(_T("\"%s\""),strCommand1);
	STARTUPINFO si={0};
	PROCESS_INFORMATION pi={0};
	si.cb = sizeof( si );
	if(!CreateProcess( NULL,(LPTSTR)(LPCTSTR)IEcmd,NULL, NULL, FALSE, 0, NULL,NULL, &si, &pi ))
	{
		SetLastError(NO_ERROR);
		//Retry
		STARTUPINFO si2={0};
		PROCESS_INFORMATION pi2={0};
		si2.cb = sizeof( si2 );
		if(!CreateProcess( strPathQ,(LPTSTR)(LPCTSTR)strCommand2,NULL, NULL, FALSE, 0, NULL,NULL, &si2, &pi2 ))
		{
			SetLastError(NO_ERROR);
			if(::ShellExecute(NULL,_T("open"),strPathQ,strCommand2,NULL, SW_SHOW) <= HINSTANCE(32))
			{
				SetLastError(NO_ERROR);
				::ShellExecute(NULL,NULL,IEcmd,NULL,NULL, SW_SHOW);
			}
		}
		else
		{
			if(pi2.hThread)
			{
				CloseHandle( pi2.hThread );  // �X���b�h�̃n���h���͎g��Ȃ��̂ł����j��
				pi2.hThread=0;
			}
			if(pi2.hProcess)
			{
				CloseHandle( pi2.hProcess ); // �����v���Z�X�̃n���h���͎g��Ȃ��̂Ŕj��
				pi2.hProcess=0;
			}
		}
	}
	else
	{
		if(pi.hThread)
		{
			CloseHandle( pi.hThread );  // �X���b�h�̃n���h���͎g��Ȃ��̂ł����j��
			pi.hThread=0;
		}
		if(pi.hProcess)
		{
			CloseHandle( pi.hProcess ); // �����v���Z�X�̃n���h���͎g��Ȃ��̂Ŕj��
			pi.hProcess=0;
		}
	}
}
void CCustomLauncherApp::ReadSetting()
{
	_wsetlocale(LC_ALL, _T("jpn")); 
	CStdioFile in;
	CString strTemp;
	CString strLogMsgLine;
	if(in.Open(m_strSetting_FileFullPath,CFile::modeRead|CFile::shareDenyWrite))
	{
		CString strTemp2;
		CString strTemp3;
		CStringArray strArray;
		while(in.ReadString(strTemp))
		{
			strTemp.TrimLeft();
			strTemp.TrimRight();
			strArray.RemoveAll();
			SBUtil::Split(strArray,strTemp,_T("="));
			strLogMsgLine += strTemp;
			strLogMsgLine += "\n";

			if(strArray.GetSize() >= 2)
			{
				strTemp2=strArray.GetAt(0);
				strTemp2.TrimLeft();
				strTemp2.TrimRight();

				strTemp3=strArray.GetAt(1);
				strTemp3.TrimLeft();
				strTemp3.TrimRight();

				if(strTemp2.Find(_T(";"))==0)
				{
					;
				}
				else if(strTemp2.Find(_T("#"))==0)
				{
					;
				}
				else
				{
					if(strTemp2.CompareNoCase(_T("Command1"))==0)
					{
						m_strCommand1=strTemp3;
					}
					else if(strTemp2.CompareNoCase(_T("Command2"))==0)
					{
						m_strCommand2=strTemp3;
					}
					else if(strTemp2.CompareNoCase(_T("KeyCombination"))==0)
					{
						if(!strTemp3.IsEmpty())
							m_iKeyCombination=_ttoi(strTemp3);
						else
							m_iKeyCombination=0;
					}
				}
			}
		}
		in.Close();
	}
}
