#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Manger :public Worker
{
public:
	Manger(int id, string name, int dId);

	virtual void showInfo();
	virtual string getDeptName();

	~Manger();
};