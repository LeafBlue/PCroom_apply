#pragma once
#include<iostream>
using namespace std;
#include<vector>

class User {
public:
	//编号 学号 教师编号 管理员编号（唯一）
	int u_num;
	char u_name[64];
	char u_pwd[64];

	//权限 0管理员 1老师 2学生
	int priv;

	User();

	User(int u_num,char* u_name,char* u_pwd, int priv);

};

//机房
class Pcroom {
public:
	//共有三个机房
	int p_num;
	char p_name[64];
	

	Pcroom();
	Pcroom(int p_num,char *p_name);
};

//预约信息
class Applyinfo {
public:
	int a_num;
	User user;
	Pcroom pcroom;
	//预约时间：11,12,21,22
	int a_info;
	int inuse;//审核通过1通过0不通过
	int isable;//1可用0不可用

	Applyinfo();
	Applyinfo(int a_num, User& user, Pcroom& pcroom, int a_info);
};

