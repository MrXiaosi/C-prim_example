#include "stdafx.h"
#include "chapter_15.hpp"

#include <ostream>

size_t BookBase::i_ = 0;

double print_total(ostream &os, const BookBase &item, size_t n)
{
	double ret = item.net_price(n);
	// 回避虚函数机制，强制使用bookbase版本net_price
	// 通常当派生类的虚函数要调用它覆盖的基类虚函数时使用
	// 例：基类中完成了一些派生类都要完成的任务，派生类可直接调用，再执行自身的操作
	//double ret = item.BookBase::net_price(n);
	os << "ibsn: " << item.isbn() 
		<< ". price: "<<item.price() << ". sold: " << n << ". total: " << ret;
	return ret;
}

void chapter_15_func1()
{
	// 虚函数作用：动态绑定，调用各自类型的函数
	BookBase base("bookbase", 3.5);
	BulkBook bulk("bulkbook", 4.5, 3, 0.8);
	print_total(cout, base, 3);
	cout << endl;
	print_total(cout, bulk, 3);
	cout << endl;
	// 静态变量在整个继承体系只存在唯一的实例
	base.set_i(1);
	cout << "base.i_: " << base.i() << endl;
	cout << "bulk.i_: " << bulk.i() << endl;
}

void chapter_15_func2()
{
}

void chapter_15_func3()
{
}

void chapter_15_func4()
{
}