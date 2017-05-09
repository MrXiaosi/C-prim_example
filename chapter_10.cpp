#include "stdafx.h"
#include "chapter_10.hpp"

#include <iostream>
#include <algorithm>
#include <numeric>				// accumulate
#include <iterator>				// back_inserter
#include <functional>			// bind,ref,cref
#include <vector>
#include <list>

using namespace std;

void chapter_10_func1()
{
	vector<int> vi{ 0, 1, 3, 11, 20, 3, 17, 20 };
	list<string> ls{ "hello", "hi", "welcome", "hi", "world" };
	
	int ival = 3;
	// 只读容器元素的算法
	// 查找第一个3，返回迭代器 使用==运算符
	// 注：find_if，第三个参数为谓词，找到第一个返回true的元素
	auto result = find(vi.cbegin(), vi.cend(), ival);
	cout << "the integer value " << ival 
		<< (vi.end() == result ? " no found" : " is found") << endl;
	string sval = "hi";
	// 统计ls中hi的个数
	auto s = count(ls.cbegin(), ls.cend(), sval);
	cout << "count \"" << sval.c_str() << "\": " << s << endl;
	// 求和 使用+运算符
	auto sum = accumulate(vi.cbegin(), vi.cend(), 0);
	cout << "vi sum: " << sum << endl;
	// 写入容器元素的算法
	// fill
	fill(vi.begin(), vi.end(), 1);
	fill_n(vi.begin(), vi.size(), 1);
	// back_inserter
	auto it = back_inserter(vi);
	*it = 2;								// 通过对it赋值，会添加元素到vi中
	fill_n(back_inserter(vi), 5, 3);		// 添加5个元素
	for (const auto &i : vi)
		cout << i << " ";
	cout << endl;
	// copy
	vector<int> vi_cp(vi.size(), 0);
	copy(vi.begin(), vi.end(), vi_cp.begin());		// 从vi拷贝到vi_cp，需保证vi_cp.size() >= vi.size()
	// replace
	replace(vi.begin(), vi.end(), 1, 13);			// 将vi中的1替换为13
	replace_copy(vi.begin(), vi.end(), back_inserter(vi_cp), 1, 13);	// 不改变原内容，替换后的内容添加到vi_cp
}

bool isShorter(const string &str1, const string &str2)
{
	return str1.size() < str2.size();
}

bool isLonger(const string &str1)
{
	return str1.size() >= 5;
}

void chapter_10_func2()
{
	vector<string> ls{ "red", "blue", "yellow", "red", "grey", "orange" };
	// sort使用<运算符
	sort(ls.begin(), ls.end());							// 排序,sort要求容器的迭代器是随机迭代器
	auto unique_pos = unique(ls.begin(), ls.end());		// 将重复元素排列到序列末尾
	ls.erase(unique_pos, ls.end());						// 删除
	cout << "sort and unique: \n\t";
	for (const auto &it : ls)
		cout << it.c_str() << " ";
	cout << endl;
	// 自定义排序方式
	sort(ls.begin(), ls.end(), isShorter);				// 按长度排序
	cout << "sort by length: \n\t";
	for (const auto &it : ls)
		cout << it.c_str() << " ";
	cout << endl;
	// 内容划分
	auto part_itr = partition(ls.begin(), ls.end(), isLonger);		// 长度大等于5的被排在前面
	auto it = ls.begin();
	cout << "partition by length bigger then 5: \n\t";
	for (const auto &it : ls)
		cout << it.c_str() << " ";
	cout << endl;
}

// lambda使用
// 捕获方式：[] 空捕获列表	[names] 显式捕获值	[&] 隐式捕获引用	[=] 显示捕获引用
// 显式隐式可混用，需先指定默认方式&、=
void chapter_10_func3()
{
	// stable_sort 不同于sort:维持相等元素的原有位置
	vector<string> ls{ "red", "blue", "yellow", "grey", "orange" };
	stable_sort(ls.begin(), ls.end(),
		[](const string &s1, const string &s2){	return s1.size() < s2.size(); }
	);
	cout << "lambda(sort by length):\n\t";
	for (const auto &it : ls)
		cout << it.c_str() << " ";
	cout << endl;
	// find_if
	int len = 5;
	auto result = find_if(ls.begin(), ls.end(),
		[len](const string &str){return str.size() > len; });	// 使用局部变量len，查找第一个长度大于len的元素
	if (ls.end() == result)
		cout << "no found" << endl;
	else
		cout << "found: " << result->c_str() << endl;
	// for_each		对每个迭代器调用谓词
	cout << "for_each:\n\t";
	for_each(ls.begin(), ls.end(),
		[](const string &str){cout << str.c_str() << " "; });
	cout << endl;
}

bool check_size(const string &str, int len, ostream &os)
{
	return str.size() >= len;
}

bool check_num(const int &a, const int &n)
{
	return a < n;
}

// bind	当多处需要使用相同lambda时，可以用bind
void chapter_10_func4()
{
	vector<string> ls{ "red", "blue", "yellow", "grey", "orange" };
	int len = 5;
	auto c = count_if(ls.begin(), ls.end(), bind(check_size, placeholders::_1, len, ref(cout)));	// bind引用ref、cref
	cout << "bind: count len bigger than 5: " << c << endl;

	int n = 10;
	vector<int> vi{ 0, 1, 3, 11, 20, 3, 17, 20 };
	auto pos = partition(vi.begin(), vi.end(), bind(check_num, placeholders::_1, n));
}

void chapter_10_func5()
{
	// Train
	auto sum = [](int a, int b){return a + b; };
	int r = sum(3, 2);
	cout << "3 + 2 = " << r << endl;
	auto sum1 = [r](int a){return a + r; };				// 此时r被拷贝，之后r改变，sum1中的r不会受影响
	cout << r << " + 2 = " << sum1(2) << endl;			// 若采用引用方式则会受影响

	int n = 10;
	vector<int> vi{ 0, 1, 3, 11, 20, 3, 17, 20 };
	auto pos = partition(vi.begin(), vi.end(),
		[n](const int &a){return a <= n; });
	cout << "partition by 10:\n\t";
	auto itr = vi.begin();
	while (itr != vi.end())
	{
		cout << (itr == pos ? "\n\t" : "") << *itr << " ";
		++itr;
	}
	cout << endl;

	vector<string> ls{ "red", "blue", "yellow", "grey", "orange" };
	int len = 5;
	auto c = count_if(ls.begin(), ls.end(),
		[len](const string &str){return str.size() >= len; });
	cout << "lambda: count len bigger than 5: " << c << endl;
}

void show(const string &s, const list<int> &ls)
{
	cout << s.c_str() << ":\n    ";
	for (const auto &val : ls)
		cout << val << " ";
	cout << endl;
}

// 迭代器
void chapter_10_func6()
{
	// 插入迭代器：front_inserter back_inserter inserter
	list<int> ls1 = { 1, 1, 2, 2, 3, 3, 4, 4 };
	list<int> ls2, ls3, ls4, ls5;
	copy(ls1.begin(), ls1.end(), front_inserter(ls2));			// 使用push_front的迭代器
	copy(ls1.begin(), ls1.end(), back_inserter(ls3));			// 使用push_back的迭代器
	copy(ls1.begin(), ls1.end(), inserter(ls4, ls4.begin()));	// 使用insert的迭代器(等同于：insert(it,val);++it;)
	unique_copy(ls1.begin(), ls1.end(), back_inserter(ls5));
	show("ls2", ls2); show("ls3", ls3); show("ls4", ls4); show("ls5", ls5);

	// 流迭代器

	// 反向迭代器（forward_list不支持）
	for (auto r_itr = ls1.rbegin(); r_itr != ls1.rend(); ++r_itr)
		cout << *r_itr << " ";					// 反向迭代器++操作会移到前一个元素，--移到下一个元素
}