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
	int a_num;
	User user;
	Pcroom pcroom;
	//ԤԼʱ�䣺11,12,21,22
	int a_info;
	int inuse;//���ͨ��1ͨ��0��ͨ��
	int isable;//1����0������

	Applyinfo();
	Applyinfo(int a_num, User& user, Pcroom& pcroom, int a_info);
};

