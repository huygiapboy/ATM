#pragma once
#include<iostream>
#include<map>
#include<set>
#include"customer.h"
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<ctime>
using namespace std;
class ATM
{
private:
    size_t time_delay;
    set<string> listID;
    map<string, customer> members;
    map<int, int> money;
    string ID_now;
    long long moneynow;
    size_t lenh_;
public:
    ATM();
    // cac ham sua file
    string mycontent(const string& link); //lay content
    void resetfile(const string& link,const  string& content); //
    void updatefile(const string& link, const string& content);
    void setlock(const string&  ID_); //khoa tai kgoan
    void openlock(const string& ID_); //mo khoa tai khoan
    void up_menh_gia();// cap nhap so to tien trong may
    void up_balance();// cap nhat so tien member
    void prinf_listID(); //In danh sach cac ID da luu
    void loadmember(const string& ID); // load thong tin cua 1 member
    void prinf_all(); //in thong tin cac member
    bool checkpass(const string& pass); // KIem tra mat khau
    // 
    void login(); // ham dang nhap
    void regist(); //ham dang ky
    void menu(); // hien thi menu
    // Cac ham tinh nang menu
    void log_out();
    void xemtk();
    void lsrt();
    void AD();
    void recharge(); // Nap tien
    void withdraw(); // Rut tien
    void QSMM();
   /* void menu();*/
    // Cac ham giao dien
    void gd_log_out();
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
    void plusx(int* arr, long long sum, map<int, int>& x, bool& exit, const long long& cost_);
    // TRUNG TAM DIEU KHIEN
    void TTDK();
    // cac lich su
    string get_time();
    void prinf_history();
    void insert_history();
    void insert_history(const string& content);
};
void start();

