#include "stdafx.h"
#include "InfoFile.h"

CInfoFile::CInfoFile() {

}
CInfoFile::~CInfoFile() {

}
//读取登陆信息
void CInfoFile::ReadLogin(CString &name, CString &pwd) {
	ifstream ifs;
	ifs.open(_F_LOGIN); //打开文件
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf)); //读取每一行内容
	name = CString(buf); //char*转化为CString
	ifs.getline(buf,sizeof(buf));
	pwd = CString(buf);

}
//修改密码
void CInfoFile::WritePwd(char* name, char* pwd) {
	ofstream ofs;
	ofs.open(_F_LOGIN);
	ofs << name << endl;
	ofs << pwd << endl;
	ofs.close();
}
//读取商品数据
void CInfoFile::ReadDocline() {
	ifstream ifs(_F_STOCK);
	char buf[1024] = { 0 };
	num = 0;
	ls.clear();
	ifs.getline(buf, sizeof(buf)); //读表头
	while (!ifs.eof()) //没到文件末尾
	{
		msg tmp;
		ifs.getline(buf, sizeof(buf));
		num++; //商品数目加一
		char *sst = strtok(buf, "|"); //以”|“进行切割
		if (sst != NULL) {
			tmp.id = atoi(sst);
		}
		else {
			break;
		}
		sst = strtok(NULL, "|");
		tmp.name = sst; //商品名称

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);
		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);
		ls.push_back(tmp);//放在链表的后面

	}
	ifs.close();
}
//商品写入文件
void CInfoFile::WriteDocline() {
	ofstream ofs(_F_STOCK);
	if (ls.size() > 0) { //商品链表有内容才执行
		ofs << "商品ID|商品名称|商品价格|库存" << endl; //写入表头
		//通过迭代器取出特定内容，写入文件，以”|“分隔，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++) {
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->price<< "|";
			ofs << it->num<< endl;
		}
	}
	ofs.close();
}
//添加新商品
void CInfoFile::Addline(CString name, int num, int price) {
	ofstream ofs(_F_STOCK);
	ofs << num++ << "|"<<name<<"|"<< price<<"|" << num << endl;
	msg tmp;
	tmp.id = num++;

	//CString 转为string
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

