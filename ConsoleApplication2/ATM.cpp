#include "ATM.h"
#pragma warning (disable : 4996)
using namespace std;
bool ATM::check_correctID(const string& ID_)
{
	if (ID_.size() < 5 || ID_.size() > 10)
	{
		cout << "ID phai dai tu 5 den 10 ky tu!\n" ;
		_sleep(time_delay);
		return false;
	}
	return true;
}
bool ATM::check_correctpass(const string& pass_)
{
	if (pass_.size() < 6)
	{
		cout << "Password phai dai tu 6 ki tu\n" ;
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
			cout << "Tao mat khau hoan tat, chao mung khach hang den voi ATM created by Giap Huy!\n";
			_sleep(time_delay);
			return true;
		}
	}
	cout << "Mat khau phai bao gom ca chu va so!\n";
	_sleep(time_delay);
	return false;
}
ATM::ATM()
{
	ID_now = "";
	lenh_ = 0;
	time_delay = 1000;
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
	system("cls");
	cout << "      DANH SACH CAC ID DA DANG KY      \n";
	cout << "Go bat ki de quay lai\n" ;
	prinf_all();
	string huylovethao;
	cin >> huylovethao;
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
					setlock(ID_);
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
				string content = getw("LOGIN", 58) + getw(get_time(),28);
				insert_history(ID_now, content);
				string atm = "ATM";
				string content2 = getw(ID_now,10) + "  " + content;
				insert_history(atm, content2);
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
		cout <<"ID: "<< left << setw(30) << c.second.getID() <<"SO DU: "<< setw(30) << c.second.getbalance();
		if (c.second.getlock())
		{
			cout <<"STATUS: "<< setw(10) << "Active" << endl;
		}
		else
		{
			cout << "STATUS: "<< setw(10) << "Locked" << endl;
		}
	}
}
string ATM::mycontent(const string& link)
{
	fstream pfile;
	pfile.open(link.c_str(), ios::in);
	string s;
	getline(pfile, s);
	pfile.close();
	return s;
}
void ATM::resetfile(const string& link,  const string& content)
{
	ofstream file(link.c_str());
	file << content;
	file.close();
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
	if (!check_correctID(ID_))
	{
		goto A;
	}
	if (listID.count(ID_))
	{
		cout << "Account had been existed!" << endl;
		_sleep(time_delay);
		goto A;
	}
	else
	{
		do
		{
			gd_dang_ky2();
			cin >> pass_;
			if (pass_ == "0")
			{
				goto A;
			}
		} while (!check_correctpass(pass_));
		system("cls");
		cout << "               REGIST                   " << endl;
		cout << "Account " << ID_ << " succuessful created!" << endl;
		ID_now = ID_;
		listID.insert(ID_);
		string link = ID_ + ".txt";
		ofstream add("CurrentID.txt");
		for (auto& c : listID) add << c << " ";
		add.close();
		ofstream newmember(link.c_str());
		newmember << pass_ << " 0 1";
		newmember.close();
		loadmember(ID_);
		string content = getw("LOGIN", 58) + getw(get_time(), 28);
		insert_history(ID_now, content);
		string atm = "ATM";
		string content2 = getw(ID_now, 10) + "  " + content;
		insert_history(atm, content2);
		lenh_ = 7;
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
	cout << setfill(' ') << left << setw(30) << "1. Xem lich su rut tien" << setfill(' ') << setw(30) << "2. Quay lai menu" << endl;

}
void ATM::gd_lsrt()
{
	system("cls");
	cout << "                 LICH SU                " << endl;
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_now << setw(30) << "So du: *********" << endl;
	cout << setfill(' ') << left << setw(30) << "1. Quay so may man" << setfill(' ') << setw(30) << "2. Quay lai menu" << endl;
}
void ATM::prinf_historyofATM()
{
	system("cls");
	cout << "         LICH SU GIAO DICH CUA ATM     \n";
	cout << "Go bat ki de Quay lai\n";
	string atm = "ATM";
	prinf_history(atm);
	string atm_by_giaphuy;
	cin >> atm_by_giaphuy;
}
void ATM::status_ID()
{
	string ID_;
A:
	system("cls");
	cout << "                XEM TRANG THAI  ID               \n";
	cout << setfill(' ') << left << setw(40) << "1. Quay lai\n";
	cout << " Nhap ID muon xem\n";
	cin >> ID_;
	if (ID_ == "1")
	{
		return;
	}
	if (!listID.count(ID_))
	{
		cout << " ID not exist!\n";
		_sleep(time_delay);
		goto A;
	}
	system("cls");
	cout << "                XEM TRANG THAI  ID               \n";
	cout << "1. Thong tin tai khoan\n";
	cout << "ID: " << left << setw(30) << members[ID_].getID() << "SO DU: " << setw(30) << members[ID_].getbalance();
	if (members[ID_].getlock())
	{
		cout << "STATUS: " << setw(10) << "Active" << endl;
	}
	else
	{
		cout << "STATUS: " << setw(10) << "Locked" << endl;
	}
	cout << "2. Lich su giao dich\n";
	prinf_history(ID_);
	if (members[ID_].getlock())
	{
		cout << "Tai khoan " << ID_ << " dang o trang thai Active, Block ID nay?\n";
	}
	else
	{
		cout << "Tai khoan " << ID_ << " dang o trang thai Locked, Active ID nay?\n";
	}
	cout << setfill(' ') << left << setw(40) << "1. Co va quay lai" << setfill(' ') << setw(30) << "2. Khong va quay lai" << endl;
	size_t re2;
	cin >> re2;
	if (re2 == 1)
	{
		if (members[ID_].getlock()) setlock(ID_);
		else openlock(ID_);
	}
	goto A;
}
void ATM::gd_AD()
{
	system("cls");
	cout << "                 XIN CHAO ADMIN              " << endl; 
	cout << setfill(' ') << left << setw(40) << "1. Danh sach tat ca ID" << setfill(' ') << setw(30) << "3. Lich su dang nhap va rut tien ATM" << endl;
	cout << setfill(' ') << left << setw(40) << "2. Xem tat ca trang thai cua ID" << setfill(' ') << setw(30) << "4. Quay lai " << endl;
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
		lenh_=8;
		return;
	}
	if (!m.count(dieuhuong))
	{
		cout << "Chuc nang khong ton tai";
		_sleep(time_delay);
		goto A;
	}
B:
	gd_guitien();
	size_t dem;
	cout << "Ban duoc nhap toi da: "<<10000000/m[dieuhuong]<<" to . Nhap so to: " <<m[dieuhuong]<<" muon nap:\n";
	cin >> dem;
	if (dem == 4)
	{
		goto A;
	}
	if (dem > 10000000 / m[dieuhuong])
	{
		cout << "Qua so to quy dinh, vui long doc ki\n";
		_sleep(time_delay);
		goto B;
	}
	money[m[dieuhuong]] += dem;
	moneynow += m[dieuhuong] * dem;
	up_menh_gia();
	members[ID_now].setbalance(members[ID_now].getbalance() + m[dieuhuong] * dem);
	up_balance();
	cout << "Da nap " << m[dieuhuong] * dem << " thanh cong!" << endl;
	string content = getw("NAP TIEN:",10) + getw("TAI KHOAN CONG",15) + getw(to_string(m[dieuhuong] * dem),10) +getw("SO DU:",8) + getw(to_string(members[ID_now].getbalance()),15) + getw(get_time(), 28);
	insert_history(ID_now, content);
	string atm = "ATM";
	string content2 = getw(ID_now,10) + "  " + content;
	insert_history(atm, content2);
	_sleep(time_delay);
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
		_sleep(time_delay);
		goto A;
	}
	if (cost > members[ID_now].getbalance())
	{
		cout << "TAI KHOAN KHONG DU SO DU!\n";
		_sleep(time_delay);
		goto A;
	}
	xu_ly_tien(cost);
	string content = getw("RUT TIEN:", 10)  + getw("TAI KHOAN TRU", 15) + getw(to_string(cost), 10) + getw("SO DU:", 8) + getw(to_string(members[ID_now].getbalance()), 15) + getw(get_time(), 28);
	insert_history(ID_now, content);
	string atm = "ATM";
	string content2 = getw(ID_now, 10) + "  " + content;
	insert_history(atm, content2);
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
	cout << setfill(' ') << left << setw(30) << "0. Quay lai menu" << setfill(' ') << setw(30) << "1. Xem lich su" << endl;
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
	loadallmember();
	size_t re1;
A:
	gd_AD();
	cin >> re1;
	switch (re1)
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
	case 4:
		lenh_ = 7;
		return;
	default:
		cout << "CHUC NANG KHONG HOP LE!\n";
		_sleep(time_delay);
		goto A;
	}
	if (re1 == 100)
	{
		goto A;
	}

} 
void ATM::lsrt(const string& ID_)
{
	system("cls");
	cout << "          LICH SU                 \n";
	cout << setfill(' ') << left << setw(30) << "Xin chao " + ID_ << setw(30) << "So du: " +to_string(members[ID_].getbalance()) << endl;
	cout << setfill(' ') << left << setw(30) << "0. Quay lai\n" << endl;
	prinf_history(ID_);
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
		cout << "DANG XUAT THANH CONG!\n";
		lenh_ = 0;
		ID_now = "";
		_sleep(time_delay);
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
			if (ID_now != "admin")
			{
				cout << "Ban khong phai la admin!"<<endl;
				lenh_ = 7;
				_sleep(time_delay);
				break;
			}
			AD();
			break;
		case 4:
			withdraw();
			break;
		case 5:
			lsrt(ID_now);
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
			system("cls");
			cout << " CAM ON DA SU DUNG ATM CREATED BY GIAP HUY\n";
			_sleep(time_delay);
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
	string time_now(dt);
	return time_now;
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
void ATM::insert_history(const string& ID_, const string& content)
{
	fstream file;
	string link = ID_ + "history.txt";
	file.open(link.c_str(), ios::app);
	file << "\n" << content;
	file.close();
}
void ATM::loadallmember()
{
	for (auto& c : listID)
	{
		loadmember(c);
	}
}
void ATM::prinf_history(const string& ID_, size_t length)
{
	string link = ID_ + "history.txt";
	FILE* pfile = fopen(link.c_str(), "r");
	fseek(pfile, 0, SEEK_END);
	char line[99];
	char line2[99];
		fseek(pfile, length, SEEK_CUR);
		fgets(line, 99, pfile);
		cout << line << endl;
		fseek(pfile, length-199, SEEK_CUR);
		fgets(line2, 99, pfile);
		cout << line2 << endl;
	
}
void start()
{
	ATM AD;
	AD.TTDK();
}
void test()
{
	ATM AD;
	string atm = "ATM";
	AD.prinf_history(atm, -99);
}
