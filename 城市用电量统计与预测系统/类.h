#pragma once
#include <iostream>
#include "region.h"
#include "�й�.cpp"
#include "����.cpp"
#include "����˹.cpp"
#include <fstream>
#define  FILENAME "������Ϣ.txt"

using namespace std;
class StatisticalManage
{
	//��¼�ļ���ͳ�����ݵ�����
	int m_EmpNum;
	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ʡ�������ָ��
	Region** m_EmpArray;

public:
	//���캯��
	StatisticalManage();

	void Show_Menu();
	void exitSystem();
	void Add_Emp();
	void save();
	//ͳ������
	int get_Num();
	//��ʼ������
	void init_Emp();
	//��ʾ����
	void show_Emp();
	//ɾ������
	void del_Emp();
	int isExist(string date, int regionId);
	//�޸�����
	void mod_Emp();
	//��������
	void find_Emp();
	//����ļ�����
	void clean_Emp();
	//Ԥ������
	void predict_Emp();
	//ͳ��
	void count_Emp();
	//��������
	~StatisticalManage();
};


#pragma once

