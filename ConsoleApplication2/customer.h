#pragma once
#include<iostream>
using namespace std;
class customer
{
private:
	long long balance;
	string ID;
	string pass;
	bool lock;
	size_t dem;
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
	void setdem(size_t dem);
	size_t getdem();
};

