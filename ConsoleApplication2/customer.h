#pragma once
#include<iostream>
#include<map>
using namespace std;
class customer
{
private:
	long long balance;
	string ID;
	string pass;
	bool lock;
public:
	customer();
	customer(string ID, string pass);
	void setlock(bool lock);
	bool getlock();
	void setbalance(long long balance);
	long long getbalance();
	void setID(string ID);
	string getID();
	void setpass(string pass);
	string getpass();
};

