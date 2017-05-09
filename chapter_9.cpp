#include "stdafx.h"
#include "chapter_9.hpp"

#include <iostream>
// 可变大小数组，支持快速随机访问。在尾部之外位置插入或删除很慢
#include <vector>
// 固定大小数组，不支持添加或删除元素
#include <array>
// 双端队列，支持快速随机访问。在头尾位置插入/删除速度很快
#include <deque>
// 双向链表，只支持双向顺序访问。在list中任何位置进行插入/删除都很快
#include <list>
// 单向链表，只支持双向顺序访问。在list中任何位置进行插入/删除都很快
#include <forward_list>
// 与vector相似，专门用于保存字符
#include <string>

//*************
// 迭代器遍历容器
//*************
void chapter_9_func1()
{
	using namespace std;
	list<int> li{ 1, 2, 3, 4, 5, 6, 7 };
	int number = 3;
	// find number
	bool is_finded = false;
	for (auto it = li.begin(); it != li.end(); ++it)
	{
		// li.begin()返回iterator,li.cbegin()返回const_iterator
		if (number == *it)
		{
			is_finded = true;
			break;
		}
	}
	if (is_finded)
		cout << "found!" << endl;
	else
		cout << "didn't found!" << endl;
}

//*************
// 初始化、赋值
//*************
void chapter_9_func2()
{
	using namespace std;
	// 初始化
	list<int> li1;				// 按元素默认构造函数初始化
	list<int> li2(li1);			// 拷贝，li1、li2必须相同类型
	list<int> li3(li1.begin(), li1.end());		// 拷贝迭代器指定范围
	list<int> li4(10);			// li4中包含10个元素，默认否早函数初始化
	list<int> li5(10, 1);		// li5包含10个元素，初始值为1

	// 赋值
	li2 = li1;
	li2 = { 1, 2, 3, 4, 5, 6 };
	swap(li1, li2);
	li2.assign(li1.begin(), li1.end());
	li1.assign({ 1, 2, 3, 4, 5, 6 });
	li1.assign(10, 1);			// 将10个元素替换为1

	list<char *> name_list{"Jane", "Tom", "Jack"};
	vector<string> name_vector;
	// name_vector赋值为name_list内容
	name_vector.assign(name_list.begin(), name_list.end());
	for (const auto &name : name_vector)
		cout << name << " ";
	cout << endl;

	// 添加元素
	li1.push_back(1);
	li1.push_front(1);
	li1.insert(li1.begin(), 4);				// 指定迭代器之前插入4
	li1.insert(li1.begin(), 1, 4);			// 指定迭代器之前插入1个4
	li1.insert(li1.begin(), { 1, 2, 3 });
	li1.insert(li1.begin(), li2.begin(), li2.end());	// li1开头插入li2 begin到end

	// 删除元素
	li1.pop_back();
	li1.pop_front();
	li1.erase(li1.begin());
	li1.erase(li1.begin(), li1.end());		// 删除迭代器范围
	li1.clear();							// 删除所有

	// 拷贝ia到vector。删除奇数
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
	vector<int> vi1(ia, end(ia));
	for (auto it = vi1.begin(); it != vi1.end();)
		if (*it & 0x1)
			it = vi1.erase(it);				// erase返回所删除元素之后元素
		else
			++it;
	for (const auto &num : vi1)
		cout << num << " ";
	cout << endl;
	// 删除奇数，复制偶数
	vector<int> vi2(ia, end(ia));
	auto it = vi2.begin();
	while (it != vi2.end())			// 不应保存end迭代器，vi2被修改end会发生改变
	{
		if (*it & 0x1)
			it = vi2.erase(it);
		else
		{
			// 在it之前再插入一个*it
			// insert返回插入的元素迭代器
			it = vi2.insert(it, *it);
			it = it + 2;
		}
	}
	for (const auto &num : vi2)
		cout << num << " ";
	cout << endl;
}

//*************
// vector、string容量管理
//*************
void chapter_9_func3()
{
	using namespace std;
	vector<int> vi{ 0, 1, 2, 3, 4 };
	vi.reserve(10);										// 设定vi预留空间为10个元素
	cout << "vi.size: " << vi.size() << endl;			// 已保存元素个数
	cout << "vi.capacity: " << vi.capacity() << endl;	// 不分配新空间情况下能保存的个数(预留空间)
}

//*************
// string额外的方法
//*************
void chapter_9_func4()
{
	using namespace std;
	// 构造
	const char *cp = "hello world!";
	string s1(cp);						// 拷贝cp
	string s2(cp, 2);					// 从cp拷贝2个字符
	string s3(cp, 2, 3);				// 从cp第2字符开始，拷贝3个
	cout << s1 << " " << s2 << " " << s3 << endl;
	string s4 = s1.substr(0, 5);		// 0~5字符
	string s5 = s1.substr(6);			// 6~end字符
	// 修改
	s1.insert(0, "h");
	s1.erase(s1.begin());
	s1.append(" hello C++!");
	s1.replace(0, 5, "HELLO");			// 从0位置，删除5个字符，插入"HELLO"
	// 搜索
	string dept("rs03p714p3");
	string number("0123456789");
	// 参数中增加，pos指定从哪里开始查找
	auto pos = dept.find("p");				// 查找p第一次出现位置
	pos = dept.rfind("p");					// 查找p最后一次出现位置
	pos = dept.find_first_of(number);		// number中任何一个字符第一次出现位置
	pos = dept.find_last_of(number);		// number中任何一个字符最后一次出现位置
	pos = dept.find_first_not_of(number);	// dept中第一个不在number出现的字符
}