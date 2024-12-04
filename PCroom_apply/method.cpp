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
		strcpy_s(p.p_name, (i + 1) + "号机房");

		ofs << p.p_num << ",";
		ofs << p.p_name << endl;
	}
	ofs.close();
}

//读取csv文件
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
					cout << (*it).u_num<<"\t" << (*it).u_name<<"\t" 
						<< (*it).u_pwd << "\t" << (((*it).priv == 1) ? "老师" : "学生") << endl;
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
					cout << (*it).p_num << "\t" << (*it).p_name << "\t"<< endl;
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

	}
}

void adduser() {
	cout << "请输入要添加的类型：1，老师，2，学生" << endl;
	int priv;
	cin >> priv;
	int the_num;
	readfromFile(the_num);

	if (priv != 1 && priv != 2) {
		cout << "输入的指令码不存在<<";
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
		strcpy_s(u.u_pwd, inputname.c_str());

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
			strcpy(u.u_name, (*(it + 1)).c_str());
			strcpy(u.u_pwd, (*(it + 2)).c_str());
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