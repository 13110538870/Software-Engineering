// SellDlg.cpp : 实现文件
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


// CSellDlg 诊断

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


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	//初始化订单信息
	//初始化下拉框
	CInfoFile file;
	file.ReadDocline();  //把商品读到file对象中
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();it++){
		//便利商品容器，把容器名称放到下拉框中
		//it->name是String AddString(CString)
		//string->CString(string->char* :调用c_str()方法。char*->CString:CString().)

		m_combol.AddString(CString(it->name.c_str()));
	}
	//默认选中第一个商品
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1(); //初始化第一个商品中的数据
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	//切换商品事件
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
			m_left = it->num;
			//同步到控件中
			UpdateData(FALSE);
		}
	
	}
}


void CSellDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
	//购买的代码实现
	if (m_num <= 0){
		MessageBox(TEXT("购买的数量必须大于0！"));
		return;
	}
	else if (m_num > m_left){
		MessageBox(TEXT("购买的数量不能大于库存！"));
		return;
	}
	else{
		//购买：获取到具体商品名称
		int index = m_combol.GetCurSel();
		//根据索引获取到具体内容
		CString name;
		m_combol.GetLBText(index, name);
		//根据名称获取库存等，并且同步到控件中
		CInfoFile file;
		file.ReadDocline();
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
			if ((CString)it->name.c_str() == name){
				//同步库存量
				it->num -= m_num;
				m_left = it->num;

				CString str;
				str.Format(_T("商品: %s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name, m_price, m_num, m_price*m_num);
				m_sellInfo = str;
				UpdateData(FALSE);
				MessageBox(TEXT("购买成功！"));

			}
		}
		//把最新数据写到文件中
		file.WriteDocline();
		//清空数据
		m_num = 0;
		m_sellInfo.Empty();
		UpdateData(FALSE);
	}
}


void CSellDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	//取消按钮
	m_num = 0;
	UpdateData(FALSE);
	//默认选中第一个
	m_combol.SetCurSel(0);
	OnCbnSelchangeCombo1(); //初始化第一个商品中的数据

}
