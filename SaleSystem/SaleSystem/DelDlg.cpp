// DelDlg.cpp : 实现文件
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


// CDelDlg 诊断

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


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
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
	// TODO:  在此添加控件通知处理程序代码
	//先获取商品名称
	int index = m_combol.GetCurSel();
	//根据索引获取到具体内容
	CString name;
	m_combol.GetLBText(index, name);
	//根据名称获取库存等，并且同步到控件中
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		if ((CString)it->name.c_str() == name){
			m_price = it->price;
			m_num = it->num;
			//同步到控件中
			UpdateData(FALSE);
		}

	}
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_num == 0){
		MessageBox(TEXT("删除内容不能为空！"));
		return;
	}
	CString type;
	int index = m_combol.GetCurSel();
	m_combol.GetLBText(index, type);
	CString str;
	str.Format(_T("删除商品： %s\r\n单价：%d\r\n个数：%d"), type, m_price, m_num);
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
	// TODO:  在此添加控件通知处理程序代码
	m_combol.SetCurSel(0);
	m_num = 0;
	OnCbnSelchangeCombo1();
}
