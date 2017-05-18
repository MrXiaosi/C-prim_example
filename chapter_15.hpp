//********************************************************
// chapter_15 面向对象程序设计
// 继承、派生、虚函数等
//********************************************************
#ifndef CHAPTER_15_HPP_
#define CHAPTER_15_HPP_

#include <iostream>
#include <string>

using namespace std;

//class BookBase final		final禁止类被继承
class BookBase
{
public:
	explicit BookBase(const string &str = string(), double pri = 0.0)
		:isbn_(str), price_(pri)
	{
	}

	string isbn() const
	{
		return isbn_;
	}

	double price() const
	{
		return price_;
	}

	void set_i(size_t i)
	{
		i_ = i;
	}

	size_t i()
	{
		return i_;
	}

	virtual double net_price(size_t n) const
	{
		return n * price_;
	}

	virtual ~BookBase()
	{
	}

private:
	
	BookBase(const BookBase&)
	{
		// 不允许拷贝
	}

	BookBase operator=(const BookBase&)
	{
		// 不允许赋值
	}

private:
	string isbn_;

protected:
	// protected成员可被本类、友元、派生类访问
	double price_;
	static size_t i_;
};

class BulkBook :public BookBase
{
	// private 派生，可以访问基类对象的private
	// public 公有派生，则基类的公有成员也是派生类接口的组成部分，
	// 能将派生类型的对象绑定到基类的引用或指针上
public:
	BulkBook(const string&str=string(), double pri=0.0, size_t m=0, double discount=0)
		:BookBase(str, pri),
		min_qty_(m),
		discount_(discount)
	{
	}

	// 改写虚函数时形参、返回值需严格匹配（返回值特例：基类B的虚函数f返回B*，C继承B，改写f返回值可以是C*）
	// override显示注明改写基类虚函数，标注后编译器会帮助检查是否匹配
	// 若不改写，将直接继承基类
	// 注意：若虚函数使用默认实参，则基类和派生类中定义的默认实参最好一致
	double net_price(size_t n) const override
	{
		return n >= min_qty_ ? n*price_*discount_ : n*price_;
	}

	void test(const BookBase &b)
	{
	}

	~BulkBook()
	{
	}
private:
	size_t min_qty_;
	double discount_;
};




void chapter_15_func1();
void chapter_15_func2();
void chapter_15_func3();
void chapter_15_func4();

#endif		// CHAPTER_15_HPP_