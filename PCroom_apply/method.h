#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include"classhead.h"
#include<fstream>
#include<string>
#include<map>

void setmenu1();
void initpcroom();
vector<Pcroom> getpcroom();
void setmenu2(string u_name, string u_pwd);
string getapplytime(int& applytime);
void stuapply();
map<int, int> coutapply(int& pcroomdata);
void adduser();
vector<User> readfromFile(int& the_num);
void addinfile(User& adduser);
vector<Applyinfo> readapplyfile();
void saveapply2(vector<Applyinfo>& v);
void saveapplyfile(Applyinfo& applyinfo);
vector<string> splitstr(string str, char keyword);