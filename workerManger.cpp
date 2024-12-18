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
		cout << "�ļ�������!" << endl;

		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;//�ļ������ڲ���ִ�й��캯��
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];//���ٶ����ռ�
	this->init_Emp();//���ļ����ݳ�ʼ�������ռ�����



}

void WorkerManger::showMenu()
{
	cout << "********************************" << endl;
	cout << "******��ӭʹ��ְ������ϵͳ!******" << endl;
	cout << "*********0.�˳��������*********" << endl;
	cout << "*********1.����ְ����Ϣ*********" << endl;
	cout << "*********2.��ʾְ����Ϣ*********" << endl;
	cout << "*********3.ɾ����ְְ��*********" << endl;
	cout << "*********4.�޸�ְ����Ϣ*********" << endl;
	cout << "*********5.����ְ����Ϣ*********" << endl;
	cout << "*********6.���ձ������*********" << endl;
	cout << "*********7.��������ĵ�*********" << endl;
	cout << "********************************" << endl;

}

void WorkerManger::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManger::Add_Emp()
{
	cout << "���������ְ������:" << endl;
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

			cout << "�������" << i + 1 << "����ְ�����:" << endl;
			cin >> id;


			if (this->IsExist(id) != -1)
			{
				cout << "�ظ�������������" << endl;
				i = -1;
				continue;
			}


			cout << "�������" << i + 1 << "����ְ������:" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ:" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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

		cout << "�ɹ����" << addNum << "����ְ��!"<<endl;

	}
	else
	{
		cout << "�������ݴ���" << endl;
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

	while (ifs >> id && ifs >> name && ifs >> dId)//��ȡ�ɹ�Ϊtrue����ȡʧ��Ϊfalse������ĩβ��ʶ��Ҳ�Ƕ�ȡʧ����
	{
		num++;
	}

	ifs.close();

	return num;
}

void WorkerManger::init_Emp()//��ȡ�ļ����ݴ��������
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//for (int i = 0; i < m_EmpNum; ++i) // ��������˶�i������������ȷ��ѭ�����������Ҳ���Խ��
		//{
		//	if (i >= 0 && i < m_EmpNum) // �������Խ����
		//	{
		//		this->m_EmpArray[i]->showInfo();
		//	}
		//	else
		//	{
		//		cout << "��������Խ����󣬵�ǰ����: " << i << endl;
		//		break; // ���߸��ݾ�����������������������¼���󲢼������Ե�
		//	}
		//}
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();//0x00007FF69A2EC69A ��(λ�� ְ������ϵͳ.exe ��)�������쳣: 0xC0000005: ��ȡλ�� 0xFFFFFFFFFFFFFFFF ʱ�������ʳ�ͻ��
		}
	}

	system("pause");

	system("cls");
}

void WorkerManger::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		
		cout << "������Ҫɾ��ְ���ı�ţ�" << endl;
		int id = 0;
		cin >> id;
		
		int index = this->IsExist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];//����ǰ��
			}
			this->m_EmpNum--;

			//ͬ���ļ���
			this->save();

			cout << "ɾ���ɹ�" << endl;

			if (this->m_EmpNum == 0)
			{
				this->m_FileIsEmpty = true;
			}
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı��" << endl;
		int id = 0;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			
			delete this->m_EmpArray[ret];//����ɾ�����飬��ɾ�������һ��Ԫ�ص�����

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;

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

			cout << "�޸ĳɹ�" << endl;

			
		}
		else
		{
			cout << "�޸�ʧ�ܣ�ְ�������ڣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManger::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "��������ҵ�ְ�����" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if(select==2)
		{
			string name;
			cout << "��������ҵ�����" << endl;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" <<this->m_EmpArray[i]->m_Id
						<<"��ְ����Ϣ���£�"<< endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}

			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManger::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;

		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.��ְ���Ž�������" << endl;
		cout << "2.��ְ���Ž��н���" << endl;

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

		cout << "����ɹ��������Ľ��Ϊ��" << endl;

		this->save();

		this->Show_Emp();
	}
}

void WorkerManger::Clean_Emp()
{
	cout << "ȷ����գ�" << endl;
	cout << "1�����" << endl;
	cout << "2������" << endl;

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

		cout << "��ճɹ���" << endl;
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