// DelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(CDelDlg::IDD)
	, m_price(0)
	, m_num(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combol);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_num);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON8, &CDelDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CDelDlg ���

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg ��Ϣ�������


void CDelDlg::OnInitialUpdate()
{
	
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		m_combol.AddString(CString(it->name.c_str()));
	}
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�Ȼ�ȡ��Ʒ����
	int index = m_combol.GetCurSel();
	//����������ȡ����������
	CString name;
	m_combol.GetLBText(index, name);
	//�������ƻ�ȡ���ȣ�����ͬ�����ؼ���
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		if ((CString)it->name.c_str() == name){
			m_price = it->price;
			m_num = it->num;
			//ͬ�����ؼ���
			UpdateData(FALSE);
		}

	}
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_num == 0){
		MessageBox(TEXT("ɾ�����ݲ���Ϊ�գ�"));
		return;
	}
	CString type;
	int index = m_combol.GetCurSel();
	m_combol.GetLBText(index, type);
	CString str;
	str.Format(_T("ɾ����Ʒ�� %s\r\n���ۣ�%d\r\n������%d"), type, m_price, m_num);
	MessageBox(str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		if (type == it->name.c_str()){
			it->num -= m_num;
		}
	}
	file.WriteDocline();
	m_num = 0;
	UpdateData(FALSE);
}


void CDelDlg::OnBnClickedButton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_combol.SetCurSel(0);
	m_num = 0;
	OnCbnSelchangeCombo1();
}
