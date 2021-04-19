#include "ATM.h"
#pragma warning (disable : 4996)
ATM::ATM()
{
	ID_now = "";
	lenh_ = 0;
	size_t time_delay = 1000;
	cout << "Waiting for really..." << endl;
	ifstream readID("CurrentID.txt");
	string IDread;
	while (readID >> IDread) listID.insert(IDread);
	readID.close();
	ifstream readmoney("Menhgia.txt");
	readmoney >> money[10000] >> money[20000] >> money[50000] >> money[100000] >> money[200000] >> money[500000];
	readmoney.close();
	moneynow = 0;
	for (auto& c : money)
		moneynow += c.first * c.second;
	system("cls");
	cout << "WELCOME TO ATM CREATED BY GIAP HUY!"<<endl;
	_sleep(time_delay);
}
void ATM::prinf_listID()
{
	for (auto& c : listID) cout << c << endl;
}
void ATM::login()
{
	string ID_;
	string pass_;
A:
	gd_dang_nhap1();
	cin >> ID_;
	if (ID_ == "0")
	{
		lenh_ = 100;
		return;
	}
	if (ID_ == "1")
	{
		lenh_ = 50;
		return;
	}
	else
	{
		if (listID.count(ID_))
		{
			loadmember(ID_);
			if (members[ID_].getlock() == false)
			{
				cout << "This account had been blocked, please choose other account!" << endl;
				setlock(ID_);
				_sleep(time_delay);
				system("cls");
				goto A;
			}
			if (!members[ID_].getlock())
			{
				cout << "This account was locked, plese choose new account!" << endl;
				_sleep(time_delay);
				goto A;
				
			}
			int dem = 0;
		B:
			gd_dang_nhap2(ID_);
			cin >> pass_;
			if (pass_ == "0") {
				lenh_ = 100;
				return;
			}
			if (pass_ == "1")
			{
				system("cls");
				goto A;
			}
			dem++;
			if (members[ID_].getpass() != pass_)
			{
				if (dem == 5)
				{
					cout << "ID now be blocked after 5 fail entering password!" << endl;
					members[ID_].setlock(false);
					_sleep(time_delay);
					goto A;
				}
				else
				{
					cout << "Sai mat khau, vui long nhap lai!" << endl;
					_sleep(time_delay);
					goto B;
				}

			}
			else
			{
				cout << "Login Sucessful!" << endl;
				ID_now = ID_;
				string content = "LOGIN: " + get_time();
				insert_history(content);
				_sleep(time_delay);
				lenh_ = 7;
			}
		}
		else
		{
			cout << "ID not exist! Please nhap lai!" << endl;
			_sleep(time_delay);
			goto A;
		}
	}
}
void ATM::gd_log_out()
{
	system("cls");
	cout << "                LOG OUT                \n";
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du:***********" << endl;
	cout << setfill(' ') << left << setw(30) << "1. Xac nhan dang xuat" << setfill(' ') << setw(30) << "2. Quay lai menu" << endl;
}
void ATM::gd_dang_nhap1()
{
	system("cls");
	cout << "                      LOGIN                     " << endl;
	cout << setfill(' ') << left << setw(30) << "0. Quay lai" << setfill(' ') << setw(30) << "1. Dang ky" << endl;
	cout << "Vui long nhap ID:" << endl;
}
void ATM::gd_dang_nhap2(const string& ID_)
{
	system("cls");
	cout << "                      LOGIN                     " << endl;
	cout << setfill(' ') << left << setw(30) << "0. Thoat" << setfill(' ') << setw(30) << "1. Quay lai" << endl;
	cout << "Hello " << ID_ << " , vui long nhap password:" << endl;
}
void ATM::loadmember(const string& ID_)
{
	if (members.empty() || !members.count(ID_))
	{
		customer newcustomer;
		string IDfile = ID_ + ".txt";
		ifstream fileID(IDfile.c_str());
		newcustomer.setID(ID_);
		string password;
		long long newbalance;
		bool lock_;
		fileID >> password >> newbalance>>lock_;
		fileID.close();
		newcustomer.setbalance(newbalance);
		newcustomer.setpass(password);
		newcustomer.setlock(lock_);
		members[ID_] = newcustomer;
	}
}
void ATM::prinf_all()
{
	for (auto& c : members)
	{
		cout << c.second.getID() << " " << c.second.getbalance() << " " << c.second.getlock() <<endl;
	}
}
string ATM::mycontent(const string& link)
{
	FILE* pfile;
	pfile = fopen(link.c_str(), "r");
	char myID[100];
	if (fgets(myID, 100, pfile) != NULL);
	string s(myID);
	fclose(pfile);
	return s;
}
void ATM::resetfile(const string& link,  const string& content)
{
	FILE* pFile;
	pFile = fopen(link.c_str(), "w");
	fputs(content.c_str(), pFile);
	fclose(pFile);
}
void ATM::setlock(const string& ID_)
{
	string link = ID_ + ".txt";
	string content = mycontent(link);
	content.pop_back(); content.push_back('0');
	resetfile(link, content);
	members[ID_].setlock(false);
}
void ATM::openlock(const string& ID_)
{
	string link = ID_ + ".txt";
	string content = mycontent(link);
	content.pop_back(); content.push_back('1');
	resetfile(link, content);
	members[ID_].setlock(true);
}
void ATM::regist()
{
A:
	gd_dang_ky1();
	string ID_;
	string pass_;
	cin >> ID_;
	if (ID_ == "0")
	{
		lenh_ = 0;
		return;
	}
	if (listID.count(ID_))
	{
		cout << "Account had been existed!" << endl;
		_sleep(time_delay);
		goto A;
	}
	else
	{
		gd_dang_ky2();
		cin >> pass_;
		if (pass_ == "0")
		{
			goto A;
		}
		else
		{
			system("cls");
			cout << "               REGIST                   " << endl;
			cout << "Account "<<ID_<<" succuessful created!"<<endl;
			ID_now = ID_;
			listID.insert(ID_);
			string link = ID_ + ".txt";
			ofstream add("CurrentID.txt");
			for (auto& c : listID) add << c<<" ";
			add.close();
			ofstream newmember(link.c_str());
			newmember << pass_ << " 0 1";
			newmember.close();
			loadmember(ID_);
			lenh_ = 7;
		}

	}

}
void ATM::gd_dang_ky1()
{
	system("cls");
	cout << "               REGIST                   " << endl;
	cout << "0. Thoat dang ky" << endl;
	cout << "Vui long nhap tai khoan:" << endl;
}
void ATM::gd_dang_ky2()
{
	system("cls");
	cout << "               REGIST                   " << endl;
	cout << "Nhap 0 de huy" << endl;
	cout << "Enter new password:" << endl;
}
void ATM::gd_menu_chinh()
{
	system("cls");
	cout << "                  MENU                " << endl;
	cout << setfill(' ') << left<<setw(30) << "Xin chao "+ID_now << setw(30) << "So du:***********" << endl;
	cout << setfill(' ') << left<<setw(30) << "1. Gui tien" << setfill(' ') << setw(30) << "4. Rut tien" << endl;
	cout << setfill(' ') << left<<setw(30) << "2. Xem tai khoan" << setfill(' ') << setw(30) << "5. Lich su rut tien" << endl;
	cout << setfill(' ') << left<<setw(30) << "3. ADMIN" << setfill(' ') << setw(30) << "6. Dang xuat" << endl;
}
void ATM::gd_guitien()
{
	system("cls");
	cout << "                 GUI TIEN               " << endl;
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du:***********" << endl;
	cout << setfill(' ') << left << setw(30) << "1. Menh gia 500000" << setfill(' ') << setw(30) << "5. Menh gia 50000" << endl;
	cout << setfill(' ') << left << setw(30) << "2. Menh gia 200000" << setfill(' ') << setw(30) << "6. Menh gia 20000" << endl;
	cout << setfill(' ') << left << setw(30) << "3. Menh gia 100000" << setfill(' ') << setw(30) << "7. Menh gia 10000" << endl;
	cout << setfill(' ') << left << setw(30) << "4. Quay lai" << setfill(' ') << setw(30) << "8. Quay so may man" << endl;
}
void ATM::gd_ruttien()
{
	system("cls");
	cout << "                 RUT TIEN               " << endl;
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du:***********" << endl;
	cout << setfill(' ') << left << setw(30) << "1. Xem tai khoan hien tai" << setfill(' ') << setw(30) << "2. Quay lai" << endl;
	cout << "Nhap so tien muon rut. Luu y: So tien muon rut phai la boi so cua 10000, toi da 3000000" << endl;
}
void ATM::gd_xemtk()
{
	system("cls");
	cout << "                 RUT TIEN               " << endl;
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du: "+to_string(members[ID_now].getbalance()) << endl;
	cout << setfill(' ') << left << setw(30) << "1. Xem lich su rut tien" << setfill(' ') << setw(30) << "2. Quay lai" << endl;

}
void ATM::gd_lsrt()
{
	system("cls");
	cout << "                 LICH SU RUT TIEN               " << endl;
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du: *********" << endl;
	cout << setfill(' ') << left << setw(30) << "1. Quay so may man" << setfill(' ') << setw(30) << "2. Quay lai menu" << endl;
}
void ATM::gd_AD()
{
	system("cls");
	cout << "                 XIN CHAO ADMIN              " << endl;
	cout << setfill(' ') << left << setw(40) << "1. Xem tat ca ID" << setfill(' ') << setw(30) << "4. Rut tien" << endl;
	cout << setfill(' ') << left << setw(40) << "2. Xem lich su rut tien theo ID" << setfill(' ') << setw(30) << "5. Lich su dang nhap va rut tien ATM" << endl;
	cout << setfill(' ') << left << setw(40) << "3. Xem thong tin ID bat ki" << setfill(' ') << setw(30) << "6. Dang xuat" << endl;
}
void ATM::up_menh_gia()
{
	ofstream file("Menhgia.txt");
	for (auto& c : money)
		file << c.second << " ";
	file.close();
}
void ATM::up_balance()
{
	string link = ID_now+".txt";
	ofstream file(link.c_str());
	file << members[ID_now].getpass() << " " << members[ID_now].getbalance() << " " << members[ID_now].getlock();
	file.close();
}
void ATM::recharge()
{
	size_t dieuhuong;
	map<size_t, int> m = { {1, 500000},{2, 200000},{3, 100000},{5, 50000},{6, 20000},{7, 10000} };
A:
	gd_guitien();
	cin >> dieuhuong;
	if (dieuhuong == 4)
	{
		lenh_ = 7;
		return;
	}
	if (dieuhuong == 8)
	{
		cout << "CHUC NANG BO SUNG SAU!\n";
		goto A;
	}
	if (!m.count(dieuhuong))
	{
		cout << "Chuc nang khong ton tai";
		_sleep(time_delay);
		goto A;
	}
	gd_guitien();
	size_t dem;
	cout << "Nhap so to: " <<m[dieuhuong]<<" muon nap:"<< endl;
	cin >> dem;
	if (dem == 4)
	{
		goto A;
	}
	money[m[dieuhuong]] += dem;
	moneynow += m[dieuhuong] * dem;
	up_menh_gia();
	members[ID_now].setbalance(members[ID_now].getbalance() + m[dieuhuong] * dem);
	up_balance();
	cout << "Da nap " << m[dieuhuong] * dem << " thanh cong!" << endl;
	string content = "NAP TIEN: TAI KHOAN CONG " + to_string(m[dieuhuong] * dem) + "    SO DU: " + to_string(members[ID_now].getbalance())+ " " + get_time();
	insert_history(content);
	_sleep(2000);
	goto A;
}
void ATM::plusx(int* arr, long long sum, map<int, int>& x, bool& exit, const long long & cost_)
{
	for (int j = 0; j < 6; j++)
	{
		if (exit) return;
		sum += arr[j];
		x[arr[j]]++;
		if (sum > cost_)
		{
			sum -= arr[j];
			x[arr[j]]--;
			continue;
		}
		if (sum < cost_)
		{
			plusx(arr, sum, x, exit, cost_);
		}
		if (sum == cost_)
		{
			for (auto& c : x)
			{
				if (c.second > money[c.first])
				{
					exit = true;
					cout << "Sorry, we can't !\n";
					return;
				}
			}
			for (auto& c : x)
			{
				money[c.first] -= c.second;
			}
			up_menh_gia();
			members[ID_now].setbalance(members[ID_now].getbalance() - cost_);
			up_balance();
			moneynow -= cost_;
			cout << "Success!\n";
			exit = true;
			return;
		}
		sum -= arr[j];
		x[arr[j]]--;
	}
}
void ATM::xu_ly_tien(const long long& cost_)
{
	int arr[6] = { 500000, 200000, 100000, 50000, 20000, 10000 };
	long long sum = 0;
	map<int, int> x = { {10000,0},{20000,0},{50000,0},{100000,0},{200000,0},{500000,0} };
	bool exit_ = false;
	plusx(arr, sum, x, exit_, cost_);
}
void ATM::withdraw()
{
	long long cost;
A:
	gd_ruttien();
	cin >> cost;
	if (cost == 1)
	{
		lenh_ = 2;
		return;
	}
	if (cost == 2)
	{
		lenh_ = 7;
		return;
	}
	if (cost % 10000 != 0|| cost>3000000)
	{
		cout << "SO TIEN KHONG HOP LE!\n";
		_sleep(time_delay);
		goto A;
	}
	if (cost > moneynow)
	{
		cout << "MAY KHONG DU SO DU DE RUT SO TIEN NAY!\n";
		goto A;
	}
	xu_ly_tien(cost);
	string content = "RUT TIEN: TAI KHOAN TRU " + to_string(cost) + "    SO DU: "+to_string(members[ID_now].getbalance())+" " + get_time();
	insert_history(content);
	_sleep(time_delay);
	goto A;
}
void ATM::menu()
{
	size_t lenh;
A:
	gd_menu_chinh();
	cin >> lenh;
	if (lenh > 6)
	{
		cout << "CHUC NANG KHONG HOP LE!\n";
		_sleep(time_delay);
		goto A;
	}
	else
	{
		lenh_ = lenh;
	}

}
void ATM::xemtk()
{
A:
	system("cls");
	cout << "               THONG TIN TAI KHOAN             \n";
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du: " +to_string(members[ID_now].getbalance()) << endl;
	cout << setfill(' ') << left << setw(30) << "0. Quay lai" << setfill(' ') << setw(30) << "1. Xem lich su" << endl;
	size_t rehuong;
	cin >> rehuong;
	switch (rehuong)
	{
	case 0:
		lenh_=7;
		return;
	case 1:
		lenh_ = 5;
		return;
	default:
		cout << "CHUC NANG KHONG HOP LE!\n";
		_sleep(time_delay);
		goto A;
	}

} 
void ATM::AD()
{
	cout << "CHUC NANG SE DUOC THEM SAU!;\n";
	_sleep(time_delay);
	lenh_ = 7;
} 
void ATM::lsrt()
{
	system("cls");
	cout << "          LICH SU GIAO DICH                \n";
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du: " +to_string(members[ID_now].getbalance()) << endl;
	cout << setfill(' ') << left << setw(30) << "0. Quay lai\n" << endl;
	prinf_history();
	cout << endl;
	int quaylai;
	cin >> quaylai;
	lenh_ = 7;
}
void ATM::log_out()
{
	size_t lenh;
A:
	gd_log_out();
	cin >> lenh;
	switch (lenh)
	{
	case 1:
		lenh_ = 0;
		ID_now = "";
		return;
	case 2:
		lenh_ = 7;
		return;
	default:
		cout << "LENH KHONG HOP LE\n";
		goto A;
	}
}
void ATM::TTDK()
{
	while (true)
	{
		switch (lenh_)
		{
		case 0:
			login();
			break;
		case 1:
			recharge();
			break;
		case 2:
			xemtk();
			break;
		case 3:
			AD();
			break;
		case 4:
			withdraw();
			break;
		case 5:
			lsrt();
			break;
		case 6:
			log_out();
			break;
		case 7: //menu
			menu();
			break;
		case 8:
			QSMM();
			break;
		case 50:
			regist();
			break;
		case 100:
			cout << " CAM ON DA SU DUNG ATM CREATED BY GIAP HUY\n";
			return;
		default:
			cout << "Chuc nang khong hop le!\n";
			lenh_ = 7;
			break;
		}
	}
}
void ATM::QSMM()
{

}
string ATM::get_time()
{
	time_t now = time(0);
	char dt[100];
	errno_t erro = ctime_s(dt, 100, &now);
	string time_t(dt);
	return time_t;
}
void ATM::prinf_history()
{
	string line;
	string link = ID_now + "history.txt";
	ifstream file(link.c_str());
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.close();
}
void ATM::insert_history(const string& content)
{
	fstream file;
	string link = ID_now + "history.txt";
	file.open(link.c_str(), ios::app);
	file << "\n" << content;
	file.close();
}
void start()
{
	ATM AD;
	AD.TTDK();
}
