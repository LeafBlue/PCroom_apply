#pragma once
#include<iostream>
using namespace std;
#include<vector>

class User {
public:
	//��� ѧ�� ��ʦ��� ����Ա��ţ�Ψһ��
	int u_num;
	char u_name[64];
	char u_pwd[64];

	//Ȩ�� 0����Ա 1��ʦ 2ѧ��
	int priv;

	User();

	User(int u_num,char* u_name,char* u_pwd, int priv);

};

//����
class Pcroom {
public:
	//������������
	int p_num;
	char p_name[64];
	

	Pcroom();
	Pcroom(int p_num,char *p_name);
};

//ԤԼ��Ϣ
class Applyinfo {
public:
	int p_num;
	int u_num;
	//ԤԼʱ�䣺11,12,21,22
	int a_info;
	int inuse;

	Applyinfo();
	Applyinfo(int p_num, int u_num, int a_info);
};
