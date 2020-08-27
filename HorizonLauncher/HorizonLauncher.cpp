
// HorizonLauncher.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "HorizonLauncher.h"
#include "HorizonLauncherDlg.h"
#include "locale.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHorizonLauncherApp

BEGIN_MESSAGE_MAP(CHorizonLauncherApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHorizonLauncherApp �R���X�g���N�V����

CHorizonLauncherApp::CHorizonLauncherApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CHorizonLauncherApp �I�u�W�F�N�g�ł��B

CHorizonLauncherApp theApp;


// CHorizonLauncherApp ������

BOOL CHorizonLauncherApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

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
		if(m_strServerName.IsEmpty() || m_strAppName.IsEmpty())
		{
			strMsg.Format(_T("%s"),_T("Horizon�N���p�̃T�[�o�[�����A�v�������Z�b�g����Ă��܂���B"));
			::MessageBox(NULL,strMsg,m_strExeNameNoExt,MB_ICONERROR);
		}
		else
		{
			this->CustomBrowserStart(m_strServerName,m_strAppName,m_CommandParam);;
		}
	}
	else
	{
		CHorizonLauncherDlg dlg;
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
BOOL CHorizonLauncherApp::IsHorizonInstalled()
{
	BOOL bRet = FALSE;
	HKEY  hKey={0};
	DWORD dwDisposition=0;
	LONG lResult=0L;
	CString strVal;
	DWORD dwType=0;

	lResult=RegOpenKeyEx(HKEY_CLASSES_ROOT,_T("vmware-view\\shell\\open\\command"),
		0,KEY_READ,&hKey);

	if(lResult == ERROR_SUCCESS)
	{
		DWORD iSize=0;
		TCHAR* pVal=NULL;

		RegQueryValueEx(hKey,_T(""),NULL,&dwType,NULL,&iSize);
		if(iSize>0)
		{
			iSize+=1;//+1=null
			pVal = new TCHAR[iSize];
			memset(pVal,0x00,sizeof(TCHAR)*iSize);
			RegQueryValueEx(hKey,_T(""),NULL,&dwType,(LPBYTE)pVal, &iSize);
			strVal = pVal;
			delete [] pVal;
		}
		RegCloseKey(hKey);
	}
	if(!strVal.IsEmpty())
		bRet = TRUE;

	return bRet;
}

CString CHorizonLauncherApp::Get_ViewClient_ProtocolCommand()
{
	HKEY  hKey={0};
	DWORD dwDisposition=0;
	LONG lResult=0L;
	CString strVal;
	DWORD dwType=0;

	lResult=RegOpenKeyEx(HKEY_CLASSES_ROOT,_T("vmware-view\\shell\\open\\command"),
		0,KEY_READ,&hKey);
	if(lResult == ERROR_SUCCESS)
	{
		DWORD iSize=0;
		TCHAR* pVal=NULL;

		RegQueryValueEx(hKey,_T(""),NULL,&dwType,NULL,&iSize);
		if(iSize>0)
		{
			iSize+=1;//+1=null
			pVal = new TCHAR[iSize];
			memset(pVal,0x00,sizeof(TCHAR)*iSize);
			RegQueryValueEx(hKey,_T(""),NULL,&dwType,(LPBYTE)pVal, &iSize);
			strVal = pVal;
			delete [] pVal;
		}
		RegCloseKey(hKey);
	}
	return strVal;
}

void CHorizonLauncherApp::CustomBrowserStart(const CString& strServerName,const CString& strAppName,const CString& strURL)
{
	//horizon client���C���X�g�[������Ă��Ȃ��B
	if(!theApp.IsHorizonInstalled())
	{
		CString strMsg=_T("VMware Horizon Client���C���X�g�[������Ă��Ȃ����A�ݒ肳��Ă��Ȃ����ߋN���ł��܂���B");
		::MessageBox(NULL,strMsg,m_strExeNameNoExt,MB_ICONERROR);
		return;
	}

	CString strCommand;
	CString strAppNameEncode;
	CString strURLEncode;
	strAppNameEncode = theApp.ConvertUTF8_URLEncode(strAppName);

	if(strURL.IsEmpty())
	{
		strCommand.Format(_T("vmware-view://%s/%s"),strServerName,strAppNameEncode);
	}
	else
	{
		strURLEncode = theApp.ConvertUTF8_URLEncode(strURL);
		strCommand.Format(_T("vmware-view://%s/%s?url=%s"),strServerName,strAppNameEncode,strURLEncode);
	}
	CString strViewProc;
	strViewProc = Get_ViewClient_ProtocolCommand();
	BOOL bExecFlg=FALSE;
	if(!strViewProc.IsEmpty())
	{
		if(strViewProc.Find(_T("%1")) > 0)
		{
			strViewProc.Replace(_T("%1"),strCommand);
			if(::ShellExecute(NULL,_T("open"),strCommand,NULL,NULL, SW_SHOW) <= HINSTANCE(32))
			{
				bExecFlg=FALSE;
			}
			else
			{
				bExecFlg=TRUE;
			}
		}
	}

	if(!bExecFlg)
	{
		::ShellExecute(NULL,NULL,strCommand,NULL,NULL, SW_SHOW);
	}
}
void CHorizonLauncherApp::ReadSetting()
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
					if(strTemp2.CompareNoCase(_T("ServerName"))==0)
					{
						m_strServerName=strTemp3;
					}
					else if(strTemp2.CompareNoCase(_T("AppName"))==0)
					{
						m_strAppName=strTemp3;
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
