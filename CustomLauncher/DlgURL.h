#pragma once


// CDlgURL �_�C�A���O

class CDlgURL : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgURL)

public:
	CDlgURL(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CDlgURL();
	CString m_strURL;
// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
