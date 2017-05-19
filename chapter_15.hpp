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

	BookBase(const BookBase& b)
	{
		price_ = b.price_;
		i_ = b.i_;
		isbn_ = b.isbn_;
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
		// 带多态性质的base class应该生命一个virtual析构函数
		// 若class带有任何virtual函数，就应该有virtual析构函数
	}
	
private:
	BookBase operator=(const BookBase& b)
	{
		// 不允许使用
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

	//using BookBase::BookBase;			// 继承构造函数
	BulkBook(const BulkBook &b)
	{
		// 先调用基类拷贝，再拷贝派生类自有对象
		// 移动构造函数同理（operator=）
		BookBase::BookBase(b);
		min_qty_ = b.min_qty_;
		discount_ = b.discount_;
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

class AWOV
{
public:
	virtual ~AWOV() = 0
	{
		// 纯虚析构函数需提供定义
	}
};

void chapter_15_func1();
void chapter_15_func2();
void chapter_15_func3();
void chapter_15_func4();

#endif		// CHAPTER_15_HPP_
