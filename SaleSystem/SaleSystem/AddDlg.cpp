// AddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(CAddDlg::IDD)
	, m_num1(0)
	, m_price1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combol);
	//  DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT2, m_num1);
	//  DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT8, m_name2);
	DDX_Text(pDX, IDC_EDIT6, m_price2);
	DDX_Text(pDX, IDC_EDIT7, m_num2);
	//  DDX_Text(pDX, IDC_EDIT1, m_price1);
	//  DDX_Text(pDX, IDC_EDIT9, m_price1);
	DDX_Text(pDX, IDC_EDIT3, m_price1);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAddDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAddDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CAddDlg ���

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg ��Ϣ�������


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	//��ʼ��������
	CInfoFile file;
	file.ReadDocline();  //����Ʒ����file������
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		//������Ʒ���������������Ʒŵ���������
		//it->name��String AddString(CString)
		//string->CString(string->char* :����c_str()������char*->CString:CString().)

		m_combol.AddString(CString(it->name.c_str()));
	}
	//Ĭ��ѡ�е�һ����Ʒ
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1(); //��ʼ����һ����Ʒ�е�����
}


void CAddDlg::OnCbnSelchangeCombo1()
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
		if (CString(it->name.c_str()) == name){
			m_price1= it->price;
			//ͬ�����ؼ���
			UpdateData(FALSE);
		}

	}
}


void CAddDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��Ӱ�ť����ʵ��
	//�õ����µ�����
	UpdateData(TRUE);
	if (m_num1 <= 0){
		MessageBox(TEXT("��ӵ������������0��"));
		return;
	}
	//��ȡ��Ʒ����
	int index = m_combol.GetCurSel();
	CString name;
	m_combol.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		if (CString(it->name.c_str()) == name){
			//��ӿ��
			it->num += m_num1;
			m_num1 = 0;
			UpdateData(FALSE);
			MessageBox(TEXT("��ӳɹ���"));
		}
	}
	//����Ʒͬ�����ļ���
	file.WriteDocline();
}


void CAddDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_num1 = 0;
	UpdateData(FALSE);
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�������Ʒ
	//��֤���ݵ���Ч��
	UpdateData(TRUE);
	if (m_name2.IsEmpty() || m_num2 <= 0 || m_price2 <= 0){
		MessageBox(TEXT("������Ϣ����"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();


	file.Addline(m_name2, m_num2, m_price2);
	file.WriteDocline();
	MessageBox(TEXT("�������Ʒ�ɹ���"));
	//ͬ���������������
	m_combol.InsertString(0, m_name2);
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1();
	//�������
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);

}


void CAddDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�������
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);

}
