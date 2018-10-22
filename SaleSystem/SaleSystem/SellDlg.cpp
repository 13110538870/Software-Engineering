// SellDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SellDlg.h"
#include "InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(CSellDlg::IDD)
	, m_price(0)
	, m_left(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combol);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_left);
	DDX_Text(pDX, IDC_EDIT5, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSellDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSellDlg ���

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg ��Ϣ�������


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	//��ʼ��������Ϣ
	//��ʼ��������
	CInfoFile file;
	file.ReadDocline();  //����Ʒ����file������
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();it++){
		//������Ʒ���������������Ʒŵ���������
		//it->name��String AddString(CString)
		//string->CString(string->char* :����c_str()������char*->CString:CString().)

		m_combol.AddString(CString(it->name.c_str()));
	}
	//Ĭ��ѡ�е�һ����Ʒ
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1(); //��ʼ����һ����Ʒ�е�����
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�л���Ʒ�¼�
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
			m_left = it->num;
			//ͬ�����ؼ���
			UpdateData(FALSE);
		}
	
	}
}


void CSellDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����Ĵ���ʵ��
	if (m_num <= 0){
		MessageBox(TEXT("����������������0��"));
		return;
	}
	else if (m_num > m_left){
		MessageBox(TEXT("������������ܴ��ڿ�棡"));
		return;
	}
	else{
		//���򣺻�ȡ��������Ʒ����
		int index = m_combol.GetCurSel();
		//����������ȡ����������
		CString name;
		m_combol.GetLBText(index, name);
		//�������ƻ�ȡ���ȣ�����ͬ�����ؼ���
		CInfoFile file;
		file.ReadDocline();
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
			if ((CString)it->name.c_str() == name){
				//ͬ�������
				it->num -= m_num;
				m_left = it->num;

				CString str;
				str.Format(_T("��Ʒ: %s \r\n���ۣ�%d \r\n������%d \r\n�ܼۣ�%d"), name, m_price, m_num, m_price*m_num);
				m_sellInfo = str;
				UpdateData(FALSE);
				MessageBox(TEXT("����ɹ���"));

			}
		}
		//����������д���ļ���
		file.WriteDocline();
		//�������
		m_num = 0;
		m_sellInfo.Empty();
		UpdateData(FALSE);
	}
}


void CSellDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ȡ����ť
	m_num = 0;
	UpdateData(FALSE);
	//Ĭ��ѡ�е�һ��
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1(); //��ʼ����һ����Ʒ�е�����

}
