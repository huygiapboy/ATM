#include "ATM.h"
#pragma warning (disable : 4996)
ATM::ATM()
{
	ID_now = "";
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
	_sleep(1000);
}
void ATM::prinf_listID()
{
	for (auto& c : listID) cout << c << endl;
}
void ATM::login()
{
	size_t time = 1500;
	string ID_;
	string pass_;
A:
	gd_dang_nhap1();
	cin >> ID_;
	if (ID_ == "0") return;
	else
	{
		if (listID.count(ID_))
		{
			loadmember(ID_);
			if (members[ID_].getlock() == false)
			{
				cout << "This account had been blocked, please choose other account!" << endl;
				setlock(ID_);
				_sleep(time);
				system("cls");
				goto A;
			}
			if (!members[ID_].getlock())
			{
				cout << "This account was locked, plese choose new account!" << endl;
				_sleep(time);
				goto A;
				
			}
			int dem = 0;
		B:
			gd_dang_nhap2(ID_);
			cin >> pass_;
			if (pass_ == "0") return;
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
					_sleep(time);
					goto A;
				}
				else
				{
					cout << "Sai mat khau, vui long nhap lai!" << endl;
					_sleep(time);
					goto B;
				}

			}
			else
			{
				cout << "Login Sucessful!" << endl;
				ID_now = ID_;
			}
		}
		else
		{
			cout << "ID not exist! Please nhap lai!" << endl;
			_sleep(time);
			goto A;
		}
	}
}
void ATM::gd_dang_nhap1()
{
	system("cls");
	cout << "                      LOGIN                     " << endl;
	cout << "Nhap 0 de quay lai" << endl;
	cout << "Vui long nhap ID:" << endl;
}
void ATM::gd_dang_nhap2(const string& ID_)
{
	system("cls");
	cout << "                      LOGIN                     " << endl;
	cout << "Nhap 0 de thoat ve menu, 1 de tro lai dang nhap" << endl;
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
	size_t time_delay = 1500;
A:
	gd_dang_ky1();
	string ID_;
	string pass_;
	cin >> ID_;
	if (ID_ == "0") return;
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
		}

	}

}
void ATM::gd_dang_ky1()
{
	system("cls");
	cout << "               REGIST                   " << endl;
	cout << "Nhap 0 de thoat!" << endl;
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
	cout << "Nhap so tien muon rut. Luu y: So tien muon rut phai la boi so cua 10000" << endl;
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
	size_t time_delay = 1500;
	map<size_t, int> m = { {1, 500000},{2, 200000},{3, 100000},{5, 50000},{6, 20000},{7, 10000} };
A:
	gd_guitien();
	cin >> dieuhuong;
	if (dieuhuong == 4) return;
	if (dieuhuong == 8) return;
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
	_sleep(time_delay);
	goto A;
}
void ATM::xu_ly_tien(const long long& cost)
{
	map<int, size_t> m = { {500000,0},{200000,0},{100000,0},{50000,0},{20000,0},{10000,0} };

}