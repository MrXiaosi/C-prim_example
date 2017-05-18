#include "stdafx.h"
#include "chapter_15.hpp"

#include <ostream>

size_t BookBase::i_ = 0;

double print_total(ostream &os, const BookBase &item, size_t n)
{
	double ret = item.net_price(n);
	// �ر��麯�����ƣ�ǿ��ʹ��bookbase�汾net_price
	// ͨ������������麯��Ҫ���������ǵĻ����麯��ʱʹ��
	// ���������������һЩ�����඼Ҫ��ɵ������������ֱ�ӵ��ã���ִ������Ĳ���
	//double ret = item.BookBase::net_price(n);
	os << "ibsn: " << item.isbn() 
		<< ". price: "<<item.price() << ". sold: " << n << ". total: " << ret;
	return ret;
}

void chapter_15_func1()
{
	// �麯�����ã���̬�󶨣����ø������͵ĺ���
	BookBase base("bookbase", 3.5);
	BulkBook bulk("bulkbook", 4.5, 3, 0.8);
	print_total(cout, base, 3);
	cout << endl;
	print_total(cout, bulk, 3);
	cout << endl;
	// ��̬�����������̳���ϵֻ����Ψһ��ʵ��
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