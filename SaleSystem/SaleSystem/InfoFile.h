#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg {
	int id;
	string name;
	int price;
	int num;
};

class CInfoFile {
public:
	CInfoFile();
	~CInfoFile();
	//读取登陆信息
	void ReadLogin(CString &name, CString &pwd);
	//修改密码
	void WritePwd(char* name, char* pwd);
	//读取商品数据
	void ReadDocline();
	//商品写入文件
	void WriteDocline();
	//添加新商品
	void Addline(CString name, int num, int price);
	list<msg> ls; //存储商品容器
	int num; //用来记录商品个数
};