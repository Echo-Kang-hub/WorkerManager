#include "manger.h"

Manger::Manger(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

void Manger::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ������:" << this->m_Name
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ��:����ϰ彻�������񣬲��·������Ա��" << endl;
}
string Manger::getDeptName()
{
	return string("����");
}

Manger::~Manger()
{

}