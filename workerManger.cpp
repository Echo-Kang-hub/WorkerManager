#include "workerManger.h"
#include "employee.h"
#include "manger.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

WorkerManger::WorkerManger()
{
	this->m_EmpNum = 0;
	this->m_EmpArray = nullptr;

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在!" << endl;

		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;//文件不存在不再执行构造函数
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];//开辟堆区空间
	this->init_Emp();//用文件数据初始化堆区空间数组



}

void WorkerManger::showMenu()
{
	cout << "********************************" << endl;
	cout << "******欢迎使用职工管理系统!******" << endl;
	cout << "*********0.退出管理程序*********" << endl;
	cout << "*********1.增加职工信息*********" << endl;
	cout << "*********2.显示职工信息*********" << endl;
	cout << "*********3.删除离职职工*********" << endl;
	cout << "*********4.修改职工信息*********" << endl;
	cout << "*********5.查找职工信息*********" << endl;
	cout << "*********6.按照编号排序*********" << endl;
	cout << "*********7.清空所有文档*********" << endl;
	cout << "********************************" << endl;

}

void WorkerManger::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManger::Add_Emp()
{
	cout << "请输入添加职工数量:" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace = new Worker * [newSize];

		if (this->m_EmpArray != nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
			cin >> id;


			if (this->IsExist(id) != -1)
			{
				cout << "重复，请重新输入" << endl;
				i = -1;
				continue;
			}


			cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
			cin >> name;

			cout << "请选择该职工岗位:" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = nullptr;

			switch (dSelect)
			{
			case 1:
				worker = new Employee(id ,name,1);
				break;
			case 2:
				worker = new Manger(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[]this->m_EmpArray;

		this->m_EmpArray = newSpace;

		this->m_EmpNum = newSize;

		this->save();

		this->m_FileIsEmpty = false;

		cout << "成功添加" << addNum << "名新职工!"<<endl;

	}
	else
	{
		cout << "输入数据错误" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManger::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManger::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)//读取成功为true，读取失败为false，读到末尾标识符也是读取失败了
	{
		num++;
	}

	ifs.close();

	return num;
}

void WorkerManger::init_Emp()//读取文件数据存入程序中
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = nullptr;

		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manger(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;

		ifs.close();
	}
}

void WorkerManger::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//for (int i = 0; i < m_EmpNum; ++i) // 这里添加了对i的自增操作，确保循环正常进行且不会越界
		//{
		//	if (i >= 0 && i < m_EmpNum) // 添加数组越界检查
		//	{
		//		this->m_EmpArray[i]->showInfo();
		//	}
		//	else
		//	{
		//		cout << "数组索引越界错误，当前索引: " << i << endl;
		//		break; // 或者根据具体需求进行其他处理，比如记录错误并继续尝试等
		//	}
		//}
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();//0x00007FF69A2EC69A 处(位于 职工管理系统.exe 中)引发的异常: 0xC0000005: 读取位置 0xFFFFFFFFFFFFFFFF 时发生访问冲突。
		}
	}

	system("pause");

	system("cls");
}

void WorkerManger::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		
		cout << "请输入要删除职工的编号：" << endl;
		int id = 0;
		cin >> id;
		
		int index = this->IsExist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];//数据前移
			}
			this->m_EmpNum--;

			//同步文件中
			this->save();

			cout << "删除成功" << endl;

			if (this->m_EmpNum == 0)
			{
				this->m_FileIsEmpty = true;
			}
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
	
}

int WorkerManger::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;

			break;
		}
	}
	return index;
}

void WorkerManger::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号" << endl;
		int id = 0;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			
			delete this->m_EmpArray[ret];//不是删除数组，是删除数组的一个元素的内容

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;

			cin >> dSelect;

			Worker* worker = nullptr;

			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manger(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;

			this->save();

			cout << "修改成功" << endl;

			
		}
		else
		{
			cout << "修改失败，职工不存在！" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManger::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if(select==2)
		{
			string name;
			cout << "请输入查找的姓名" << endl;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为：" <<this->m_EmpArray[i]->m_Id
						<<"号职工信息如下："<< endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}

			if (flag == false)
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManger::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;

		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1.按职工号进行升序" << endl;
		cout << "2.按职工号进行降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功！排序后的结果为：" << endl;

		this->save();

		this->Show_Emp();
	}
}

void WorkerManger::Clean_Emp()
{
	cout << "确定清空？" << endl;
	cout << "1、清空" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = nullptr;
			}

			delete[] this->m_EmpArray;
			this->m_EmpArray = nullptr;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}

		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");

}

WorkerManger::~WorkerManger()
{
	if (this->m_EmpArray != nullptr)
	{
		delete[]this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}