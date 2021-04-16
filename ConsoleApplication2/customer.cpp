#include "customer.h"
customer::customer()
{
	balance = 0;
}
customer::customer(string ID, string pass)
{
	this->ID = ID;
	this->pass = pass;
	balance = 0;
}
void customer::setbalance(long long balance)
{
	this->balance = balance;
}
long long customer::getbalance()
{
	return balance;
}
void customer::setID(string ID)
{
	this->ID = ID;
}
string customer::getID()
{
	return ID;
}
void customer::setpass(string pass)
{
	this->pass = pass;
}
string customer::getpass()
{
	return pass;
}
void customer::setlock(bool lock)
{
	this->lock = lock;
}
bool customer::getlock()
{
	return lock;
}