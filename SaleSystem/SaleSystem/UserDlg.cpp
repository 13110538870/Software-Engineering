// UserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "UserDlg.h"
#include "InfoFile.h"

// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(CUserDlg::IDD)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_EN_CHANGE(IDC_EDIT3, &CUserDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg ���

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg ��Ϣ�������


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	//��ʼ��
	m_user = TEXT("����Ա");
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	m_name = name;
	UpdateData(FALSE);

}


void CUserDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�޸�����
	//���õ����µ�ֵ
	UpdateData(TRUE);
	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty()){
		MessageBox(TEXT("�������ݲ���Ϊ�գ�"));
		return;
	}
	//�������ȷ������Ҫһ��
	if (m_newPwd != m_surePwd){
		MessageBox(TEXT("������������벻һ�£�"));
		return;
	}
	//������;����벻����ͬ
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (m_newPwd == pwd){
		MessageBox(TEXT("�����벻�ܺ;�������ͬ��"));
		return;
	}
	//CStringתchar*
	CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
	MessageBox(TEXT("�����޸ĳɹ���"));
	//�������
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ȡ����ť
	//�������
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}
