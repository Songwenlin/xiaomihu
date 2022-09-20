#pragma once
#include <iostream>
#include <string>
using namespace std;

//国家抽象类
class Region
{
public:
	//纯虚函数，需要重写虚函数
	//显示信息
	virtual void showInfo() = 0;
	//不加等于0将报错，原因是，不加等于0为虚函数，需要在类里面实现
	//加入纯虚函数，因为父类的虚函数都是无意义的，主要都是调用子类重写的内容
	//获取地区名称
	virtual string getRegionName() = 0;

	//国家编号
	int regionId;

	//城市
	string city;

	//日期
	string date;

	//第一产业电量
	float first;

	//第二产业电量
	float second;

	//第三产业电量
	float third;

	//居民用电量
	float people;
};

