// C++prim_example.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "chapter_8.hpp"
#include "chapter_9.hpp"
#include "chapter_12.hpp"
#include "chapter_13.hpp"

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

void chapter_12_func()
{
	chapter_12_func1();
	chapter_12_func2();
	chapter_12_func3();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//chapter_8_func();
	chapter_9_func();
	//chapter_12_func();
	//system("pause");
	getchar();
	return 0;
}