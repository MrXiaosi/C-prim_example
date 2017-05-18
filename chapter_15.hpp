//********************************************************
// chapter_15 �������������
// �̳С��������麯����
//********************************************************
#ifndef CHAPTER_15_HPP_
#define CHAPTER_15_HPP_

#include <iostream>
#include <string>

using namespace std;

//class BookBase final		final��ֹ�౻�̳�
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
		// ��������
	}

	BookBase operator=(const BookBase&)
	{
		// ������ֵ
	}

private:
	string isbn_;

protected:
	// protected��Ա�ɱ����ࡢ��Ԫ�����������
	double price_;
	static size_t i_;
};

class BulkBook :public BookBase
{
	// private ���������Է��ʻ�������private
	// public ���������������Ĺ��г�ԱҲ��������ӿڵ���ɲ��֣�
	// �ܽ��������͵Ķ���󶨵���������û�ָ����
public:
	BulkBook(const string&str=string(), double pri=0.0, size_t m=0, double discount=0)
		:BookBase(str, pri),
		min_qty_(m),
		discount_(discount)
	{
	}

	// ��д�麯��ʱ�βΡ�����ֵ���ϸ�ƥ�䣨����ֵ����������B���麯��f����B*��C�̳�B����дf����ֵ������C*��
	// override��ʾע����д�����麯������ע����������������Ƿ�ƥ��
	// ������д����ֱ�Ӽ̳л���
	// ע�⣺���麯��ʹ��Ĭ��ʵ�Σ��������������ж����Ĭ��ʵ�����һ��
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