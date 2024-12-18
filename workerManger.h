#pragma once
#include <iostream>//包含输入输出流
#include "worker.h"
using namespace std;
class WorkerManger
{
public:
	WorkerManger();

	void showMenu();

	void ExitSystem();

	int m_EmpNum;
	Worker ** m_EmpArray;

	void Add_Emp();

	void save();

	bool m_FileIsEmpty;

	int get_EmpNum();

	void init_Emp();

	void Show_Emp();

	void Del_Emp();

	int IsExist(int id);

	void Mod_Emp();

	void Find_Emp();

	void Sort_Emp();

	void Clean_Emp();

	~WorkerManger();
};
