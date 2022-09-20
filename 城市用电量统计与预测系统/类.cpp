#include "类.h"
#include <stdlib.h>
void StatisticalManage::Show_Menu()
{
	cout << "****************************************" << endl;
	cout << "*******  欢迎使用电量统计系统！ ********" << endl;
	cout << "*************  0.退出程序  *************" << endl;
	cout << "*************  1.添加信息  *************" << endl;
	cout << "*************  2.显示信息  *************" << endl;
	cout << "*************  3.删除信息  *************" << endl;
	cout << "*************  4.修改信息  *************" << endl;
	cout << "*************  5.查找信息  *************" << endl;
	cout << "*************  6.清空文档  *************" << endl;
	cout << "*************  7.统计电量  *************" << endl;
	cout << "*************  8.预测电量  *************" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
void StatisticalManage::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(1);
}

StatisticalManage::StatisticalManage()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0; //初始化人数
		this->m_EmpArray = NULL; //初始化数组
		this->m_FileIsEmpty = true; //初始化文件为空标志
		ifs.close();//关闭文件
		return;
	}
	//文件存在，并且记录为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->m_EmpNum = 0; //初始化人数
		this->m_EmpArray = NULL; //初始化数组
		this->m_FileIsEmpty = true; //初始化文件为空标志
		ifs.close();//关闭文件
		return;
	}
	int num = this->get_Num();
	//cout << "数据个数为：" << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Region * [this->m_EmpNum];
	init_Emp(); //初始化统计数量
}

//析构函数
StatisticalManage::~StatisticalManage()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		m_EmpArray = NULL;
	}
}

//添加信息
void StatisticalManage::Add_Emp()
{
	cout << "请输入增加统计的数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Region** newspace = new Region * [newSize];

		//将原空间下内容存放到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}
		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
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
			//国家编号
			int dSelect;

			cout << "请选择国家：（输入国家前面的序号）" << endl;
			cout << "1,中国" << endl;
			cout << "2,俄罗斯" << endl;
			cout << "3,美国" << endl;
			cin >> dSelect;

			cout << "请输入第" << i + 1 << "个数据的城市" << endl;
			cin >> city;
			cout << "请输入第" << i + 1 << "个数据的日期" << endl;
			cin >> date;
			cout << "请输入第" << i + 1 << "个数据的第一产业用电量" << endl;
			cin >> first;
			cout << "请输入第" << i + 1 << "个数据的第二产业用电量" << endl;
			cin >> second;
			cout << "请输入第" << i + 1 << "个数据的第三产业用电量" << endl;
			cin >> third;
			cout << "请输入第" << i + 1 << "个数据的居民用电量" << endl;
			cin >> people;


			Region* region = NULL;
			switch (dSelect)
			{
			case 1:  //湖北
				region = new China(city, date, first, second, third, people, 1);
				break;
			case 2: //广东
				region = new Russia(city, date, first, second, third, people, 2);
				break;
			case 3: //浙江
				region = new USA(city, date, first, second, third, people, 3);
				break;
			default:
				break;
			}


			newspace[this->m_EmpNum + i] = region;

		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//更改新空间指向
		this->m_EmpArray = newspace;
		//更新新的数据条数
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;

		//提示信息
		cout << "添加成功" << addNum << "条数据" << endl;
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;

	}
	system("pause");
	system("cls");
}

//保存文件
void StatisticalManage::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //用输出的方式打开文件  --写文件
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
	//国家编号
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
//初始化数组
void StatisticalManage::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
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
	//国家编号
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
		//存放再数组中
		this->m_EmpArray[index] = region;
		index++;
	}
}

void StatisticalManage::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
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
//删除数据
void StatisticalManage::del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要删除的城市：" << endl;
		string city;
		cin >> city;
		cout << "该城市位于哪个国家" << endl;
		cout << "1,中国" << endl;
		cout << "2,俄罗斯" << endl;
		cout << "3,美国" << endl;
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
		if (n == 0)cout << "删除失败，未找到该数据" << endl;
		else cout << "删除成功" << endl;

	}
	system("pause");
	system("cls");
}

//修改数据假
//void StatisticalManage::mod_Emp()
//{
//	if (this->m_FileIsEmpty)
//	{
//		cout << "文件不存在或记录为空！" << endl;
//	}
//	else
//	{
//		cout << "请输入您想修改的城市：" << endl;
//		string city;
//		cin >> city;
//		cout << "该城市位于哪个国家" << endl;
//		cout << "1,中国" << endl;
//		cout << "2,俄罗斯" << endl;
//		cout << "3,美国" << endl;
//		int regionid;
//		cin >> regionid;
//
//		int ret = this->isExist(city, regionid);
//		if (ret != -1)
//		{
//			delete this->m_EmpArray[ret];
//			//cout << "查到国家编号为：" << regionid << "日期为：" << date << "的数据" << endl;
//
//			//城市
//			string city;
//			//日期
//			string date;
//			//第一产业电量
//			float first;
//			//第二产业电量
//			float second;
//			//第三产业电量
//			float third;
//			//居民用电量
//			float people;
//			//国家编号
//			int dSelect;
//
//			cout << "请选择新的国家：" << endl;
//			cout << "1,中国" << endl;
//			cout << "2,俄罗斯" << endl;
//			cout << "3,浙江" << endl;
//			cin >> dSelect;
//
//			cout << "请输入新的城市:" << endl;
//			cin >> city;
//			cout << "请输入新的日期:" << endl;
//			cin >> date;
//			cout << "请输入新的新增确诊人数" << endl;
//			cin >> first;
//			cout << "请输入新的累计确诊人数" << endl;
//			cin >> second;
//			cout << "请输入新的累计治愈人数" << endl;
//			cin >> third;
//			cout << "请输入新的累计死亡人数" << endl;
//			cin >> people;
//
//			Region* region = NULL;
//			switch (dSelect)
//			{
//			case 1:  //中国
//				region = new China(city, date, first, second, third, people, 1);
//				break;
//			case 2: //俄罗斯
//				region = new Russia(city, date, first, second, third, people, 2);
//				break;
//			case 3: //美国
//				region = new USA(city, date, first, second, third, people, 3);
//				break;
//			default:
//				break;
//			}
//			//更改数据到数组中
//			this->m_EmpArray[ret] = region;
//			cout << "修改成功！" << endl;
//			//保存到文件
//			this->save();
//		}
//		else
//		{
//			cout << "修改失败，查无此数据！" << endl;
//		}
//	}
//	system("pause");
//	system("cls");
//}

//修改数据 真
void StatisticalManage::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入您想修改的城市：" << endl;
		string city;
		cin >> city;
		cout << "该城市位于哪个国家" << endl;
		cout << "1,中国" << endl;
		cout << "2,俄罗斯" << endl;
		cout << "3,美国" << endl;
		int regionid;
		cin >> regionid;
		string city2;
		cout << "请问您想修改为哪个城市" << endl;
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
				//更改数据到数组中
				//this->m_EmpArray[index] = region;
				cout << "修改成功！" << endl;
				//保存到文件
				this->save();
			}
		}
		if (n == 0)cout << "修改失败，未找到该城市数据" << endl;

	}
	system("pause");
	system("cls");
}
//查找数据
void StatisticalManage::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1，按城市查找" << endl;
		cout << "2，按国家编号查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			string city;
			cout << "请输入查找的城市：" << endl;
			cin >> city;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->city == city)
				{
					/*cout << "查找成功，日期为：" << m_EmpArray[i]->date
						<< "的数据如下" << endl;*/
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此数据
				cout << "查找失败，查无此数据" << endl;
			}

		}
		else if (select == 2)
		{
			int regionid;
			cout << "请输入国家编号：" << endl;
			cout << "1,中国" << endl;
			cout << "2,俄罗斯" << endl;
			cout << "3,美国" << endl;
			cin >> regionid;
			bool flag = false; //查找的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->regionId == regionid)
				{
					/*cout << "查找成功，国家编号为：" << m_EmpArray[i]->regionId
						<< "的数据如下" << endl;*/
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此数据
				cout << "查找失败，查无此数据" << endl;
			}
		}
		/*else if (select == 3)
		{

			cout << "请输入想要查找的日期与国家编号：" << endl;
			string date;
			cin >> date;
			cout << "1,中国" << endl;
			cout << "2,俄罗斯" << endl;
			cout << "3,美国" << endl;
			int regionid;
			cin >> regionid;

			int ret = this->isExist(date, regionid);
			if (ret != -1)
			{
				cout << "查找成功！该数据信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此数据！" << endl;
			}
		}*/
		else
		{
			cout << "输入选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}
//预测
void StatisticalManage::predict_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		double arr[100] = { 0 };
		cout << "请输入您想预测的城市：" << endl;
		string city;
		cin >> city;
		cout << "该城市位于哪个国家" << endl;
		cout << "1,中国" << endl;
		cout << "2,俄罗斯" << endl;
		cout << "3,美国" << endl;
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
				cout << "斜率k=" << a << "截距b=" << b << endl;
				int m, d, x = 0;
				cout << "请问你想预测2022年哪一个月" << endl;
				cin >> m;
				cout << "请问你想预测2022年该月哪一天" << endl;
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
				cout << "预测电量为：" << a * x + b << endl;
			}
		}
		if (n == 0)cout << "预测失败，未找到该城市数据" << endl;
	}
	system("pause");
	system("cls");


}
//统计
void StatisticalManage::count_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
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
					b1++; cout << "\t|第一产业:" << a[j];
				};
				if (a[j] == this->m_EmpArray[i]->second && b2 == 0)
				{
					b2++; cout << "\t|第二产业:" << a[j];
				};
				if (a[j] == this->m_EmpArray[i]->third && b3 == 0)
				{
					b3++;  cout << "\t|第三产业:" << a[j];
				}
				if (a[j] == this->m_EmpArray[i]->people && b4 == 0)
				{
					b4++;  cout << "\t|居民：" << a[j];
				}
			}
			cout << endl;
		}

		system("pause");
		system("cls");
	}
	int regionid;
	cout << "请选择国家进行统计：" << endl;
	cout << "1,中国" << endl;
	cout << "2,俄罗斯" << endl;
	cout << "3,美国" << endl;
	cin >> regionid;
	bool flag = false; //查找的标志
	double f = 0, s = 0, t = 0, p = 0;
	for (int i = 0; i < m_EmpNum; i++)
	{

		if (this->m_EmpArray[i]->regionId == regionid)
		{
			/*cout << "查找成功，国家编号为：" << m_EmpArray[i]->regionId
				<< "的数据如下" << endl;*/
			f += this->m_EmpArray[i]->first; s += this->m_EmpArray[i]->second; t += this->m_EmpArray[i]->third; p += this->m_EmpArray[i]->people;
			flag = true;
		}
	}
	if (flag == false)
	{
		//查无此数据
		cout << "查找失败，查无此国家数据" << endl;
	}
	else
	{
		cout << "该国家各产业总电量如下" << endl;
		cout << "第一产业：" << f << "第二产业：" << s << "第三产业：" << t << "居民用电：" << p << endl;
	}
	system("pause");
	system("cls");
}
//清空数据
void StatisticalManage::clean_Emp()
{
	cout << "确认清空？" << endl;
	cout << "1，确认" << endl;
	cout << "2，返回" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式，ios::trunc 如果存在啊，删除文件并重新创建
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
		cout << "清空成功！" << endl;
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
		//展示菜单
		sm.Show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			sm.exitSystem();//退出系统
			break;
		case 1:
			sm.Add_Emp();
			//添加信息
			break;
		case 2:
			sm.show_Emp();//显示信息
			break;
		case 3:
			sm.del_Emp();//删除信息
			break;
		case 4:
			sm.mod_Emp();//修改信息
			break;
		case 5:
			sm.find_Emp();//查找信息
			break;
		case 6:
			sm.clean_Emp();//清空文件
			break;
		case 7:
			sm.count_Emp();//统计电量
			break;
		case 8:
			sm.predict_Emp();//预测电量
			break;
		default:
			break;
		}
	}
	system("pause");
	system("cls");
	return 0;
}
