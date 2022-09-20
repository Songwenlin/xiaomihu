#pragma once
#include <iostream>
#include "region.h"
#include "中国.cpp"
#include "美国.cpp"
#include "俄罗斯.cpp"
#include <fstream>
#define  FILENAME "电量信息.txt"

using namespace std;
class StatisticalManage
{
	//记录文件中统计数据的条数
	int m_EmpNum;
	//标志文件是否为空
	bool m_FileIsEmpty;

	//省份数组的指针
	Region** m_EmpArray;

public:
	//构造函数
	StatisticalManage();

	void Show_Menu();
	void exitSystem();
	void Add_Emp();
	void save();
	//统计数量
	int get_Num();
	//初始化数组
	void init_Emp();
	//显示数据
	void show_Emp();
	//删除数据
	void del_Emp();
	int isExist(string date, int regionId);
	//修改数据
	void mod_Emp();
	//查找数据
	void find_Emp();
	//清空文件数据
	void clean_Emp();
	//预测数据
	void predict_Emp();
	//统计
	void count_Emp();
	//析构函数
	~StatisticalManage();
};


#pragma once

