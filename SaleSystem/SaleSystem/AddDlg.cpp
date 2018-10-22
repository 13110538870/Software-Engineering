// AddDlg.cpp : 实现文件
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


// CAddDlg 诊断

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


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	//初始化下拉框
	CInfoFile file;
	file.ReadDocline();  //把商品读到file对象中
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		//便利商品容器，把容器名称放到下拉框中
		//it->name是String AddString(CString)
		//string->CString(string->char* :调用c_str()方法。char*->CString:CString().)

		m_combol.AddString(CString(it->name.c_str()));
	}
	//默认选中第一个商品
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1(); //初始化第一个商品中的数据
}


void CAddDlg::OnCbnSelchangeCombo1()
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
		if (CString(it->name.c_str()) == name){
			m_price1= it->price;
			//同步到控件中
			UpdateData(FALSE);
		}

	}
}


void CAddDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	//添加按钮功能实现
	//拿到最新的数据
	UpdateData(TRUE);
	if (m_num1 <= 0){
		MessageBox(TEXT("添加的数量必须大于0！"));
		return;
	}
	//获取商品名称
	int index = m_combol.GetCurSel();
	CString name;
	m_combol.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		if (CString(it->name.c_str()) == name){
			//添加库存
			it->num += m_num1;
			m_num1 = 0;
			UpdateData(FALSE);
			MessageBox(TEXT("添加成功！"));
		}
	}
	//把商品同步到文件中
	file.WriteDocline();
}


void CAddDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	m_num1 = 0;
	UpdateData(FALSE);
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	//添加新商品
	//验证数据的有效性
	UpdateData(TRUE);
	if (m_name2.IsEmpty() || m_num2 <= 0 || m_price2 <= 0){
		MessageBox(TEXT("输入信息有误！"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();


	file.Addline(m_name2, m_num2, m_price2);
	file.WriteDocline();
	MessageBox(TEXT("添加新商品成功！"));
	//同步到左侧下拉框中
	m_combol.InsertString(0, m_name2);
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1();
	//清空数据
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);

}


void CAddDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	//清空数据
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);

}
