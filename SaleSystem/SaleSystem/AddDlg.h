#pragma once
#include "afxwin.h"



// CAddDlg ������ͼ

class CAddDlg : public CFormView
{
	DECLARE_DYNCREATE(CAddDlg)

protected:
	CAddDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CAddDlg();

public:
	enum { IDD = DIALOG_ADD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combol;
//	CString m_price1;
	int m_num1;
//	int m_price1;
	CString m_name2;
	int m_price2;
	int m_num2;
//	int m_price1;
//	CString m_price1;
	int m_price1;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};

