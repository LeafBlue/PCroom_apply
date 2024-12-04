#include"classhead.h"

User::User() {}

User::User(int u_num, char* u_name, char* u_pwd, int priv){
	this->u_num = u_num;
	strcpy_s(this->u_name,u_name);
	strcpy_s(this->u_pwd, u_pwd);
	this->priv = priv;
}

Pcroom::Pcroom() {}
Pcroom::Pcroom(int p_num, char* p_name) {
	this->p_num = p_num;
	strcpy_s(this->p_name, p_name);
}


Applyinfo::Applyinfo(){}
Applyinfo::Applyinfo(int p_num, int u_num, int a_info) {
	this->p_num = p_num;
	this->u_num = u_num;
	this->a_info = a_info;
	this->inuse = 1;//0·ñ1ÊÇ
}

