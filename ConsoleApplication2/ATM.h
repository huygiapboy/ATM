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
#include<stdio.h>
#include<cstdlib>
#include<sstream>
#include"SetConsole.h"
#include"resource.h"
#include"Object.h"
using namespace std;
class ATM
{
private:
    unsigned long time_delay;
    set<string> listID;
    map<string, customer> members;
    map<int, size_t> money;
    vector<string> language;
    string ID_now;
    long long moneynow;
    size_t lenh_;
   
public:
    bool Re_start = false;
    ATM();
    void SHOW();

    // cac ham ktra tk va mat khau
    bool check_correctID(const string& ID_); //Ktra ID hop le khi dang ky
    bool check_correctpass(const string& pass_); // Ktra pass hop le khi dang ky
    bool check_correctnumber(const string& number); //ktra so hop le

    // Cac  ham sua file
    void setlock(const string&  ID_); //khoa tai kgoan
    void openlock(const string& ID_); //mo khoa tai khoan
    void up_menh_gia();// cap nhap so to tien trong may
    void up_balance();// cap nhat so tien member
    void update_file(const string& ID_);// cap nhat trang thai file cua member
    void prinf_listID(); //In danh sach cac ID da luu
    void loadmember(const string& ID); // load thong tin cua 1 member
    void loadallmember(); // load thong tin tat ca members
    void prinf_all(); //in thong tin cac member
    
    // Cac ham bat dau ATM
    void set_language();
    void login(); // ham dang nhap
    void regist(); //ham dang ky
    void menu(); // hien thi menu

    // Cac ham tinh nang menu
    void status_ID(); //xem trang thai tai khoan theo ID (ADMIN)
    void log_out(); // dang xuat
    void xemtk(); // xem tai khoan
    void lsrt(const string& ID_); // lich su rut tien
    void AD(); // ADMIN
    void recharge(); // Nap tien
    void withdraw(); // Rut tien
    void Status_ATM();
    void Update_Money();
    void Lucky_number();
    void View_Lucky();
    void transfer();
    void Change_pass(const string& ID_);

    // Cac ham giao dien
    void gd_log_out();
    void gd_dang_nhap1();
    void gd_dang_nhap2(const string& ID_);
    void gd_dang_ky1();
    void gd_dang_ky2();
    void gd_menu_chinh();
    void gd_guitien();
    void gd_ruttien();
    void gd_AD();
    void gd_Status_ATM();
    void gd_Update_Money();

    // thuat toan rut tien
    bool xu_ly_tien(const int& cost);
    vector<int> push(const int& cost);
    void TTRT(vector<int>& x, int j, const int& cost, vector<int>& y, int& sum, bool& exit);



    // TRUNG TAM DIEU KHIEN
    void TTDK();

    // cac ham lich su
    string get_time(); // Lay thoi gian hien tai
    string getw(string content, size_t n); //xet be rong lich su
    void prinf_history(const string& ID_); //In lich su
    void prinf_historyofATM(); // In lich su cua ATM
    void insert_history(const string& ID_, const string& content);
    friend void test();
};
int rand(int max, int min);
void start();
void test();

