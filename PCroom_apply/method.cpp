#include"method.h"



User loginuser;

void setmenu1() {
	cout << "-------------------------------------" << endl;
	cout << "------------����ԤԼϵͳ-----------" << endl;
	cout << "--------------���ȵ�¼--------------" << endl;
	cout << endl;
	cout << "�������û�����" << endl;
	string getu_name;
	cin >> getu_name;
	cout << "���������룺" << endl;
	string getu_pwd;
	cin >> getu_pwd;

	setmenu2(getu_name, getu_pwd);
}

//��ʼ���������ݣ��˺���ֻ��ִ��һ��
void initpcroom() {
	ofstream ofs;
	ofs.open("pcroom.csv", ios::out | ios::trunc);
	//��������
	for (int i = 0; i < 3; i++) {
		Pcroom p;
		p.p_num = (i + 1);
		string pname = to_string(i + 1) + "�Ż���";
		strcpy_s(p.p_name, pname.c_str());

		ofs << p.p_num << ",";
		ofs << p.p_name << endl;
	}
	ofs.close();
}

//��ȡ�����ļ�
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
		//����ȫ�ֱ���
		loginuser = User();
		loginuser.u_num = 0;
		strcpy_s(loginuser.u_name, u_name.c_str());
		strcpy_s(loginuser.u_pwd, u_pwd.c_str());
		loginuser.priv = 0;


		cout << "*****************************************************" << endl;
		cout << "**********��ӭ��¼�����ĵ�ǰ����ǹ���Ա**********" << endl;
		cout << "*****************��ѡ��Ҫִ�еĲ���****************" << endl;
		cout << "********************1������˺�*********************" << endl;
		cout << "********************2���鿴�˺�*********************" << endl;
		cout << "********************3���鿴����*********************" << endl;
		cout << "********************4�����ԤԼ*********************" << endl;
		cout << "********************5���˳���½*********************" << endl;
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
				cout << "�û����\t" << "�û�����\t" << "�û�����\t" << "�û�Ȩ��" << endl;
				for (vector<User>::iterator it = alluser.begin(); it != alluser.end(); it++) {
					cout << (*it).u_num<<"\t\t" << (*it).u_name<<"\t\t" 
						<< (*it).u_pwd << "\t\t" << (((*it).priv == 1) ? "��ʦ" : "ѧ��") << endl;
				}
			}
			system("pause");
			setmenu2(u_name, u_pwd);
		}
		else if (inputnum == 3) {
			vector<Pcroom> pvct = getpcroom();
			if (pvct.size() > 0) {
				cout << "�������\t" << "��������\t" << endl;
				for (vector<Pcroom>::iterator it = pvct.begin(); it != pvct.end(); it++) {
					cout << (*it).p_num << "\t\t" << (*it).p_name << "\t\t"<< endl;
				}
			}
			system("pause");
			setmenu2(u_name, u_pwd);
		}
		else if (inputnum == 4) {
			cout << "�����������ԤԼ��Ϣ..." << endl;
			ofstream applyofs;
			applyofs.open("applyinfo.csv",ios::out | ios::trunc);
			applyofs.close();
			system("pause");
			setmenu2(u_name, u_pwd);
		}
		else if (inputnum == 5) {
			loginuser = User();
			cout << "�˳���½..." << endl;
			system("pause");
			setmenu1();
		}
		else {
			cout << "�����ָ���벻����<<";
			system("pause");
			setmenu2(u_name, u_pwd);
		}
	}

	else {
		//���ļ��л�ȡ������Ϣ
		int num = 0;
		vector<User> vu = readfromFile(num);
		int isexist = 0;
		for (vector<User>::iterator it = vu.begin(); it != vu.end(); it++) {
			//�洢������num name pwd priv
			if (u_name == (*it).u_name && u_pwd == (*it).u_pwd) {
				isexist = 1;
				loginuser = (*it);
			}
		}
		if (isexist == 0) {
			cout << "�û������������" << endl;
			system("pause");
			setmenu1();
		}
		else {
			if (loginuser.priv == 1) {//��¼������ʦ
				cout << "*****************************************************" << endl;
				cout << "**********��ӭ��¼�����ĵ�ǰ����ǣ���ʦ**********" << endl;
				cout << "*****************��ѡ��Ҫִ�еĲ���****************" << endl;
				cout << "********************1���鿴ԤԼ*********************" << endl;
				cout << "********************2�����ԤԼ*********************" << endl;
				cout << "********************3���˳���½*********************" << endl;

				int inputdata = 0;
				cin >> inputdata;
				if (inputdata == 1) {
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if ((*it).isable == 1) {
							cout << "ԤԼ��ţ�" << (*it).a_num << "\t";
							cout << "�û�����" << (*it).user.u_name << "\t";
							cout << "ԤԼ������" << (*it).pcroom.p_name << "\t";
							cout << "ԤԼʱ�䣺" << getapplytime((*it).a_info) << "\t";
							if ((*it).inuse == 0) {
								cout << "��������" << "δͨ��" << "\t"<<endl;
							}
							else {
								cout << "��������" << "ͨ��" << "\t" << endl;
							}
							
						}
					}
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 2) {
					cout << "��������Ҫͨ����ԤԼ���" << endl;
					int cross;
					cin >> cross;
					int isexite = 0;
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if ((*it).isable == 1 && (*it).a_num == cross) {
							isexite = 1;
							if ((*it).inuse == 0) {
								(*it).inuse = 1;

								//ɾ��Դ�ļ�����vector����д���µ��ļ�
								saveapply2(vap);
								cout << cross <<"��ԤԼ���ͨ����" << endl;
							}
							else {
								cout << "��һ���Ѿ����ͨ���ˡ�" << endl;
								system("pause");
								setmenu2(u_name, u_pwd);
							}
						}
					}
					if (isexite == 0) { cout << "����ı�Ų����ڻ�����ʧЧ��" << endl; }
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 3) {
					loginuser = User();
					cout << "�˳���½..." << endl;
					system("pause");
					setmenu1();
				}
			}
			else if (loginuser.priv == 2) {//��¼����ѧ��
				cout << "*****************************************************" << endl;
				cout << "**********��ӭ��¼�����ĵ�ǰ����ǣ�ѧ��**********" << endl;
				cout << "*****************��ѡ��Ҫִ�еĲ���****************" << endl;
				cout << "********************1������ԤԼ*********************" << endl;
				cout << "*****************2���鿴�ҵ�ԤԼ********************" << endl;
				cout << "*****************3���鿴����ԤԼ********************" << endl;
				cout << "********************4��ȡ��ԤԼ*********************" << endl;
				cout << "********************5���˳���½*********************" << endl;

				int inputdata = 0;
				cin >> inputdata;
				if (inputdata == 1) {
					stuapply();
					cout << "ԤԼ�ɹ���" << endl;
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 2) {
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if (((*it).user.u_num = loginuser.u_num) && ((*it).isable == 1)) {
							cout << "ԤԼ��ţ�" << (*it).a_num << "\t";
							cout << "�û�����" << (*it).user.u_name << "\t";
							cout << "ԤԼ������" << (*it).pcroom.p_name << "\t";
							cout << "ԤԼʱ�䣺" << getapplytime((*it).a_info)<< "\t";
							cout << "��������" << (((*it).inuse == 0) ? "δͨ��" : "ͨ��") << "\t";
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
							cout << "ԤԼ��ţ�" << (*it).a_num << "\t";
							cout << "�û�����" << (*it).user.u_name << "\t";
							cout << "ԤԼ������" << (*it).pcroom.p_name << "\t";
							cout << "ԤԼʱ�䣺" << getapplytime((*it).a_info) << "\t";
							cout << "��������" << (((*it).inuse == 0) ? "δͨ��" : "ͨ��") << "\t";
							cout << endl;
						}
					}
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 4) {
					cout << "��������Ҫȡ��ԤԼ��ԤԼ��ţ�" << endl;
					int delanum;
					cin >> delanum;
					int isexite = 0;
					vector<Applyinfo> vap = readapplyfile();
					for (vector<Applyinfo>::iterator it = vap.begin();it != vap.end(); it++) {
						if ((*it).isable == 1 && (*it).a_num == delanum) {
							isexite = 1;
							if ((*it).user.u_num == loginuser.u_num) {
								(*it).isable = 0;

								//ɾ��Դ�ļ�����vector����д���µ��ļ�
								saveapply2(vap);
								cout << "��ȡ��"<< delanum<<"�ŵ�ԤԼ" << endl;
							}
							else {
								cout << "�ⲻ�����ԤԼ������Ȩȡ����" << endl;
								system("pause");
								setmenu2(u_name, u_pwd);
							}
						}
					}
					if (isexite == 0) { cout << "����ı�Ų����ڻ�����ʧЧ" << endl; }
					system("pause");
					setmenu2(u_name, u_pwd);
				}
				else if (inputdata == 5) {
					loginuser = User();
					cout << "�˳���½..." << endl;
					system("pause");
					setmenu1();
				}

			}
		}
	}
}

string getapplytime(int &applytime) {
	string strtime;
	if (applytime == 11) { return "��һ����"; }
	else if (applytime == 12) { return "��һ����"; }
	else if (applytime == 21) { return "�ܶ�����"; }
	else if (applytime == 22) { return "�ܶ�����"; }
	else if (applytime == 31) { return "��������"; }
	else if (applytime == 32) { return "��������"; }
	else if (applytime == 41) { return "��������"; }
	else if (applytime == 42) { return "��������"; }
	else if (applytime == 51) { return "��������"; }
	else if (applytime == 52) { return "��������"; }
}

void stuapply() {
	vector<Applyinfo> vap = readapplyfile();
	cout << "��������ҪԤԼ�Ļ������룺" << endl;
	cout << "1�Ż�����2�Ż�����3�Ż���" << endl;
	int pcroomdata;
	cin >> pcroomdata;
	cout << "��ǰ����ԤԼ�����" << endl;
	map<int, int> m_apply = coutapply(pcroomdata);
	cout << "ʱ��/����\t��  һ\t\t��  ��\t\t��  ��\t\t��  ��\t\t��  ��\t" << endl;
	cout << "����\t\t";
	cout << ((m_apply[11] == 0) ? "11 ��ԤԼ" : "11 ����ԤԼ") << "\t";
	cout << ((m_apply[21] == 0) ? "21 ��ԤԼ" : "21 ����ԤԼ") << "\t";
	cout << ((m_apply[31] == 0) ? "31 ��ԤԼ" : "31 ����ԤԼ") << "\t";
	cout << ((m_apply[41] == 0) ? "41 ��ԤԼ" : "41 ����ԤԼ") << "\t";
	cout << ((m_apply[51] == 0) ? "51 ��ԤԼ" : "51 ����ԤԼ") << "\t";
	cout << endl;
	cout << "����\t\t";
	cout << ((m_apply[11] == 0) ? "12 ��ԤԼ" : "12 ����ԤԼ") << "\t";
	cout << ((m_apply[21] == 0) ? "22 ��ԤԼ" : "22 ����ԤԼ") << "\t";
	cout << ((m_apply[31] == 0) ? "32 ��ԤԼ" : "32 ����ԤԼ") << "\t";
	cout << ((m_apply[41] == 0) ? "42 ��ԤԼ" : "42 ����ԤԼ") << "\t";
	cout << ((m_apply[51] == 0) ? "52 ��ԤԼ" : "52 ����ԤԼ") << "\t";
	cout << endl;

	cout << "��������ҪԤԼ��ʱ�ζ�Ӧ���룺" << endl;
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
		if (pcroomdata == 1) { strcpy_s(tem_p.p_name, "1�Ż���"); }
		else if (pcroomdata == 2) { strcpy_s(tem_p.p_name, "2�Ż���"); }
		else if (pcroomdata == 3) { strcpy_s(tem_p.p_name, "3�Ż���"); }
		newapply.pcroom = tem_p;
		newapply.isable = 1;
		saveapplyfile(newapply);
	}
	else {
		cout << "�����ʱ�β���ԤԼ��" << endl;
		system("pause");
		stuapply();
	}
}

map<int, int> coutapply(int &pcroomdata) {
	vector<Applyinfo> vapp = readapplyfile();
	map<int, int> m;
	//0�������δͨ��������ԤԼ
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
	cout << "������Ҫ��ӵ����ͣ�1����ʦ��2��ѧ��" << endl;
	int priv;
	cin >> priv;
	int the_num;
	readfromFile(the_num);

	if (priv != 1 && priv != 2) {
		cout << "�����ָ���벻����"<<endl;
		system("pause");
		adduser();
	}
	else {
		User u;
		u.u_num = the_num + 1;

		cout << "������Ҫ��ӵ��û�������" << endl;
		string inputname;
		cin >> inputname;
		strcpy_s(u.u_name, inputname.c_str());

		cout << "�������û����룺" << endl;
		string inputpwd;
		cin >> inputpwd;
		strcpy_s(u.u_pwd, inputpwd.c_str());

		u.priv = priv;
		//��������ӵ��ļ���ͷȥ
		addinfile(u);
	}
}

//���ļ��ж�ȡ�������ݣ������ص�vector
vector<User> readfromFile(int &the_num) {
	the_num = 0;
	vector<User> v;
	//����ļ������� �򴴽��ļ�
	ofstream o("user.csv",ios::out|ios::app);
	o.close();
	//��ȡ�ļ�
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
			//�洢������num name pwd priv

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
	//�洢������num name pwd priv
	ofs << adduser.u_num << ",";
	ofs << adduser.u_name << ",";
	ofs << adduser.u_pwd << ",";
	ofs << adduser.priv << endl;

	ofs.close();
}

//��ȡԤԼ�ļ�
vector<Applyinfo> readapplyfile() {
	vector<Applyinfo> vapply;
	//����ļ��������򴴽��ļ�
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

//��vectorд��ԤԼ�ļ�
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
		cout << "�ļ���ʧ��" << endl;
	}
}


//д��ԤԼ�ļ�
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
		cout << "�ļ���ʧ��" << endl;
	}

	ofs.close();
}


//���ݶ��Ž�ȡ�ַ���
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