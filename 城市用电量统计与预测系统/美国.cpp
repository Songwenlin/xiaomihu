#pragma once
#include <iostream>
using namespace std;
#include "region.h"

//������
//���м̳У����̳и�����������ԣ����ɷ���˽�����ԣ�
//����ı������������మ�Ǳ�������
class USA :public Region
{
public:
	//���캯��
	USA(string city2, string date2, float a, float b, float c, float d, int regionId2)
	{
		this->city = city2;
		this->date = date2;
		this->first = a;
		this->second = b;
		this->third = c;
		this->people = d;
		this->regionId = regionId2;

	}
	virtual void showInfo()//virtual �ؼ��ֿ���ʡ�ԣ�����д����ĺ���
	{
		cout << "|���ң�" << this->getRegionName()
			<< "\t|���У�" << this->city
			<< "\t|���ڣ�" << this->date
			<< "\t|��һ��ҵ������" << this->first
			<< "\t|�ڶ���ҵ������" << this->second
			<< "\t|������ҵ������" << this->third
			<< "\t|�����õ�����" << this->people << endl;
	}
	virtual string getRegionName()
	{
		return string("����");
	}
};