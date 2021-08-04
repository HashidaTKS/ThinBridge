// BHORedirector.h : CBHORedirector �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��
#include <shlguid.h> 
#include <exdispid.h> 
#include "BHORedirector_i.h"
#include <atlstr.h>
#include <atlcoll.h>
#include <atlfile.h>
#include "locale.h"
#include "atltime.h"
#include <activscp.h>
#include <atlfile.h>
#include <string>
#include "TBGlobal.h"
#include "SBUtil.h"
#include "AtlStdioFile.h"
#include "URLRedirectCore.h"

#pragma comment(lib, "Version.lib")

using namespace ATL;

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif

// CBHORedirector
class ATL_NO_VTABLE CBHORedirector :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBHORedirector, &CLSID_BHORedirector>,
	public IObjectWithSiteImpl<CBHORedirector>,
	public IDispatchImpl<IBHORedirector, &IID_IBHORedirector, &LIBID_BHORedirectorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispEventImpl<1, CBHORedirector, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>
{
public:
	CBHORedirector()
	{
		m_fAdvised=FALSE;
		//m_hEventLog=NULL;
		m_bInEdgeIEMode=FALSE;
		m_iPrevMS_Sum = 0;
		m_iPrevMS = 0;
		m_iBreakerCnt = 0;
	}
	bool IsPageIWebBrowser(IDispatch* pDisp);
	void CloseTabWindow(LPDISPATCH pDisp);
	void CloseTabWindow();
	BOOL IsClosedTabWindow();

	CString m_strTopURL;

	CString m_strSafeGuardURL;
	CString m_strSafeGuard_chkURL;
	DWORD m_iPrevMS_Sum;
	DWORD m_iPrevMS;
	DWORD m_iBreakerCnt;

	BOOL IsSafeGuard(LPCTSTR sURL,DWORD oTimeout=3)
	{
		BOOL bRet=TRUE;
		DWORD dwNow=::GetTickCount();
		DWORD dwPCon=0;

		ATLTRACE(_T("====================\n"));
		//�O��̎��s���Ԃ��Ȃ��B���݂��Z�b�g
		if(m_iPrevMS==0)
			m_iPrevMS=dwNow;
		ATLTRACE(_T("m_iPrevMS:%d\n"),m_iPrevMS);

		dwPCon = dwNow - m_iPrevMS;
		ATLTRACE(_T("dwPCon:%d\n"),dwPCon);
		//�O��ƍ���̎��ԍ�������B
		m_iPrevMS_Sum+=dwPCon;
		ATLTRACE(_T("m_iPrevMS_Sum:%d\n"),m_iPrevMS_Sum);

		//�N���񐔂��C���N�������g
		InterlockedIncrement(&m_iBreakerCnt);
		ATLTRACE(_T("m_iBreakerCnt:%d\n"),m_iBreakerCnt);


		//�������ԁF2�b�ԂɂR��N������Ă���ꍇ�́A���[�v���^��
		if(m_iPrevMS_Sum<=1000)
		{
			//if(g_iBreakerCnt>=2)
			//{
			//	bRet=FALSE;
			//	g_iPrevMS_Sum=0;
			//	g_iPrevMS=0;
			//	g_iBreakerCnt=0;
			//	return bRet;
			//}
			;
		}
		else if(m_iPrevMS_Sum<=2000)
		{
			if(m_iBreakerCnt>=3)
			{
				bRet=FALSE;
				m_iPrevMS_Sum=0;
				m_iPrevMS=0;
				m_iBreakerCnt=0;
				return bRet;
			}
		}
		else if(m_iPrevMS_Sum<=3000)
		{
			if(m_iBreakerCnt>=4)
			{
				bRet=FALSE;
				m_iPrevMS_Sum=0;
				m_iPrevMS=0;
				m_iBreakerCnt=0;
				return bRet;
			}
		}
		else
		{
			//�O��ƍ���̍������Ԃ�3�b�ȏ�̍�������
			if(dwPCon>3000)
			{
				//�J�E���^�[�ނ����Z�b�g����B
				m_iPrevMS_Sum=0;
				m_iPrevMS=0;
				m_iBreakerCnt=0;
			}
			if(m_iBreakerCnt>=10)
			{
				//�J�E���^�[�ނ����Z�b�g����B
				m_iPrevMS_Sum=0;
				m_iPrevMS=0;
				m_iBreakerCnt=0;
			}
		}

		//����URL��3�b�ȓ��̏ꍇ�́A���[�v�̋^������
		if(m_strSafeGuard_chkURL.Compare(sURL)==0)
		{
			if(dwPCon>0 && dwPCon<oTimeout*1000+1000)
			{
				bRet=FALSE;
				m_iPrevMS_Sum=0;
				m_iPrevMS=0;
				m_iBreakerCnt=0;
				return bRet;
			}
		}
		//������O�ɑO��̎��ԂƂ��č���̎��Ԃ��Z�b�g
		m_iPrevMS=dwNow;
		m_strSafeGuard_chkURL=sURL;
		ATLTRACE(_T("m_iPrevMS:%d\n"),m_iPrevMS);
		ATLTRACE(_T("-------------------\n"));
		return bRet;
	}

	CString m_strThinBridge_EXE_FullPath;
	void Navigate_RedirectHTM(CComPtr<IWebBrowser2>  spWebBrowse,CString OptionParam,DWORD dRedirectPageAction,DWORD dwCloseTimeout);


	//MS-Edge��IEMode����p 2021-02-26
	BOOL m_bInEdgeIEMode;

	//ThinApp VirtIE�p
	BOOL m_bInVOS;
	CString m_strVirtIELabel;

	int m_IE_M_Ver;
	CURLRedirectList m_RedirectList;
	CString m_strRedirectFilePath;

	CString m_strUserDataPath;


	void WriteDebugTraceDateTime(LPCTSTR msg,int iLogType,BOOL bForce=FALSE);
	void OpenAnotherBrowser(CURLRedirectDataClass* pRedirectData,CString strURL);

	STDMETHOD(SetSite)(IUnknown *pUnkSite);
DECLARE_REGISTRY_RESOURCEID(IDR_BHOREDIRECTOR1)

DECLARE_NOT_AGGREGATABLE(CBHORedirector)

BEGIN_COM_MAP(CBHORedirector)
	COM_INTERFACE_ENTRY(IBHORedirector)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()

BEGIN_CATEGORY_MAP(CBHORedirector)
	IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
	IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
END_CATEGORY_MAP()

BEGIN_SINK_MAP(CBHORedirector)
//    SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE,DocumentComplete)
	SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, BeforeNavigate)
	SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_NAVIGATECOMPLETE2, NavigateComplete)

//	SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_TITLECHANGE, TitleChange)
//	SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_NEWWINDOW2, NewWindow2)
//	SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_NEWWINDOW3, NewWindow3)
END_SINK_MAP()
    // DWebBrowserEvents2
//	void STDMETHODCALLTYPE DocumentComplete(IDispatch *pDisp, VARIANT *pvarURL);
	void STDMETHODCALLTYPE BeforeNavigate(LPDISPATCH pDisp, VARIANT* URL,
		VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData,
		VARIANT* Headers,   BOOL* Cancel);
	void STDMETHODCALLTYPE NavigateComplete(LPDISPATCH pDisp, VARIANT* URL);

	//void STDMETHODCALLTYPE TitleChange(BSTR bstrText);
	//void STDMETHODCALLTYPE NewWindow2(IDispatch **ppDisp,VARIANT_BOOL *Cancel);
	//void STDMETHODCALLTYPE NewWindow3(IDispatch **ppDisp,VARIANT_BOOL *Cancel,VARIANT Flags,BSTR bstrUrlContext,BSTR bstrUrl);

	CAtlMap<intptr_t, intptr_t> m_MapCloseWebBrowserPtrs;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

//private:
    CComPtr<IWebBrowser2>  m_spWebBrowser;
	BOOL m_fAdvised;
	BOOL IsEmptyPage();
	BOOL m_bQuickRedirectExecFlg;
};

OBJECT_ENTRY_AUTO(__uuidof(BHORedirector), CBHORedirector)
