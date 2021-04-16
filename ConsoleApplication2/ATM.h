#pragma once
#include<iostream>
#include<map>
#include<set>
#include"customer.h"
#include"history.h"
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
class ATM
{
private:
    set<string> listID;
    map<string, customer> members;
    map<int, int> money;
    string ID_now;
    long long moneynow;
    history GD;
public:
    ATM();
    // cac ham sua file
    string mycontent(const string& link); //lay content
    void resetfile(const string& link,const  string& content); //
    void updatefile(const string& link, const string& content);
    void setlock(const string&  ID_);
    void openlock(const string& ID_);
    void up_menh_gia();
    void up_balance();

    void prinf_listID(); //In danh sach cac ID da luu
    void loadmember(const string& ID); // load thong tin cua 1 member
    void prinf_all(); //in thong tin cac member
    bool checkpass(const string& pass); // KIem tra mat khau
    void login(); // ham dang nhap
    void regist(); //ham dang ky
    void menu(); // hien thi menu
    // Cac ham tinh nang menu
    void xemtk();
    void lsrt();
    void AD();
    void recharge(); // Nap tien
    void withdraw(); // Rut tien
    // Cac ham giao dien
    void gd_dang_nhap1();
    void gd_dang_nhap2(const string& ID_);
    void gd_dang_ky1();
    void gd_dang_ky2();
    void gd_menu_chinh();
    void gd_guitien();
    void gd_ruttien();
    void gd_xemtk();
    void gd_lsrt();
    void gd_AD();
    // thuat toan rut tien
    void xu_ly_tien(const long long& cost);
};

