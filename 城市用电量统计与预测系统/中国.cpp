#pragma once
#include <iostream>
using namespace std;
#include "region.h"

//中国类
//公有继承，将继承父类的所有属性，不可访问私有属性，
//父类的保护属性在子类爱是保护属性
class China :public Region
{
public:
	//构造函数
	China(string city2, string date2, float a, float b, float c, float d, int regionId2)
	{
		this->city = city2;
		this->date = date2;
		this->first = a;
		this->second = b;
		this->third = c;
		this->people = d;
		this->regionId = regionId2;
	}
	virtual void showInfo()//virtual 关键字可以省略，是重写父类的函数
	{
		//cout << "_______________________________________________________________________________________________________________" << endl;
		cout << "|" << this->getRegionName()
			<< "\t|" << this->city
			<< "\t|" << this->date
			<< "\t|第一产业:" << this->first
			<< "\t|第二产业:" << this->second
			<< "\t|第三产业:" << this->third
			<< "\t|居民：" << this->people << "|" << endl;
	}
	virtual string getRegionName()
	{
		return string("中国");
	}
};

