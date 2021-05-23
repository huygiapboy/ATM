#include "Object.h"
Object::Object(){}
void Object::setobj(string file_name, bool mode) {
	ifstream file(file_name.c_str());
	string line;
	while (getline(file, line)) obj.push_back(line);
	file.close();
	if(mode) reverse(obj.begin(), obj.end());
}
Object::Object(string file_name, bool mode)
{
	setobj(file_name, mode);
}
void Object::show_ready(SHORT x, SHORT y, SHORT n, unsigned long time_delay, SHORT keep_last)
{
	for (int i = 1; i <= obj.size(); i++)
	{
		for (SHORT j = 0; j < i; j++)
		{
			GoTo(x, y - j + 1);
			cout << obj[obj.size() + j - i];
		}
		Sleep(time_delay);
		if (i <= obj.size() - keep_last)
		{
			for (SHORT j = 0; j < i; j++)
			{
				GoTo(x, y - j + 1);
				for (auto& c : obj[obj.size() + j - i]) cout << " ";
			}
		}
	}
}
void Object::show_showing(SHORT x, SHORT y, SHORT n, unsigned long time_delay, SHORT keep_last)
{
	for (SHORT i = 0; i < n; i++)
	{
		for (SHORT j = 0; j < obj.size(); j++)
		{
			GoTo(x, y - i - j);
			cout << obj[j];
		}
		Sleep(time_delay);
		if (i < n - keep_last)
		{
			for (SHORT j = 0; j < obj.size(); j++)
			{
				GoTo(x, y - i - j);
				for (auto& c : obj[j]) cout << " ";
			}
		}
	}
}
void Object::show_disappear(SHORT x, SHORT y, SHORT n, unsigned long time_delay, SHORT keep_last)
{
	SHORT n_ = y-n;
	for (int i = obj.size()-2; i >=keep_last; i--)
	{
		n_--;
		for (SHORT j = 0; j < i; j++)
		{
			GoTo(x, n_-j);
			cout << obj[j];
		}
		Sleep(time_delay);
		if (i > keep_last)
		{
			for (SHORT j = 0; j < i; j++)
			{
				GoTo(x, n_ - j);
				for (auto& c : obj[j]) cout << " ";
			}
		}
	}
}
void Object::show(SHORT x, SHORT y, SHORT n, unsigned long time_delay)
{
	for (SHORT i = 0; i <= 10; i++)
	{
		show_ready(i*9, y, n, time_delay, 0);
		show_showing(i*9, y, n, time_delay, 0);
		show_disappear(i*9, y, n, time_delay, 0);
	}
}
SHORT Object::size()
{
	return obj.size();
}
//void Object::show(SHORT x, SHORT y, SHORT n, unsigned long time_delay, bool appear, bool showing, bool disappear)
//{
//	if (appear) show_ready(x, y, n, time_delay);
//	if (showing) show_showing(x, y, n, time_delay);
//	if (disappear)
//	{
//		system("cls");
//		show_disappear(x, y, n, time_delay);
//	}
//	//if (disappear)
//	//{
//	//	 system("cls");
//	//	 show_disappear(x, y, n, time_delay);
//	//	 /*show_disappear2(x, y, n, time_delay);
//	//	 show_disappear(x, y, n, time_delay);*/
//	//}
//}
//void Object::show(string file_name, SHORT x, SHORT y, SHORT n, unsigned long time_delay)
//{
//	setobj(file_name, 0);
//	show(x, y, n, time_delay);
//}
//void Object::show_disappear2(SHORT x, SHORT y, SHORT n, unsigned long time_delay)
//{
//	for (int i = 1; i <= obj.size(); i++)
//	{
//		for (SHORT j = i - 1; j >= 0; j--)
//		{
//			GoTo(x, y - j + 1 - n);
//			cout << obj[obj.size() + j - i];
//		}
//		Sleep(time_delay);
//		for (SHORT j = i - 1; j >= 0; j--)
//		{
//			GoTo(x, y - j + 1 - n);
//			for (auto& c : obj[obj.size() + j - i]) cout << " ";
//		}
//	}
//}