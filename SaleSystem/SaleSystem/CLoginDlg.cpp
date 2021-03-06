// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT1, &CLoginDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//登陆按钮点击事件
	UpdateData(TRUE); //拿到最新的值进行判断

	//输入不能为空
	if (m_user.IsEmpty() || m_pwd.IsEmpty()) {
		MessageBox(TEXT("输入不能为空！"));
		return;
	}
	//获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (name == m_user) {
		if (pwd == m_pwd) {
			CDialog::OnCancel(); //关闭当前对话框
		}
		else
			MessageBox(TEXT("密码输入有误！"));
	}
	else {
		MessageBox(TEXT("用户名输入有误！"));

	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//默认初始化信息
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_user = name;
	m_pwd = pwd;
	//同步到控件中去
	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//取消按钮
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	//退出整个程序
	exit(0);
}


void CLoginDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
