#include"method.h"



User loginuser;

void setmenu1() {
	cout << "-------------------------------------" << endl;
	cout << "------------机房预约系统-----------" << endl;
	cout << "--------------请先登录--------------" << endl;
	cout << endl;
	cout << "请输入用户名：" << endl;
	string getu_name;
	cin >> getu_name;
	cout << "请输入密码：" << endl;
	string getu_pwd;
	cin >> getu_pwd;

	setmenu2(getu_name, getu_pwd);
}

//初始化机房数据，此函数只能执行一次
void initpcroom() {
	ofstream ofs;
	ofs.open("pcroom.csv", ios::out | ios::trunc);
	//三个机房
	for (int i = 0; i < 3; i++) {
		Pcroom p;
		p.p_num = (i + 1);
		string pname = to_string(i + 1) + "号机房";
		strcpy_s(p.p_name, pname.c_str());

		ofs << p.p_num << ",";
		ofs << p.p_name << endl;
	}
	ofs.close();
}

//读取机房文件
vector<Pcroom> getpcroom() {
	vector<Pcroom> v_pcroom;
	ifstream ifs("pcroom.csv", ios::in);
	string line;
	while (getline(ifs, line)) {
		vector<string> vstr = splitstr(line,',');

		Pcroom p;
		vector<string>::iterator it = vstr.begin();
		p.p_num = stoi(*it);
		strcpy_s(p.p_name, (*(it + 1)).c_str());

		v_pcroom.push_back(p);
	}

	ifs.close();
	return v_pcroom;
}




void setmenu2(string u_name, string u_pwd) {
	if (u_name == "admin" && u_pwd == "123456") {
		//存入全局变量
		loginuser = User();
		loginuser.u_num = 0;
		strcpy_s(loginuser.u_name, u_name.c_str());
		strcpy_s(loginuser.u_pwd, u_pwd.c_str());
		loginuser.priv = 0;


		cout << "*****************************************************" << endl;
		cout << "**********欢迎登录，您的当前身份是管理员**********" << endl;
		cout << "*****************请选择要执行的操作****************" << endl;
		cout << "********************1，添加账号*********************" << endl;
		cout << "********************2，查看账号*********************" << endl;
		cout << "********************3，查看机房*********************" << endl;
		cout << "********************4，清空预约*********************" << endl;
		cout << "********************5，退出登陆*********************" << endl;
		int inputnum;
		cin >> inputnum;
		if (inputnum == 1) {
			adduser();
			system("pause");
			setmenu2(u_name, u_pwd);
		}
		else if (inputnum == 2) {
			int u_num = 0;
			vector<User> alluser = readfromFile(u_num);
			if (alluser.size() > 0) {
				cout << "用户编号\t" << "用户姓名\t" << "用户密码\t" << "用户权限" << endl;
				for (vector<User>::iterator it = alluser.begin(); it != alluser.end(); it++) {
					cout << (*it).u_num<<"\t\t" << (*it).u_name<<"\t\t" 
						<< (*it).u_pwd << "\t\t" << (((*it).priv == 1) ? "老师" : "学生") << endl;
				}
			}
			system("pause");
			setmenu2(u_name, u_pwd);
		}
		else if (inputnum == 3) {
			vector<Pcroom> pvct = getpcroom();
			if (pvct.size() > 0) {
				cout << "机房编号\t" << "机房名称\t" << endl;
				for (vector<Pcroom>::iterator it = pvct.begin(); it != pvct.end(); it++) {
					cout << (*it).p_num << "\t\t" << (*it).p_name << "\t\t"<< endl;
				}
			}
			system("pause");
			setmenu2(u_name, u_pwd);
		}
		else if (inputnum == 4) {
			cout << "正在清空所有预约信息..." << endl;
			ofstream applyofs;
			applyofs.open("applyinfo.csv",ios::out | ios::trunc);
			applyofs.close();
			system("pause");
			setmenu2(u_name, u_pwd);
		}
		else if (inputnum == 5) {
			loginuser = User();
			cout << "退出登陆..." << endl;
			system("pause");
			setmenu1();
		}
		else {
			cout << "输入的指令码不存在<<";
			system("pause");
			setmenu2(u_name, u_pwd);
		}
	}

	else {
		//从文件中获取对象信息
		int num = 0;
		vector<User> vu = readfromFile(num);
		int isexist = 0;
		for (vector<User>::iterator it = vu.begin(); it != vu.end(); it++) {
			//存储方案：num name pwd priv
			if (u_name == (*it).u_name && u_pwd == (*it).u_pwd) {
				isexist = 1;
				loginuser = (*it);
			}
		}
		if (isexist == 0) {
			cout << "用户名或密码错误" << endl;
			system("pause");
			setmenu1();
		}
		else {
			if (loginuser.priv == 1) {//登录的是老师
				cout << "*****************************************************" << endl;
				cout << "**********欢迎登录，您的当前身份是：老师**********" << endl;
				cout << "*****************请选择要执行的操作****************" << endl;
				cout << "********************1，查看预约*********************" << endl;
				cout << "********************2，审核预约*********************" << endl;
				cout << "********************3，退出登陆*********************" << endl;

				int inputdata = 0;
				cin >> inputdata;
				if (inputdata == 1) {
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if ((*it).isable == 1) {
							cout << "预约编号：" << (*it).a_num << "\t";
							cout << "用户名：" << (*it).user.u_name << "\t";
							cout << "预约机房：" << (*it).pcroom.p_name << "\t";
							cout << "预约时间：" << getapplytime((*it).a_info) << "\t";
							if ((*it).inuse == 0) {
								cout << "审核情况：" << "未通过" << "\t"<<endl;
							}
							else {
								cout << "审核情况：" << "通过" << "\t" << endl;
							}
							
						}
					}
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 2) {
					cout << "请输入你要通过的预约编号" << endl;
					int cross;
					cin >> cross;
					int isexite = 0;
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if ((*it).isable == 1 && (*it).a_num == cross) {
							isexite = 1;
							if ((*it).inuse == 0) {
								(*it).inuse = 1;

								//删除源文件，将vector重新写入新的文件
								saveapply2(vap);
								cout << cross <<"号预约审核通过。" << endl;
							}
							else {
								cout << "这一项已经审核通过了。" << endl;
								system("pause");
								setmenu2(u_name, u_pwd);
							}
						}
					}
					if (isexite == 0) { cout << "输入的编号不存在或者已失效。" << endl; }
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 3) {
					loginuser = User();
					cout << "退出登陆..." << endl;
					system("pause");
					setmenu1();
				}
			}
			else if (loginuser.priv == 2) {//登录的是学生
				cout << "*****************************************************" << endl;
				cout << "**********欢迎登录，您的当前身份是：学生**********" << endl;
				cout << "*****************请选择要执行的操作****************" << endl;
				cout << "********************1，申请预约*********************" << endl;
				cout << "*****************2，查看我的预约********************" << endl;
				cout << "*****************3，查看所有预约********************" << endl;
				cout << "********************4，取消预约*********************" << endl;
				cout << "********************5，退出登陆*********************" << endl;

				int inputdata = 0;
				cin >> inputdata;
				if (inputdata == 1) {
					stuapply();
					cout << "预约成功。" << endl;
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 2) {
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if (((*it).user.u_num = loginuser.u_num) && ((*it).isable == 1)) {
							cout << "预约编号：" << (*it).a_num << "\t";
							cout << "用户名：" << (*it).user.u_name << "\t";
							cout << "预约机房：" << (*it).pcroom.p_name << "\t";
							cout << "预约时间：" << getapplytime((*it).a_info)<< "\t";
							cout << "审核情况：" << (((*it).inuse == 0) ? "未通过" : "通过") << "\t";
							cout << endl;
						}
					}
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 3) {
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if ((*it).isable == 1) {
							cout << "预约编号：" << (*it).a_num << "\t";
							cout << "用户名：" << (*it).user.u_name << "\t";
							cout << "预约机房：" << (*it).pcroom.p_name << "\t";
							cout << "预约时间：" << getapplytime((*it).a_info) << "\t";
							cout << "审核情况：" << (((*it).inuse == 0) ? "未通过" : "通过") << "\t";
							cout << endl;
						}
					}
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 4) {
					cout << "请输入你要取消预约的预约编号：" << endl;
					int delanum;
					cin >> delanum;
					int isexite = 0;
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if ((*it).isable == 1 && (*it).a_num == delanum) {
							isexite = 1;
							if ((*it).user.u_num == loginuser.u_num) {
								(*it).isable = 0;

								//删除源文件，将vector重新写入新的文件
								saveapply2(vap);
								cout << "已取消"<< delanum<<"号的预约" << endl;
							}
							else {
								cout << "这不是你的预约，你无权取消！" << endl;
								system("pause");
								setmenu2(u_name, u_pwd);
							}
						}
					}
					if (isexite == 0) { cout << "输入的编号不存在或者已失效" << endl; }
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 5) {
					loginuser = User();
					cout << "退出登陆..." << endl;
					system("pause");
					setmenu1();
				}

			}
		}
	}
}

string getapplytime(int &applytime) {
	string strtime;
	if (applytime == 11) { return "周一上午"; }
	else if (applytime == 12) { return "周一下午"; }
	else if (applytime == 21) { return "周二上午"; }
	else if (applytime == 22) { return "周二下午"; }
	else if (applytime == 31) { return "周三上午"; }
	else if (applytime == 32) { return "周三下午"; }
	else if (applytime == 41) { return "周四上午"; }
	else if (applytime == 42) { return "周四下午"; }
	else if (applytime == 51) { return "周五上午"; }
	else if (applytime == 52) { return "周五下午"; }
}

void stuapply() {
	vector<Applyinfo> vap = readapplyfile();
	cout << "请输入你要预约的机房号码：" << endl;
	cout << "1号机房，2号机房，3号机房" << endl;
	int pcroomdata;
	cin >> pcroomdata;
	cout << "当前机房预约情况：" << endl;
	map<int, int> m_apply = coutapply(pcroomdata);
	cout << "时间/日期\t周  一\t\t周  二\t\t周  三\t\t周  四\t\t周  五\t" << endl;
	cout << "上午\t\t";
	cout << ((m_apply[11] == 0) ? "11 可预约" : "11 不可预约") << "\t";
	cout << ((m_apply[21] == 0) ? "21 可预约" : "21 不可预约") << "\t";
	cout << ((m_apply[31] == 0) ? "31 可预约" : "31 不可预约") << "\t";
	cout << ((m_apply[41] == 0) ? "41 可预约" : "41 不可预约") << "\t";
	cout << ((m_apply[51] == 0) ? "51 可预约" : "51 不可预约") << "\t";
	cout << endl;
	cout << "下午\t\t";
	cout << ((m_apply[11] == 0) ? "12 可预约" : "12 不可预约") << "\t";
	cout << ((m_apply[21] == 0) ? "22 可预约" : "22 不可预约") << "\t";
	cout << ((m_apply[31] == 0) ? "32 可预约" : "32 不可预约") << "\t";
	cout << ((m_apply[41] == 0) ? "42 可预约" : "42 不可预约") << "\t";
	cout << ((m_apply[51] == 0) ? "52 可预约" : "52 不可预约") << "\t";
	cout << endl;

	cout << "请输入你要预约的时段对应号码：" << endl;
	int applytime;
	cin >> applytime;
	if (m_apply[applytime] == 0) {
		Applyinfo newapply;
		newapply.a_num = vap.size() + 1;
		newapply.inuse = 0;
		newapply.a_info = applytime;
		newapply.user = loginuser;
		Pcroom tem_p;
		tem_p.p_num = pcroomdata;
		if (pcroomdata == 1) { strcpy_s(tem_p.p_name, "1号机房"); }
		else if (pcroomdata == 2) { strcpy_s(tem_p.p_name, "2号机房"); }
		else if (pcroomdata == 3) { strcpy_s(tem_p.p_name, "3号机房"); }
		newapply.pcroom = tem_p;
		newapply.isable = 1;
		saveapplyfile(newapply);
	}
	else {
		cout << "输入的时段不可预约！" << endl;
		system("pause");
		stuapply();
	}
}

map<int, int> coutapply(int &pcroomdata) {
	vector<Applyinfo> vapp = readapplyfile();
	map<int, int> m;
	//0代表审核未通过，可以预约
	m[11] = 0;m[21] = 0;m[31] = 0;m[41] = 0;m[51] = 0;
	m[12] = 0;m[22] = 0;m[32] = 0;m[42] = 0;m[52] = 0;
	if (vapp.size() > 0) {
		for (vector<Applyinfo>::iterator it = vapp.begin();it != vapp.end(); it++) {
			if ((*it).pcroom.p_num == pcroomdata && (*it).inuse == 1 && (*it).isable ==1) {
				m[(*it).a_info] = 1;
			}
		}
	}
	
	return m;
}

void adduser() {
	cout << "请输入要添加的类型：1，老师，2，学生" << endl;
	int priv;
	cin >> priv;
	int the_num;
	readfromFile(the_num);

	if (priv != 1 && priv != 2) {
		cout << "输入的指令码不存在"<<endl;
		system("pause");
		adduser();
	}
	else {
		User u;
		u.u_num = the_num + 1;

		cout << "请输入要添加的用户姓名：" << endl;
		string inputname;
		cin >> inputname;
		strcpy_s(u.u_name, inputname.c_str());

		cout << "请输入用户密码：" << endl;
		string inputpwd;
		cin >> inputpwd;
		strcpy_s(u.u_pwd, inputpwd.c_str());

		u.priv = priv;
		//将数据添加到文件里头去
		addinfile(u);
	}
}

//从文件中读取所有数据，并返回到vector
vector<User> readfromFile(int &the_num) {
	the_num = 0;
	vector<User> v;
	//如果文件不存在 则创建文件
	ofstream o("user.csv",ios::out|ios::app);
	o.close();
	//读取文件
	ifstream ifs;
	char ch;
	ifs >> ch;
	ifs.open("user.csv", ios::in);
	if (ifs.eof()) {
		the_num = 0;
		return v;
	}
	else {
		string line;
		while (getline(ifs, line)) {
			vector<string> vstr = splitstr(line,',');
			vector<string>::iterator it = vstr.begin();
			//存储方案：num name pwd priv

			User u;
			u.u_num = stoi(*it);
			strcpy_s(u.u_name, (*(it + 1)).c_str());
			strcpy_s(u.u_pwd, (*(it + 2)).c_str());
			u.priv = stoi(*(it + 3));



			v.push_back(u);
			the_num++;
		}
	}
	o.close();
}

void addinfile(User &adduser) {
	ofstream ofs;
	ofs.open("user.csv", ios::out | ios::app);
	//存储方案：num name pwd priv
	ofs << adduser.u_num << ",";
	ofs << adduser.u_name << ",";
	ofs << adduser.u_pwd << ",";
	ofs << adduser.priv << endl;

	ofs.close();
}

//读取预约文件
vector<Applyinfo> readapplyfile() {
	vector<Applyinfo> vapply;
	//如果文件不存在则创建文件
	ofstream ofs("applyinfo.csv", ios::out | ios::app);
	ofs.close();

	ifstream ifs;
	
	char ch;
	ifs >> ch;
	ifs.open("applyinfo.csv", ios::in);
	if (ifs.eof()) {
		return vapply;
	}
	string line;
	while (getline(ifs, line)) {
		vector<string> vstr = splitstr(line, ',');
		vector<string>::iterator it = vstr.begin();
		Applyinfo ap;
		ap.a_num = stoi(*it);

		User user;
		user.u_num = stoi(*(it + 1));
		strcpy_s(user.u_name, (*(it + 2)).c_str());
		strcpy_s(user.u_pwd, (*(it + 3)).c_str());
		user.priv = stoi(*(it + 4));
		ap.user = user;

		Pcroom p;
		p.p_num = stoi(*(it + 5));
		strcpy_s(p.p_name, (*(it + 6)).c_str());
		ap.pcroom = p;

		ap.a_info = stoi(*(it + 7));
		ap.inuse = stoi(*(it + 8));
		ap.isable = stoi(*(it + 9));
		vapply.push_back(ap);
	}

	return vapply;
}

//将vector写入预约文件
void saveapply2(vector<Applyinfo> &v) {
	ofstream ofs;
	ofs.open("applyinfo.csv", ios::out | ios::trunc);

	if (ofs.is_open()) {
		for (vector<Applyinfo>::iterator it = v.begin();it != v.end();it++) {
			ofs << (*it).a_num << ",";

			User user = (*it).user;
			ofs << user.u_num << ",";
			ofs << user.u_name << ",";
			ofs << user.u_pwd << ",";
			ofs << user.priv << ",";

			Pcroom p = (*it).pcroom;
			ofs << p.p_num << ",";
			ofs << p.p_name << ",";

			ofs << (*it).a_info << ",";
			ofs << (*it).inuse << ",";
			ofs << (*it).isable << endl;
		}
	}
	else {
		cout << "文件打开失败" << endl;
	}
}


//写入预约文件
void saveapplyfile(Applyinfo & applyinfo) {
	ofstream ofs;
	ofs.open("applyinfo.csv", ios::out | ios::app);

	if (ofs.is_open()) {
		ofs << applyinfo.a_num << ",";

		User user = applyinfo.user;
		ofs << user.u_num << ",";
		ofs << user.u_name << ",";
		ofs << user.u_pwd << ",";
		ofs << user.priv << ",";

		Pcroom p = applyinfo.pcroom;
		ofs << p.p_num << ",";
		ofs << p.p_name << ",";

		ofs << applyinfo.a_info << ",";
		ofs << applyinfo.inuse << ","; 
		ofs << applyinfo.isable<< endl;
	}
	else {
		cout << "文件打开失败" << endl;
	}

	ofs.close();
}


//根据逗号截取字符串
vector<string> splitstr(string str, char keyword) {
	vector<string> vsplit;
	int data = count(str.begin(), str.end(), keyword);

	int inital = 0;
	for (int i = 0; i < data; i++) {
		int index1 = str.find(keyword, inital);
		vsplit.push_back(str.substr(inital, (index1 - inital)));
		inital = index1 + 1;
	}
	vsplit.push_back(str.substr(inital));
	return vsplit;
}