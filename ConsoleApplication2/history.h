#pragma once
#include<iostream>
#include<vector>
#include<map>
using namespace std;
class history
{
private:
	map<string, long long> list;
	string ID;
public:
	history();
	void insert(string time, long long money);
	void display();
};

