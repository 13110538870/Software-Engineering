#include "stdafx.h"
#include "InfoFile.h"

CInfoFile::CInfoFile() {

}
CInfoFile::~CInfoFile() {

}
//��ȡ��½��Ϣ
void CInfoFile::ReadLogin(CString &name, CString &pwd) {
	ifstream ifs;
	ifs.open(_F_LOGIN); //���ļ�
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf)); //��ȡÿһ������
	name = CString(buf); //char*ת��ΪCString
	ifs.getline(buf,sizeof(buf));
	pwd = CString(buf);

}
//�޸�����
void CInfoFile::WritePwd(char* name, char* pwd) {
	ofstream ofs;
	ofs.open(_F_LOGIN);
	ofs << name << endl;
	ofs << pwd << endl;
	ofs.close();
}
//��ȡ��Ʒ����
void CInfoFile::ReadDocline() {
	ifstream ifs(_F_STOCK);
	char buf[1024] = { 0 };
	num = 0;
	ls.clear();
	ifs.getline(buf, sizeof(buf)); //����ͷ
	while (!ifs.eof()) //û���ļ�ĩβ
	{
		msg tmp;
		ifs.getline(buf, sizeof(buf));
		num++; //��Ʒ��Ŀ��һ
		char *sst = strtok(buf, "|"); //�ԡ�|�������и�
		if (sst != NULL) {
			tmp.id = atoi(sst);
		}
		else {
			break;
		}
		sst = strtok(NULL, "|");
		tmp.name = sst; //��Ʒ����

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);
		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);
		ls.push_back(tmp);//��������ĺ���

	}
	ifs.close();
}
//��Ʒд���ļ�
void CInfoFile::WriteDocline() {
	ofstream ofs(_F_STOCK);
	if (ls.size() > 0) { //��Ʒ���������ݲ�ִ��
		ofs << "��ƷID|��Ʒ����|��Ʒ�۸�|���" << endl; //д���ͷ
		//ͨ��������ȡ���ض����ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++) {
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->price<< "|";
			ofs << it->num<< endl;
		}
	}
	ofs.close();
}
//�������Ʒ
void CInfoFile::Addline(CString name, int num, int price) {
	ofstream ofs(_F_STOCK);
	ofs << num++ << "|"<<name<<"|"<< price<<"|" << num << endl;
	msg tmp;
	tmp.id = num++;

	//CString תΪstring
	CStringA temp;
	temp = name;
	char* ptr = temp.GetBuffer();
	tmp.name = ptr;

	tmp.price = price;
	tmp.num = num;
	ls.push_back(tmp);
	ofs.close();
}

int main()
{
	return 0;
}

