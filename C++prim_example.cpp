// C++prim_example.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "chapter_8.hpp"
#include "chapter_9.hpp"
#include "chapter_10.hpp"
#include "chapter_11.hpp"
#include "chapter_12.hpp"
#include "chapter_13.hpp"
#include "chapter_15.hpp"

using namespace std;

void chapter_8_func()
{
	//chapter_8_func1();
	chapter_8_func2();
}

void chapter_9_func()
{
	chapter_9_func1();
	chapter_9_func2();
	chapter_9_func3();
	//chapter_9_func4();
}

void chapter_10_func()
{
	chapter_10_func1();
	chapter_10_func2();
	chapter_10_func3();
	chapter_10_func5();
	chapter_10_func4();
	chapter_10_func6();
}

void chapter_11_func()
{
	//chapter_11_func1();
	//chapter_11_func2();
	//chapter_11_func3();
	//chapter_11_func4();
	//chapter_11_func5();
	chapter_11_func6();
}

void chapter_12_func()
{
	chapter_12_func1();
	chapter_12_func2();
	chapter_12_func3();
}

void chapter_13_func()
{
	HasPtr1 lhp("hello");
	HasPtr1 rhp(" world");
	//int i = rhp + 3;						// HasPtr1中定义了转int类型运算,隐式调用
	cout << lhp + rhp << endl;
	cout << "compare lhp, rhp: " << (lhp == rhp) << endl;
	int i = lhp + rhp;
}

void chapter_15_func()
{
	chapter_15_func1();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//chapter_8_func();
	//chapter_9_func();
	//chapter_10_func();
	//chapter_11_func();
	//chapter_12_func();
	//chapter_13_func();
	chapter_15_func();
	//system("pause");
	getchar();
	return 0;
}