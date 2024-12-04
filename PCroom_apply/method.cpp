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
		strcpy_s(p.p_name, (i + 1) + "�Ż���");

		ofs << p.p_num << ",";
		ofs << p.p_name << endl;
	}
	ofs.close();
}

//��ȡcsv�ļ�
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
					cout << (*it).u_num<<"\t" << (*it).u_name<<"\t" 
						<< (*it).u_pwd << "\t" << (((*it).priv == 1) ? "��ʦ" : "ѧ��") << endl;
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
					cout << (*it).p_num << "\t" << (*it).p_name << "\t"<< endl;
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

	}
}

void adduser() {
	cout << "������Ҫ��ӵ����ͣ�1����ʦ��2��ѧ��" << endl;
	int priv;
	cin >> priv;
	int the_num;
	readfromFile(the_num);

	if (priv != 1 && priv != 2) {
		cout << "�����ָ���벻����<<";
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
		strcpy_s(u.u_pwd, inputname.c_str());

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
	//�洢������num name pwd priv
	ofs << adduser.u_num << ",";
	ofs << adduser.u_name << ",";
	ofs << adduser.u_pwd << ",";
	ofs << adduser.priv << endl;

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