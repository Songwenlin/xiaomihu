#include "��.h"
#include <stdlib.h>
void StatisticalManage::Show_Menu()
{
	cout << "****************************************" << endl;
	cout << "*******  ��ӭʹ�õ���ͳ��ϵͳ�� ********" << endl;
	cout << "*************  0.�˳�����  *************" << endl;
	cout << "*************  1.�����Ϣ  *************" << endl;
	cout << "*************  2.��ʾ��Ϣ  *************" << endl;
	cout << "*************  3.ɾ����Ϣ  *************" << endl;
	cout << "*************  4.�޸���Ϣ  *************" << endl;
	cout << "*************  5.������Ϣ  *************" << endl;
	cout << "*************  6.����ĵ�  *************" << endl;
	cout << "*************  7.ͳ�Ƶ���  *************" << endl;
	cout << "*************  8.Ԥ�����  *************" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
void StatisticalManage::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(1);
}

StatisticalManage::StatisticalManage()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//�ļ����������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0; //��ʼ������
		this->m_EmpArray = NULL; //��ʼ������
		this->m_FileIsEmpty = true; //��ʼ���ļ�Ϊ�ձ�־
		ifs.close();//�ر��ļ�
		return;
	}
	//�ļ����ڣ����Ҽ�¼Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0; //��ʼ������
		this->m_EmpArray = NULL; //��ʼ������
		this->m_FileIsEmpty = true; //��ʼ���ļ�Ϊ�ձ�־
		ifs.close();//�ر��ļ�
		return;
	}
	int num = this->get_Num();
	//cout << "���ݸ���Ϊ��" << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Region * [this->m_EmpNum];
	init_Emp(); //��ʼ��ͳ������
}

//��������
StatisticalManage::~StatisticalManage()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		m_EmpArray = NULL;
	}
}

//�����Ϣ
void StatisticalManage::Add_Emp()
{
	cout << "����������ͳ�Ƶ�������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Region** newspace = new Region * [newSize];

		//��ԭ�ռ������ݴ�ŵ��¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}
		//����������
		for (int i = 0; i < addNum; i++)
		{
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
			//���ұ��
			int dSelect;

			cout << "��ѡ����ң����������ǰ�����ţ�" << endl;
			cout << "1,�й�" << endl;
			cout << "2,����˹" << endl;
			cout << "3,����" << endl;
			cin >> dSelect;

			cout << "�������" << i + 1 << "�����ݵĳ���" << endl;
			cin >> city;
			cout << "�������" << i + 1 << "�����ݵ�����" << endl;
			cin >> date;
			cout << "�������" << i + 1 << "�����ݵĵ�һ��ҵ�õ���" << endl;
			cin >> first;
			cout << "�������" << i + 1 << "�����ݵĵڶ���ҵ�õ���" << endl;
			cin >> second;
			cout << "�������" << i + 1 << "�����ݵĵ�����ҵ�õ���" << endl;
			cin >> third;
			cout << "�������" << i + 1 << "�����ݵľ����õ���" << endl;
			cin >> people;


			Region* region = NULL;
			switch (dSelect)
			{
			case 1:  //����
				region = new China(city, date, first, second, third, people, 1);
				break;
			case 2: //�㶫
				region = new Russia(city, date, first, second, third, people, 2);
				break;
			case 3: //�㽭
				region = new USA(city, date, first, second, third, people, 3);
				break;
			default:
				break;
			}


			newspace[this->m_EmpNum + i] = region;

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�����¿ռ�ָ��
		this->m_EmpArray = newspace;
		//�����µ���������
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;

		//��ʾ��Ϣ
		cout << "��ӳɹ�" << addNum << "������" << endl;
		this->save();
	}
	else
	{
		cout << "��������" << endl;

	}
	system("pause");
	system("cls");
}

//�����ļ�
void StatisticalManage::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�  --д�ļ�
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->city << "  "
			<< this->m_EmpArray[i]->date << "  "
			<< this->m_EmpArray[i]->first << "  "
			<< this->m_EmpArray[i]->second << "  "
			<< this->m_EmpArray[i]->third << "  "
			<< this->m_EmpArray[i]->people << "  "
			<< this->m_EmpArray[i]->regionId << endl;

	}
	ofs.close();

}

int StatisticalManage::get_Num()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
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
	//���ұ��
	int dSelect;
	int num = 0;
	while (ifs >> city && ifs >> date && ifs >> first && ifs >> second && ifs >> third
		&& ifs >> people && ifs >> dSelect)
	{
		num++;
	}
	ifs.close();
	return num;
}
//��ʼ������
void StatisticalManage::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
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
	//���ұ��
	int dSelect;
	int index = 0;
	while (ifs >> city && ifs >> date && ifs >> first && ifs >> second && ifs >> third
		&& ifs >> people && ifs >> dSelect)
	{
		Region* region = NULL;
		if (dSelect == 1)
		{
			region = new China(city, date, first, second, third, people, dSelect);
		}
		else if (dSelect == 2)
		{
			region = new Russia(city, date, first, second, third, people, dSelect);
		}
		else
		{
			region = new USA(city, date, first, second, third, people, dSelect);
		}
		//�����������
		this->m_EmpArray[index] = region;
		index++;
	}
}

void StatisticalManage::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int StatisticalManage::isExist(string city2, int regionId2)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->city == city2 && this->m_EmpArray[i]->regionId == regionId2)
		{
			index = i;
			break;
		}
	}
	return index;
}
//ɾ������
void StatisticalManage::del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫɾ���ĳ��У�" << endl;
		string city;
		cin >> city;
		cout << "�ó���λ���ĸ�����" << endl;
		cout << "1,�й�" << endl;
		cout << "2,����˹" << endl;
		cout << "3,����" << endl;
		int regionid;
		cin >> regionid;
		int n = 0;
		//int index = this->isExist(city, regionid);
		while ((this->isExist(city, regionid)) != -1)
		{
			n++;
			int index = this->isExist(city, regionid);
			if (index != -1)
			{
				for (int i = index; i < this->m_EmpNum - 1; i++)
				{
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}
				this->m_EmpNum--;
				this->save();
			}
		}
		if (n == 0)cout << "ɾ��ʧ�ܣ�δ�ҵ�������" << endl;
		else cout << "ɾ���ɹ�" << endl;

	}
	system("pause");
	system("cls");
}

//�޸����ݼ�
//void StatisticalManage::mod_Emp()
//{
//	if (this->m_FileIsEmpty)
//	{
//		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
//	}
//	else
//	{
//		cout << "�����������޸ĵĳ��У�" << endl;
//		string city;
//		cin >> city;
//		cout << "�ó���λ���ĸ�����" << endl;
//		cout << "1,�й�" << endl;
//		cout << "2,����˹" << endl;
//		cout << "3,����" << endl;
//		int regionid;
//		cin >> regionid;
//
//		int ret = this->isExist(city, regionid);
//		if (ret != -1)
//		{
//			delete this->m_EmpArray[ret];
//			//cout << "�鵽���ұ��Ϊ��" << regionid << "����Ϊ��" << date << "������" << endl;
//
//			//����
//			string city;
//			//����
//			string date;
//			//��һ��ҵ����
//			float first;
//			//�ڶ���ҵ����
//			float second;
//			//������ҵ����
//			float third;
//			//�����õ���
//			float people;
//			//���ұ��
//			int dSelect;
//
//			cout << "��ѡ���µĹ��ң�" << endl;
//			cout << "1,�й�" << endl;
//			cout << "2,����˹" << endl;
//			cout << "3,�㽭" << endl;
//			cin >> dSelect;
//
//			cout << "�������µĳ���:" << endl;
//			cin >> city;
//			cout << "�������µ�����:" << endl;
//			cin >> date;
//			cout << "�������µ�����ȷ������" << endl;
//			cin >> first;
//			cout << "�������µ��ۼ�ȷ������" << endl;
//			cin >> second;
//			cout << "�������µ��ۼ���������" << endl;
//			cin >> third;
//			cout << "�������µ��ۼ���������" << endl;
//			cin >> people;
//
//			Region* region = NULL;
//			switch (dSelect)
//			{
//			case 1:  //�й�
//				region = new China(city, date, first, second, third, people, 1);
//				break;
//			case 2: //����˹
//				region = new Russia(city, date, first, second, third, people, 2);
//				break;
//			case 3: //����
//				region = new USA(city, date, first, second, third, people, 3);
//				break;
//			default:
//				break;
//			}
//			//�������ݵ�������
//			this->m_EmpArray[ret] = region;
//			cout << "�޸ĳɹ���" << endl;
//			//���浽�ļ�
//			this->save();
//		}
//		else
//		{
//			cout << "�޸�ʧ�ܣ����޴����ݣ�" << endl;
//		}
//	}
//	system("pause");
//	system("cls");
//}

//�޸����� ��
void StatisticalManage::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�����������޸ĵĳ��У�" << endl;
		string city;
		cin >> city;
		cout << "�ó���λ���ĸ�����" << endl;
		cout << "1,�й�" << endl;
		cout << "2,����˹" << endl;
		cout << "3,����" << endl;
		int regionid;
		cin >> regionid;
		string city2;
		cout << "���������޸�Ϊ�ĸ�����" << endl;
		cin >> city2;
		int n = 0;
		//Region* region = NULL;
		//int ret = this->isExist(city, regionid);
		while ((this->isExist(city, regionid)) != -1)
		{
			n++;
			int index = this->isExist(city, regionid);
			if (index != -1)
			{
				for (int i = index; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->city == city)
					{
						this->m_EmpArray[i]->city = city2;
					}
				}
				//�������ݵ�������
				//this->m_EmpArray[index] = region;
				cout << "�޸ĳɹ���" << endl;
				//���浽�ļ�
				this->save();
			}
		}
		if (n == 0)cout << "�޸�ʧ�ܣ�δ�ҵ��ó�������" << endl;

	}
	system("pause");
	system("cls");
}
//��������
void StatisticalManage::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1�������в���" << endl;
		cout << "2�������ұ�Ų���" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			string city;
			cout << "��������ҵĳ��У�" << endl;
			cin >> city;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->city == city)
				{
					/*cout << "���ҳɹ�������Ϊ��" << m_EmpArray[i]->date
						<< "����������" << endl;*/
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴�����
				cout << "����ʧ�ܣ����޴�����" << endl;
			}

		}
		else if (select == 2)
		{
			int regionid;
			cout << "��������ұ�ţ�" << endl;
			cout << "1,�й�" << endl;
			cout << "2,����˹" << endl;
			cout << "3,����" << endl;
			cin >> regionid;
			bool flag = false; //���ҵı�־
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->regionId == regionid)
				{
					/*cout << "���ҳɹ������ұ��Ϊ��" << m_EmpArray[i]->regionId
						<< "����������" << endl;*/
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴�����
				cout << "����ʧ�ܣ����޴�����" << endl;
			}
		}
		/*else if (select == 3)
		{

			cout << "��������Ҫ���ҵ���������ұ�ţ�" << endl;
			string date;
			cin >> date;
			cout << "1,�й�" << endl;
			cout << "2,����˹" << endl;
			cout << "3,����" << endl;
			int regionid;
			cin >> regionid;

			int ret = this->isExist(date, regionid);
			if (ret != -1)
			{
				cout << "���ҳɹ�����������Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴����ݣ�" << endl;
			}
		}*/
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}
//Ԥ��
void StatisticalManage::predict_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		double arr[100] = { 0 };
		cout << "����������Ԥ��ĳ��У�" << endl;
		string city;
		cin >> city;
		cout << "�ó���λ���ĸ�����" << endl;
		cout << "1,�й�" << endl;
		cout << "2,����˹" << endl;
		cout << "3,����" << endl;
		int regionid;
		cin >> regionid;
		int n = 0;
		if ((this->isExist(city, regionid)) != -1)
		{
			n++;
			int index = this->isExist(city, regionid);
			if (index != -1)
			{
				int count = 0;
				for (int i = index; i < this->m_EmpNum; i++)
				{
					count++;
					if (count > 30) break;
					arr[i] = this->m_EmpArray[i]->first + this->m_EmpArray[i]->second + this->m_EmpArray[i]->third + this->m_EmpArray[i]->people;
				}
				double data[30][2] = { 0 };
				int count2 = 0;
				for (int i = index; i < m_EmpNum; i++)
				{
					count2++;
					if (count2 > 30) break;
					data[i - index][0] = i - index + 1, data[i - index][1] = arr[i];
				}
				double sum_x = 0;
				double sum_y = 0;
				double sum_xy = 0;
				double sum_x2 = 0;
				for (int i = 0; i < 30; i++)
				{
					sum_x += data[i][0];
					sum_y += data[i][1];
					sum_xy += data[i][0] * data[i][1];
					sum_x2 += data[i][0] * data[i][0];
				}
				double a, b;
				a = (sum_xy - sum_x * sum_y / 30) / (sum_x2 - sum_x * sum_x / 30);
				b = sum_y / 30 - a * sum_x / 30;
				cout << "б��k=" << a << "�ؾ�b=" << b << endl;
				int m, d, x = 0;
				cout << "��������Ԥ��2022����һ����" << endl;
				cin >> m;
				cout << "��������Ԥ��2022�������һ��" << endl;
				cin >> d;
				if (m == 1)  x = d;
				if (m == 2) x = d + 31;
				if (m == 3) x = d + 59;
				if (m == 4) x = d + 90;
				if (m == 5) x = d + 120;
				if (m == 6) x = d + 151;
				if (m == 7) x = d + 181;
				if (m == 8) x = d + 212;
				if (m == 9) x = d + 243;
				if (m == 10) x = d + 273;
				if (m == 11) x = d + 304;
				if (m == 12) x = d + 334;
				cout << "Ԥ�����Ϊ��" << a * x + b << endl;
			}
		}
		if (n == 0)cout << "Ԥ��ʧ�ܣ�δ�ҵ��ó�������" << endl;
	}
	system("pause");
	system("cls");


}
//ͳ��
void StatisticalManage::count_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			cout << "|" << this->m_EmpArray[i]->getRegionName()
				<< "\t|" << this->m_EmpArray[i]->city
				<< "\t|" << this->m_EmpArray[i]->date;

			float a[4]; a[0] = this->m_EmpArray[i]->first, a[1] = this->m_EmpArray[i]->second, a[2] = this->m_EmpArray[i]->third, a[3] = this->m_EmpArray[i]->people;

			for (int m = 0; m < 3; m++)
			{
				for (int j = 0; j < 3 - m; j++)
				{
					if (a[j + 1] > a[j])
					{
						float tmp = a[j + 1];
						a[j + 1] = a[j]; a[j] = tmp;
					}
				}
			}
			int b1 = 0, b2 = 0, b3 = 0, b4 = 0;
			for (int j = 0; j < 4; j++)
			{
				if (a[j] == this->m_EmpArray[i]->first && b1 == 0)
				{
					b1++; cout << "\t|��һ��ҵ:" << a[j];
				};
				if (a[j] == this->m_EmpArray[i]->second && b2 == 0)
				{
					b2++; cout << "\t|�ڶ���ҵ:" << a[j];
				};
				if (a[j] == this->m_EmpArray[i]->third && b3 == 0)
				{
					b3++;  cout << "\t|������ҵ:" << a[j];
				}
				if (a[j] == this->m_EmpArray[i]->people && b4 == 0)
				{
					b4++;  cout << "\t|����" << a[j];
				}
			}
			cout << endl;
		}

		system("pause");
		system("cls");
	}
	int regionid;
	cout << "��ѡ����ҽ���ͳ�ƣ�" << endl;
	cout << "1,�й�" << endl;
	cout << "2,����˹" << endl;
	cout << "3,����" << endl;
	cin >> regionid;
	bool flag = false; //���ҵı�־
	double f = 0, s = 0, t = 0, p = 0;
	for (int i = 0; i < m_EmpNum; i++)
	{

		if (this->m_EmpArray[i]->regionId == regionid)
		{
			/*cout << "���ҳɹ������ұ��Ϊ��" << m_EmpArray[i]->regionId
				<< "����������" << endl;*/
			f += this->m_EmpArray[i]->first; s += this->m_EmpArray[i]->second; t += this->m_EmpArray[i]->third; p += this->m_EmpArray[i]->people;
			flag = true;
		}
	}
	if (flag == false)
	{
		//���޴�����
		cout << "����ʧ�ܣ����޴˹�������" << endl;
	}
	else
	{
		cout << "�ù��Ҹ���ҵ�ܵ�������" << endl;
		cout << "��һ��ҵ��" << f << "�ڶ���ҵ��" << s << "������ҵ��" << t << "�����õ磺" << p << endl;
	}
	system("pause");
	system("cls");
}
//�������
void StatisticalManage::clean_Emp()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//��ģʽ��ios::trunc ������ڰ���ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray != NULL)
				{
					delete this->m_EmpArray[i];
				}

			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

int main()
{

	StatisticalManage sm;
	int choice = 0;
	while (true)
	{
		//չʾ�˵�
		sm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			sm.exitSystem();//�˳�ϵͳ
			break;
		case 1:
			sm.Add_Emp();
			//�����Ϣ
			break;
		case 2:
			sm.show_Emp();//��ʾ��Ϣ
			break;
		case 3:
			sm.del_Emp();//ɾ����Ϣ
			break;
		case 4:
			sm.mod_Emp();//�޸���Ϣ
			break;
		case 5:
			sm.find_Emp();//������Ϣ
			break;
		case 6:
			sm.clean_Emp();//����ļ�
			break;
		case 7:
			sm.count_Emp();//ͳ�Ƶ���
			break;
		case 8:
			sm.predict_Emp();//Ԥ�����
			break;
		default:
			break;
		}
	}
	system("pause");
	system("cls");
	return 0;
}
