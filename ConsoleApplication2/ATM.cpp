#include "ATM.h"
#pragma warning (disable : 4996)
using namespace std;
using std::cin;

ATM::ATM()
{
	cout << "Waiting for really..." << endl;
	ID_now = "";
	lenh_ = 0;
	time_delay = 1000;
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
	SHOW();
	_sleep(time_delay);
	set_language();
}
void ATM::SHOW()
{
	int random = rand(7, 1);
	string link;
	switch (random)
	{
	case 1:
		link = "DAULAU.txt";
		break;
	case 2:
		link = "GAU.txt";
		break;
	case 3:
		link = "GUN.txt";
		break;
	case 4:
		link = "HaiTraitim.txt";
		break;
	case 5:
		link = "KILAN.txt";
		break;
	case 6:
		link = "LIKE.txt";
		break;
	case 7:
		link = "TraiTim.txt";
		break;
	default:
		break;
	}
	Object obj("Wellcome.txt", 1);
	Object obj2(link, 1);
	obj.show_ready(50, 18, 10, 30, 0);
	obj.show_showing(50, 18, 10, 30, 0);
	obj.show_disappear(50, 18, 10, 30, 2);
	//Sleep(time_delay);
	obj2.show_ready(50, 2+obj2.size(), 1, 30, 0);
	obj2.show_showing(50, 2+obj2.size(), 1, 30, 1);
}
// Cac ham ktra tk mk
bool ATM::check_correctID(const string& ID_)
{
	if (ID_.size() < 5 || ID_.size() > 10)
	{
		cout << language[4]<<endl;
		_sleep(time_delay);
		return false;
	}
	return true;
}
bool ATM::check_correctpass(const string& pass_)
{
	if (pass_.size() < 6)
	{
		cout << language[6]<<endl;
		_sleep(time_delay);
		return false;
	}
	map<bool, bool> m = { {0,0},{1,0} };
	for (auto& c : pass_)
	{
		if (c >= '0' && c <= '9') m[0] = 1;
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) m[1] = 1;
		if (m[0] && m[1])
		{
			return true;
		}
	}
	cout << language[8]<<endl;
	_sleep(time_delay);
	return false;
}
bool ATM::check_correctnumber(const string& number)
{
	if (number.size() > 8||number.empty()) return false;
	for (const auto& c : number)
	{
		if (c>='0'&&c<='9') continue;
		else return false;
	}
	return true;
}

//CAC HAM SUA FILE
void ATM::setlock(const string& ID_)
{
	members[ID_].setlock(false);
	string link = ID_ + ".txt";
	ofstream file(link.c_str());
	file << members[ID_].getpass() << " " << members[ID_].getbalance() << " " << members[ID_].getdem() << " " << members[ID_].getlock();
	file.close();
}
void ATM::openlock(const string& ID_)
{
	members[ID_].setlock(true);
	string link = ID_ + ".txt";
	ofstream file(link.c_str());
	file << members[ID_].getpass() << " " << members[ID_].getbalance() << " " << "0" << " " << members[ID_].getlock();
	file.close();	
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
	string link = ID_now + ".txt";
	ofstream file(link.c_str());
	file << members[ID_now].getpass() << " " << members[ID_now].getbalance() << " " << members[ID_now].getdem()<<" "<< members[ID_now].getlock();
	file.close();
}
void ATM::update_file(const string& ID_)
{
	string link = ID_ + ".txt";
	ofstream file(link.c_str());
	file << members[ID_].getpass() << " " << members[ID_].getbalance() << " " << members[ID_].getdem() << " " << members[ID_].getlock();
	file.close();
}
void ATM::prinf_listID()
{
	system("cls");
	cout << language[10]<<endl;
	prinf_all();
	string huylovethao;
	cout << language[11]<<endl;
	fflush(stdin);
	getline(cin, huylovethao);
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
		size_t dem;
		fileID >> password >> newbalance >> dem >>lock_;
		fileID.close();
		newcustomer.setbalance(newbalance);
		newcustomer.setpass(password);
		newcustomer.setlock(lock_);
		newcustomer.setdem(dem);
		members[ID_] = newcustomer;
	}
}
void ATM::loadallmember()
{
	for (auto& c : listID)
	{
		loadmember(c);
	}
}
void ATM::prinf_all()
{
	for (auto& c : members)
	{
		cout << language[13] <<" "<< left << setw(30) << c.second.getID() << language[14]<<" " << setw(30) << c.second.getbalance();
		if (c.second.getlock())
		{
			cout << language[15]<<" "<< setw(10) << language[16] << endl;
		}
		else
		{
			cout << language[15]<<" " << setw(10) << language[17]<< endl;
		}
	}
}

// Cac ham bat dau ATM
void ATM::set_language()
{
	language.clear();
	system("cls");
	cout << "Choose Language:" << endl;
	cout << "1. Vietnamese                        5. English" << endl;
	cout << "2. German                            6. Indonesian" << endl;
	cout << "3. Danish                            7. Dutch" << endl;
	cout << "4. French                            8. Norwegian" << endl;
	string link;
	string re;
A:
	fflush(stdin);
	getline(cin, re);
	if (re == "restart")
	{
		Re_start = true;
		lenh_ = 99;
		return;
	}
	if (!check_correctnumber(re))
	{
		delete_(0, 5, 2);
		cout << "Invalid function!                                                                                                  " << endl;
		_sleep(time_delay);
		delete_(0, 5, 1);
		goto A;
	}
	switch (stoi(re))
	{
	case 1:
		link = "VIETNAMESE.txt";
		break;
	case 5:
		link = "ENGLISH.txt";
		break;
	case 2:
		link = "GERMAN.txt";
		break;
	case 6:
		link = "INDONESIA.txt";
		break;
	case 3:
		link = "DANISH.txt";
		break;
	case 7:
		link = "DUTCH.txt";
		break;
	case 4:
		link = "FRENCH.txt";
		break;
	case 8:
		link = "NORWEGIAN.txt";
		break;
	default:
		delete_(0, 5, 2);
		cout << "Invalid function!                                                                                                  " << endl;
		_sleep(time_delay);
		delete_(0, 5, 1);
		goto A;
	}
	ifstream file(link.c_str());
	string line;
	while (getline(file, line)) language.push_back(line);
}
void ATM::login()
{
	string ID_;
	string pass_;
I:
	gd_dang_nhap1();
A:
	fflush(stdin);
	getline(cin, ID_);
	if (ID_ == "restart")
	{
		Re_start = true;
		lenh_ = 99;
		return;
	}
	if (ID_ == "1")
	{
		set_language();
		lenh_ = 0;
		return;
	}
	if (ID_ == "2")
	{
		lenh_ = 50;
		return;
	}
	else
	{
		if (listID.count(ID_))
		{
			loadmember(ID_);
			ID_now = ID_;
			if (!members[ID_].getlock())
			{
				cout << language[19] << endl;
				_sleep(time_delay);
				delete_(0, 3, 3);
				goto A;
				
			}
			int dem = members[ID_].getdem();
			gd_dang_nhap2(ID_);
		B:
			fflush(stdin);
			getline(cin, pass_);
			if (pass_ == "2") {
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
					cout << language[20] << endl;
					members[ID_].setdem(dem);
					up_balance();
					members[ID_].setlock(false);
					setlock(ID_);
					_sleep(time_delay);
					delete_(0, 3, 3);
					goto I;
				}
				else
				{
					cout << language[21] << endl;
					members[ID_].setdem(dem);
					up_balance();
					_sleep(time_delay);
					delete_(0, 3, 3);
					goto B;
				}
			}
			else
			{
				cout << language[22] << endl;
				members[ID_].setdem(0);
				up_balance();
				string content = getw("LOGIN", 58) + getw(get_time(),28);
				insert_history(ID_now, content);
				string atm = "ATM";
				string content2 = getw(ID_now,10) + "  " + content;
				insert_history(atm, content2);
				_sleep(time_delay);
				lenh_ = 20;
			}
		}
		else
		{
			cout << language[23] << endl;
			_sleep(time_delay);
			delete_(0, 3, 3);
			goto A;
		}
	}
}
void ATM::regist()
{
A:
	gd_dang_ky1();
	string ID_;
	string pass_;
I:
	fflush(stdin);
	getline(cin, ID_);
	if (ID_ == "1")
	{
		lenh_ = 0;
		return;
	}
	if (!check_correctID(ID_))
	{
		delete_(0, 3, 3);
		goto I;
	}
	if (listID.count(ID_))
	{
		cout << language[25] << endl;
		_sleep(time_delay);
		delete_(0, 3, 3);
		goto I;
	}
	else
	{
		gd_dang_ky2();
		do
		{
			delete_(0, 3, 2);
			fflush(stdin);
			getline(cin, pass_);
			if (pass_ == "1")
			{
				goto A;
			}
		} while (!check_correctpass(pass_));
		delete_(0, 3, 2);
		cout << language[7];
		_sleep(time_delay);
		ID_now = ID_;
		listID.insert(ID_);
		string link = ID_ + ".txt";
		ofstream add("CurrentID.txt",ios::app);
		add << "  " << ID_;
		add.close();
		ofstream newmember(link.c_str());
		newmember << pass_ << " 0 0 1";
		newmember.close();
		loadmember(ID_);
		string content = getw("LOGIN", 58) + getw(get_time(), 28);
		insert_history(ID_now, content);
		string atm = "ATM";
		string content2 = getw(ID_now, 10) + "  " + content;
		insert_history(atm, content2);
		lenh_ = 20;
	}

}
void ATM::menu()
{
	string lenh;
	gd_menu_chinh();
A:
	fflush(stdin);
	getline(cin, lenh);
	if (!check_correctnumber(lenh))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 6, 3);
		goto A;
	}
	if (stoi(lenh) > 8||stoi(lenh)<1)
	{
		cout << language[82]<<endl;
		_sleep(time_delay);
		delete_(0, 6, 3);
		goto A;
	}
	else
	{
		lenh_ = stoi(lenh);
	}

}

// Cac ham tinh nang menu
void ATM::status_ID()
{
	string ID_;
I:
	system("cls");
	cout << language[31]<<endl;
	cout << setfill(' ') << left << setw(40) << language[32] << endl;
	cout << language[33]<<endl;
A:
	fflush(stdin);
	getline(cin, ID_);
	if (ID_ == "1")
	{
		return;
	}
	if (!listID.count(ID_))
	{
		cout << language[34]<<endl;
		_sleep(time_delay);
		delete_(0, 3, 2);
		goto A;
	}
	system("cls");
	cout << language[31]<<endl;
	cout << language[35]<<endl;
	cout << language[13]<<" " << left << setw(30) << members[ID_].getID() << language[14]<<" " << setw(30) << members[ID_].getbalance();
	if (members[ID_].getlock())
	{
		cout << language[15]<<" " << setw(10) << language[16] << endl;
	}
	else
	{
		cout << language[15] << setw(10) << language[17] << endl;
	}
	cout << language[36] << endl;
	prinf_history(ID_);
	if (members[ID_].getlock())
	{
		cout << language[13]<<" " << ID_ << language[37]<<endl;
	}
	else
	{
		cout << language[13]<<" " << ID_ << language[38]<<endl;
	}
	cout << setfill(' ') << left << setw(40) << language[39] << setfill(' ') << setw(30) << language[40] << endl;
	string re2;
	fflush(stdin);
	getline(cin, re2);
	if (!check_correctnumber(re2))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		goto I;
	}
	switch (stoi(re2))
	{
	case 2:
		if (members[ID_].getlock()) setlock(ID_);
		else openlock(ID_);
		break;
	case 1:
		break;
	default:
		cout << language[82] << endl;
		_sleep(time_delay);
		break;
	}
	goto I;
}
void ATM::log_out()
{
	string lenh;
	gd_log_out();
A:
	fflush(stdin);
	getline(cin, lenh);
	if (!check_correctnumber(lenh))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 3, 3);
		goto A;
	}
	switch (stoi(lenh))
	{
	case 1:
		cout << language[42] << endl;
		lenh_ = 0;
		ID_now = "";
		_sleep(time_delay);
		return;
	case 2:
		lenh_ = 20;
		return;
	default:
		cout << language[82]<<endl;
		_sleep(time_delay);
		delete_(0, 3, 3);
		goto A;
	}
}
void ATM::xemtk()
{
	system("cls");
	cout << language[44]<<endl;
	cout << setfill(' ') << left << setw(30) << language[45]+" " + ID_now << setw(30) << language[46]+ " " + to_string(members[ID_now].getbalance()) << endl;
	cout << setfill(' ') << left << setw(30) << language[47] << setw(30) << language[48]<<endl;
	string rehuong;
A:
	fflush(stdin);
	getline(cin, rehuong);
	if (!check_correctnumber(rehuong))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 3, 3);
		goto A;
	}
	switch (stoi(rehuong))
	{
	case 1:
		lenh_ = 20;
		return;
	case 2:
		lenh_ = 98;
		return;
	default:
		cout << language[82]<<endl;
		_sleep(time_delay);
		delete_(0, 3, 3);
		goto A;
	}

}
void ATM::lsrt(const string& ID_)
{
	system("cls");
	cout << language[50]<<endl;
	cout << setfill(' ') << left << setw(30) << language[45]+" "+ ID_ << setw(30) << language[46]+" " + to_string(members[ID_].getbalance()) << endl;
	prinf_history(ID_);
	cout << endl;
	cout << language[11]<<endl;
	string quaylai;
	fflush(stdin);
	getline(cin, quaylai);
	lenh_ = 20;
}
void ATM::AD()
{
	loadallmember();
	string re1;
A:
	gd_AD();
	fflush(stdin);
	getline(cin, re1);
	if (!check_correctnumber(re1))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 4, 3);
		goto A;
	}
	switch (stoi(re1))
	{
	case 1:
		prinf_listID();
		goto A;
	case 2:
		status_ID();
		goto A;
	case 3:
		prinf_historyofATM();
		goto A;
	case 6:
		lenh_ = 20;
		return;
	case 4:
		Status_ATM();
		goto A;
	case 5:
		View_Lucky();
		goto A;
	default:
		cout << language[82]<<endl;
		_sleep(time_delay);
		delete_(0, 4, 3);
		goto A;
	}
	if (stoi(re1) == 100)
	{
		goto A;
	}

}
void ATM::recharge()
{
	string dieuhuong;
	map<string, int> m = { {"1", 500000},{"2", 200000},{"3", 100000},{"4", 50000},{"5", 20000},{"6", 10000} };
A:
	gd_guitien();
I:
	fflush(stdin);
	getline(cin, dieuhuong);
	if (!check_correctnumber(dieuhuong))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 6, 3);
		goto I;
	}
	if (dieuhuong == "0")
	{
		lenh_ = 20;
		return;
	}
	if (!m.count(dieuhuong))
	{
		cout << language[82]<<endl;
		_sleep(time_delay);
		delete_(0, 6, 3);
		goto I;
	}
	string number;
	size_t dem;
	delete_(0, 6, 2);
	cout << language[52] << " " << 10000000 / m[dieuhuong] << language[53] << " " << m[dieuhuong] << language[54] << endl;
B:
	fflush(stdin);
	getline(cin, number);
	if (!check_correctnumber(number))
	{
		cout << language[124] << endl;
		_sleep(time_delay);
		delete_(0, 7, 3);
		goto B;
	}
	dem = stoi(number);
	if (dem == 0)
	{
		delete_(0, 6, 3);
		goto I;
	}
	if (dem > 10000000 / m[dieuhuong])
	{
		cout << language[55]<<endl;
		_sleep(time_delay);
		delete_(0, 7, 3);
		goto B;
	}
	money[m[dieuhuong]] += dem;
	moneynow += m[dieuhuong] * dem;
	up_menh_gia();
	members[ID_now].setbalance(members[ID_now].getbalance() + m[dieuhuong] * dem);
	up_balance();
	string content = getw("NAP TIEN:", 10) + getw("TAI KHOAN CONG", 15) + getw(to_string(m[dieuhuong] * dem), 10) + getw("SO DU:", 8) + getw(to_string(members[ID_now].getbalance()), 15) + getw(get_time(), 28);
	insert_history(ID_now, content);
	string atm = "ATM";
	string content2 = getw(ID_now, 10) + "  " + content;
	insert_history(atm, content2);
	delete_(0, 1, 1);
	cout << setfill(' ') << left << setw(30) << language[45] + " " + ID_now << setw(30) << language[14] + " " + to_string(members[ID_now].getbalance()) << endl;
	GoTo(0, 7);
	cout << language[56]<<" " << m[dieuhuong] * dem << language[57] << endl;
	_sleep(time_delay);
	delete_(0, 7, 3);
	goto B;
}
void ATM::withdraw()
{
	int cost;
	string number;
	gd_ruttien();
A:
	fflush(stdin);
	getline(cin, number);
	if (!check_correctnumber(number))
	{
		cout << language[59] << endl;
		_sleep(time_delay);
		delete_(0, 4, 3);
		goto A;
	}
	cost = stoi(number);
	if (cost == 2)
	{
		lenh_ = 2;
		return;
	}
	if (cost == 1)
	{
		lenh_ = 20;
		return;
	}
	if (cost % 10000 != 0 || cost > 3000000)
	{
		cout << language[59]<<endl;
		_sleep(time_delay);
		delete_(0, 4, 3);
		goto A;
	}
	if (cost > moneynow)
	{
		cout << language[60]<<endl;
		_sleep(time_delay);
		delete_(0, 4, 3);
		goto A;
	}
	if (cost > members[ID_now].getbalance())
	{
		cout << language[61]<<endl;
		_sleep(time_delay);
		delete_(0, 4, 3);
		goto A;
	}
	if (xu_ly_tien(cost))
	{
		delete_(0, 1, 1);
		cout << setfill(' ') << left << setw(30) << language[45] + " " + ID_now << setw(30) << language[14] + " " + to_string(members[ID_now].getbalance()) << endl;
		GoTo(0, 4);
		string content = getw("RUT TIEN:", 10) + getw("TAI KHOAN TRU", 15) + getw(to_string(cost), 10) + getw("SO DU:", 8) + getw(to_string(members[ID_now].getbalance()), 15) + getw(get_time(), 28);
		insert_history(ID_now, content);
		string atm = "ATM";
		string content2 = getw(ID_now, 10) + "  " + content;
		insert_history(atm, content2);
	}
	_sleep(time_delay);
	delete_(0, 4, 3);
	goto A;
}
void ATM::Update_Money()
{
	string dieuhuong;
	map<string, int> m = { {"1", 500000},{"2", 200000},{"3", 100000},{"4", 50000},{"5", 20000},{"6", 10000} };
A:
	gd_Update_Money();
I:
	fflush(stdin);
	getline(cin, dieuhuong);
	if (dieuhuong == "0") return;
	if (!m.count(dieuhuong))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 8, 3);
		goto I;
	}
	string number;
	delete_(0, 8, 3);
	cout << language[121] << m[dieuhuong] << language[122]<<endl;
B:
	fflush(stdin);
	getline(cin, number);
	if (!check_correctnumber(number))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 9, 3);
		goto B;
	}
	if (number == "0")
	{
		delete_(0, 8, 3);
		goto I;
	}
	if (check_correctnumber(number))
	{
		int n = stoi(number);
		money[m[dieuhuong]] += n;
		up_menh_gia();
		moneynow += m[dieuhuong] * n;
		delete_(0, stoi(dieuhuong), 1);
		cout << dieuhuong << ". " << left  << language[162] << setw(7) << m[dieuhuong] << setw(5) << money[m[dieuhuong]] << language[132];
		GoTo(0, 9);
		cout << language[123] << endl;
		_sleep(time_delay);
		delete_(0, 9, 3);
		goto B;
	}
	else
	{
		cout << language[124] << endl;
		_sleep(time_delay);
		delete_(0, 8, 3);
		goto B;
	}

}
void ATM::Status_ATM()
{
	string re1;
A:
	gd_Status_ATM();
	fflush(stdin);
	getline(cin, re1);
	if (!check_correctnumber(re1))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 10, 3);
		goto A;
	}
	switch (stoi(re1))
	{
	case 1:
		return;
	case 2:
		Update_Money();
		goto A;
	default:
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 10, 3);
		goto A;
	}
}
void ATM::Lucky_number()
{
	long long max;
A:
	system("cls");
	cout << language[139] << endl;
	cout << language[140] << endl;
	cout << setfill(' ') << left << setw(30) << language[141] << setfill(' ') << setw(30) << language[144] << endl;
	cout << setfill(' ') << left << setw(30) << language[142] << setfill(' ') << setw(30) << language[145] << endl;
	cout << setfill(' ') << left << setw(30) << language[143] << setfill(' ') << setw(30) << language[146] << endl;
	string mode;
I:
	fflush(stdin);
	getline(cin, mode);
	if (!check_correctnumber(mode))
	{
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 5, 3);
		goto I;
	}
	switch (stoi(mode))
	{
	case 1:
		max = 10;
		break;
	case 2:
		max = 20;
		break;
	case 3:
		max = 50;
		break;
	case 4:
		max = 100;
		break;
	case 5:
		max = 200;
		break;
	case 6:
		up_balance();
		lenh_ = 20;
		return;
	default:
		cout << language[82] << endl;
		_sleep(time_delay);
		delete_(0, 5, 3);
		goto I;
	}
B:
	long long money_ = 100000;
	long long money_max = money_ * max;
	if (members[ID_now].getbalance() < 100000)
	{
		cout << language[147] << endl;
		_sleep(time_delay);
		goto A;
	}
	system("cls");
	cout << language[148] << endl;
	cout << language[149] << max << language[150] << endl;
	cout << setfill(' ') << left << setw(30) << language[151] << endl;
	cout << language[152] << max <<endl<< language[153] << money_max << language[154] << endl;
	cout << language[155] << endl;
C:
	cout << language[156];
	string number;
	fflush(stdin);
	getline(cin, number);
	if (number == "0")
	{
		goto A;
	}
	if (!check_correctnumber(number))
	{
		cout << language[124] << endl;
		_sleep(time_delay);
		delete_(0, 6, 3);
		goto C;
	}
	if (stoi(number) > max)
	{
		cout << language[124] << endl;
		_sleep(time_delay);
		delete_(0, 6, 3);
		goto C;
	}
	int random = rand(max, 1);
	members[ID_now].setbalance(members[ID_now].getbalance() - 100000);
	string content = getw("LK NUB:", 10) + getw("TAI KHOAN TRU", 15) + getw(to_string(100000), 10) + getw("SO DU:", 8) + getw(to_string(members[ID_now].getbalance()), 15) + getw(get_time(), 28);
	insert_history(ID_now, content);
	string atm = "ATM";
	string content2 = getw(ID_now, 10) + "  " + content;
	insert_history(atm, content2);
	cout << language[157];
	string content4 = " . . . . . . ";
	stringstream ss(content4);
	while (ss >> content4)
	{
		cout << content4;
		_sleep(300);
	}
	cout << random<<endl;
	if (stoi(number) == random)
	{
		cout << language[158] << endl;
		members[ID_now].setbalance(members[ID_now].getbalance() + 100000*max);
		string content = getw("LK NUB:", 10) + getw("TAI KHOAN CONG", 15) + getw(to_string(money_max), 10) + getw("SO DU:", 8) + getw(to_string(members[ID_now].getbalance()), 15) + getw(get_time(), 28);
		insert_history(ID_now, content);
		string atm = "ATM";
		string content2 = getw(ID_now, 10) + "  " + content;
		insert_history(atm, content2);
		string link = "LUCKY";
		string content3 = getw(ID_now, 10)+ getw("MODE: "+to_string(max)+"X",12)+getw(to_string(money_max), 10) + getw(get_time(), 28);
		insert_history(link, content3);
		_sleep(time_delay+500);
		delete_(0, 6, 3);
		goto C;
	}
	else
	{
		cout << language[159] << endl;
		_sleep(time_delay+500);
		if (members[ID_now].getbalance() < 100000)
		{
			cout << language[147] << endl;
			_sleep(time_delay);
			goto A;
		}
		delete_(0, 6, 3);
		goto C;
	}


}
void ATM::View_Lucky()
{
	string link = "LUCKY";
	system("cls");
	cout << language[161] << endl;
	prinf_history(link);
	cout << endl;
	cout << language[11] << endl;
	string quaylai;
	fflush(stdin);
	getline(cin, quaylai);
}
void ATM::transfer()
{
	system("cls");
	cout << language[166]<< endl;
	cout << setfill(' ') << left << setw(30) << language[45] + " " + ID_now << setw(30) << language[14] + " " + to_string(members[ID_now].getbalance()) << endl;
	cout << language[167] << endl;
	cout << language[168] ;
	string ID_;
A:
	fflush(stdin);
	getline(cin, ID_);
	if (ID_ == "1")
	{
		lenh_ = 20;
		return;
	}
	if (!listID.count(ID_))
	{
		cout << language[169] << endl;
		_sleep(time_delay);
		delete_(0, 3, 2);
		cout << language[168];
		goto A;
	}
	if (ID_ == ID_now)
	{
		cout << language[170] << endl;
		_sleep(time_delay);
		delete_(0, 3, 2);
		cout << language[168];
		goto A;
	}
	loadmember(ID_);
	string number;
	delete_(0, 3, 3);
	cout << language[171]<<" " << ID_now <<" "<< language[172] <<" "<< ID_ << endl;
	cout << language[173] << endl;
B:
	fflush(stdin);
	getline(cin, number);
	if (number == "1")
	{
		delete_(0, 3, 4);
		cout<< language[168];
		goto A;
	}
	if (!check_correctnumber(number))
	{
		cout << language[174] << endl;
		_sleep(time_delay);
		delete_(0, 5, 3);
		goto B;
	}
	int money_ = stoi(number);
	if (ID_now != "admin" && members[ID_now].getbalance() < money_)
	{
		cout << language[175] << endl;
		_sleep(time_delay);
		delete_(0, 5, 3);
		goto B;
	}
	if (ID_now != "admin" && (money_ < 50000 || money_>50000000))
	{
		cout << language[176] << endl;
		_sleep(time_delay);
		delete_(0, 5, 3);
		goto B;
	}
	if (ID_now != "admin")
	{
		members[ID_now].setbalance(members[ID_now].getbalance() - money_);
		update_file(ID_now);
	}
	members[ID_].setbalance(members[ID_].getbalance() + money_);
	update_file(ID_);
	string content = getw("C.KHOAN:", 10) + getw("TAI KHOAN CONG", 15) + getw(number, 10) + getw("SO DU:", 8) + getw(to_string(members[ID_].getbalance()), 15) + getw(get_time(), 28) + getw("TU: ", 5) + getw(ID_now, 10);
	insert_history(ID_, content);
	string content2= getw("C.KHOAN:", 10) + getw("TAI KHOAN TRU", 15) + getw(number, 10) + getw("SO DU:", 8) + getw(to_string(members[ID_now].getbalance()), 15) + getw(get_time(), 28) + getw("TOI:", 5) + getw(ID_, 10);
	insert_history(ID_now, content2);
	string atm = "ATM";
	string content3 = getw(ID_now, 10) + "  " + getw("CHUYEN " + number, 34)+getw(" TOI  :" + ID_,24) + getw(get_time(), 28);
	insert_history(atm, content3);
	cout << language[177] << endl;
	if (ID_now != "admin")
	{
		delete_(0, 1, 1);
		cout << setfill(' ') << left << setw(30) << language[45] + " " + ID_now << setw(30) << language[14] + " " + to_string(members[ID_now].getbalance()) << endl;
	}
	_sleep(time_delay);
	delete_(0, 5, 4);
	goto B;
	
}
void ATM::Change_pass(const string& ID_)
{
	string pass;
	int dem = members[ID_].getdem();
	system("cls");
	cout << language[26] << endl;
	cout << endl;
	cout << language[68] << endl;
	cout <<  language[45] << " " << ID_ << language[74] << endl;
A:
	fflush(stdin);
	getline(cin, pass);
	if (pass == "1")
	{
		lenh_ = 2;
		return;
	}
	if (pass != members[ID_].getpass())
	{
		cout << language[21] << endl;
		dem++;
		if (dem == 5)
		{
			cout << language[20] << endl;
			setlock(ID_);
			lenh_ = 0;
			_sleep(time_delay);
			return;
		}
		members[ID_].setdem(dem);
		update_file(ID_);
		_sleep(time_delay);
		delete_(0, 4, 3);
		goto A;
	}
	delete_(0, 3, 3);
	cout << language[45] << " " << ID_ << " "<<language[81] << endl;
B:
	fflush(stdin);
	getline(cin, pass);
	if (pass == "1")
	{
		delete_(0, 3, 3);
		cout << language[45] << " " << ID_ << language[74] << endl;
		goto A;
	}
	if (!check_correctpass(pass))
	{
		delete_(0, 4, 3);
		goto B;
	}
	members[ID_].setpass(pass);
	update_file(ID_);
	delete_(0, 3, 3);
	cout << language[27] << endl;
	_sleep(time_delay);
	lenh_ = 2;
	return;
}

// Cac ham giao dien
void ATM::gd_log_out()
{
	system("cls");
	cout << language[63]<<endl;
	cout << setfill(' ') << left << setw(30) << language[45]+ " " + ID_now  << endl;
	cout << setfill(' ') << left << setw(30) << language[64] << setfill(' ') << setw(30) << language[65] << endl;
}
void ATM::gd_dang_nhap1()
{
	system("cls");
	cout << language[67] << endl;
	cout << setfill(' ') << left << setw(30) << language[68] << setfill(' ') << setw(30) << language[69] << endl;
	cout << language[70] << endl;
}
void ATM::gd_dang_nhap2(const string& ID_)
{
	system("cls");
	cout << language[67] << endl;
	cout << setfill(' ') << left << setw(30) << language[73] << setfill(' ') << setw(30) << language[72] << endl;
	cout << language[45]<<" " << ID_ << language[74] << endl;
}
void ATM::gd_dang_ky1()
{
	system("cls");
	cout << language[76] << endl;
	cout << language[77] << endl;
	cout << language[78]<< endl;
}
void ATM::gd_dang_ky2()
{
	system("cls");
	cout << language[76] << endl;
	cout << language[80] << endl;
	cout << language[81] << endl;
}
void ATM::gd_menu_chinh()
{
	system("cls");
	cout << language[84] << endl;
	cout << setfill(' ') << left << setw(30) << language[45]+ " " + ID_now << setw(30) << language[85] << endl;
	cout << setfill(' ') << left << setw(30) << language[86] << setfill(' ') << setw(30) << language[89] << endl;
	cout << setfill(' ') << left << setw(30) << language[87] << setfill(' ') << setw(30) << language[90] << endl;
	cout << setfill(' ') << left << setw(30) << language[88] << setfill(' ') << setw(30) << language[164] << endl;
	cout << setfill(' ') << left << setw(30) << language[163]     << setfill(' ') << setw(30) << language[91] << endl;
}
void ATM::gd_guitien()
{
	system("cls");
	cout << language[93] << endl;
	cout << setfill(' ') << left << setw(30) << language[45]+" " + ID_now << setw(30) << language[14]+ " " + to_string(members[ID_now].getbalance()) << endl;
	cout << setfill(' ') << left << setw(30) << language[94] << setfill(' ') << setw(30) << language[97] << endl;
	cout << setfill(' ') << left << setw(30) << language[95] << setfill(' ') << setw(30) << language[98] << endl;
	cout << setfill(' ') << left << setw(30) << language[96] << setfill(' ') << setw(30) << language[99] << endl;
	cout << setfill(' ') << left << setw(30) << language[100] << endl;
}
void ATM::gd_ruttien()
{
	system("cls");
	cout << language[102] << endl;
	cout << setfill(' ') << left << setw(30) << language[45]+ " " + ID_now << setw(30) << language[14]+ " " + to_string(members[ID_now].getbalance()) << endl;
	cout << setfill(' ') << left << setw(30) << language[104] << setfill(' ') << setw(30) << language[103] << endl;
	cout << language[105] << endl;
}
void ATM::gd_AD()
{
	system("cls");
	cout << language[107] << endl;
	cout << setfill(' ') << left << setw(40) << language[108] << setfill(' ') << setw(30) << language[110] << endl;
	cout << setfill(' ') << left << setw(40) << language[109] << setfill(' ') << setw(30) << language[126] << endl;
	cout << setfill(' ') << left << setw(40) << language[127] << setfill(' ') << setw(30) << language[111] << endl;
}
void ATM::gd_Status_ATM()
{
	system("cls");
	cout << language[129] << endl;
	cout << language[130] << moneynow << endl;
	cout << language[131] << endl;
	cout << language[94] << left << setw(5) << money[500000] << language[132] << endl;
	cout << language[95] << left << setw(5) << money[200000] << language[132] << endl;
	cout << language[96] << left << setw(5) << money[100000] << language[132] << endl;
	cout << language[97] << left << setw(5) << money[50000] <<  language[132] << endl;
	cout << language[98] << left << setw(5) << money[20000] <<  language[132] << endl;
	cout << language[99] << left << setw(5) << money[10000] <<  language[132] << endl;
	cout << setfill(' ') << left << setw(30) << language[133] << setfill(' ') << setw(30) << language[134] << endl;
	
}
void ATM::gd_Update_Money()
{
	system("cls");
	cout << language[136] << endl;
	cout << language[94] << left << setw(5) << money[500000] << language[132] << endl;
	cout << language[95] << left << setw(5) << money[200000] << language[132] << endl;
	cout << language[96] << left << setw(5) << money[100000] << language[132] << endl;
	cout << language[97] << left << setw(5) << money[50000] << language[132] << endl;
	cout << language[98] << left << setw(5) << money[20000] << language[132] << endl;
	cout << language[99] << left << setw(5) << money[10000] << language[132] << endl;
	cout << setfill(' ') << left << setw(30) << language[137] << endl;
}

// Thuat toan rut tien
bool ATM::xu_ly_tien(const int& cost_)
{
	vector<int> x = push(cost_);
	bool exit = false;
	vector<int> y;
	int sum = 0;
	TTRT(x, 0, cost_, y, sum, exit);
	if (sum != cost_)
	{
		cout << language[113] << endl;
		_sleep(time_delay);
		return false;
	}
	for (auto& c : y) money[c] --;
	up_menh_gia();
	members[ID_now].setbalance(members[ID_now].getbalance() - cost_);
	up_balance();
	moneynow -= cost_;
	cout << language[114] << endl;
	return true;
}
vector<int> ATM::push(const int& cost)
{
	int arr[] = { 500000,200000,100000,50000,20000,10000 };
	vector<int> result;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < cost / arr[i] && j < money[arr[i]]; j++) result.push_back(arr[i]);
	}
	return result;
}
void ATM::TTRT(vector<int>& x, int j, const int& cost, vector<int>& y, int& sum, bool& exit)
{
	for (int i = j; i < x.size(); i++)
	{
		if (exit) return;
		sum += x[i];
		y.push_back(x[i]);
		if (sum == cost)
		{
			exit = true;
			return;
		}
		if (sum > cost)
		{
			sum -= x[i];
			y.pop_back();
			continue;
		}
		if (sum < cost) TTRT(x, i + 1, cost, y, sum, exit);
	}
	if (!y.empty())
	{
		sum -= y.back();
		y.pop_back();
	}
}
// TRUNG TAM DIEU KHIEN
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
			if (ID_now != "admin")
			{
				cout << language[116] << endl;
				lenh_ = 20;
				_sleep(time_delay);
				break;
			}
			AD();
			break;
		case 4:
			Lucky_number();
			break;
		case 5:
			withdraw();
			break;
		case 6:
			lsrt(ID_now);
			break;
		case 7:
			transfer();
			break;
		case 8:
			log_out();
			break;
		case 20: 
			menu();
			break;
		case 50:
			regist();
			break;
		case 98:
			Change_pass(ID_now);
			break;
		case 99:
			return;
		case 100:
			system("cls");
			cout << language[117]<<endl;
			_sleep(time_delay);
			return;
		default:
			cout << language[82]<<endl;
			lenh_ = 20;
			break;
		}
	}
}


// Cac ham lich su
string ATM::get_time()
{
	time_t now = time(0);
	char dt[100];
	errno_t erro = ctime_s(dt, 100, &now);
	string time_now(dt);
	time_now.pop_back();
	return time_now;
}
string ATM::getw(string content, size_t n)
{
	string fill(n, ' ');
	auto it = fill.begin();
	for (auto& c : content)
	{
		if (it == fill.end())
		{
			break;
		}
		*it = c;
		it++;
	}
	return fill;
}
void ATM::prinf_history(const string& ID_)
{
	string line;
	string link = ID_ + "history.txt";
	ifstream file(link.c_str());
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.close();
}
void ATM::prinf_historyofATM()
{
	system("cls");
	cout << language[119]<<endl;
	string atm = "ATM";
	prinf_history(atm);
	cout << language[11]<<endl;
	string atm_by_giaphuy;
	fflush(stdin);
	getline(cin, atm_by_giaphuy);
}
void ATM::insert_history(const string& ID_, const string& content)
{
	fstream file;
	string link = ID_ + "history.txt";
	file.open(link.c_str(), ios::app);
	file << "\n" << content;
	file.close();
}
int rand(int max, int min)
{
	srand(time(NULL));
	int random= rand() % (max - min + 1) + min;
	for (int i = 0; i < 10; i++)
	{
		srand(random+time(NULL));
		random= rand() % (max - min + 1) + min;
	}
	return random;
}
// BAT DAU ATM
void start()
{
	
	SETCONSOLE();
A:
	ATM AD;
	AD.TTDK();
	if (AD.Re_start) goto A;
}
void test()
{
	SETCONSOLE();
	ATM AD;
	AD.loadallmember();
	AD.ID_now="huygiapboy";
	AD.transfer();
}