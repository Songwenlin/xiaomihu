#pragma once
#include <iostream>
#include <string>
using namespace std;

//���ҳ�����
class Region
{
public:
	//���麯������Ҫ��д�麯��
	//��ʾ��Ϣ
	virtual void showInfo() = 0;
	//���ӵ���0������ԭ���ǣ����ӵ���0Ϊ�麯������Ҫ��������ʵ��
	//���봿�麯������Ϊ������麯������������ģ���Ҫ���ǵ���������д������
	//��ȡ��������
	virtual string getRegionName() = 0;

	//���ұ��
	int regionId;

	//����
	string city;

	//����
	string date;

	//��һ��ҵ����
	float first;

	//�ڶ���ҵ����
	float second;

	//������ҵ����
	float third;

	//�����õ���
	float people;
};

