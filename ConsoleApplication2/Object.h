#pragma once
#include"SetConsole.h"
#include<vector>
#include<fstream>
#include<string>
#include<winnt.h>
#include<algorithm>
using namespace std;
class Object
{
private:
	vector<string> obj;
public:
	Object();
	Object(string file_name, bool reverse);
	void setobj(string file_name, bool mode);
	void show_ready(SHORT x, SHORT y, SHORT n, unsigned long time_delay, SHORT keep_last);
	void show_disappear(SHORT x, SHORT y, SHORT n, unsigned long time_delay, SHORT keep_last);
	void show_showing(SHORT x, SHORT y, SHORT n, unsigned long time_delay, SHORT keep_last);
	/*void show(SHORT x, SHORT y, SHORT n, unsigned long time_delay, bool appear, bool showing, bool disappear);*/
    /*void show_disappear2(SHORT x, SHORT y, SHORT n, unsigned long time_delay);*/
	void show(SHORT x, SHORT y, SHORT n, unsigned long time_delay);
	SHORT size();
};

