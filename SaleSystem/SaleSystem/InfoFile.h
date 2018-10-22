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
	//��ȡ��½��Ϣ
	void ReadLogin(CString &name, CString &pwd);
	//�޸�����
	void WritePwd(char* name, char* pwd);
	//��ȡ��Ʒ����
	void ReadDocline();
	//��Ʒд���ļ�
	void WriteDocline();
	//�������Ʒ
	void Addline(CString name, int num, int price);
	list<msg> ls; //�洢��Ʒ����
	int num; //������¼��Ʒ����
};