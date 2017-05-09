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
	// ֻ������Ԫ�ص��㷨
	// ���ҵ�һ��3�����ص����� ʹ��==�����
	// ע��find_if������������Ϊν�ʣ��ҵ���һ������true��Ԫ��
	auto result = find(vi.cbegin(), vi.cend(), ival);
	cout << "the integer value " << ival 
		<< (vi.end() == result ? " no found" : " is found") << endl;
	string sval = "hi";
	// ͳ��ls��hi�ĸ���
	auto s = count(ls.cbegin(), ls.cend(), sval);
	cout << "count \"" << sval.c_str() << "\": " << s << endl;
	// ��� ʹ��+�����
	auto sum = accumulate(vi.cbegin(), vi.cend(), 0);
	cout << "vi sum: " << sum << endl;
	// д������Ԫ�ص��㷨
	// fill
	fill(vi.begin(), vi.end(), 1);
	fill_n(vi.begin(), vi.size(), 1);
	// back_inserter
	auto it = back_inserter(vi);
	*it = 2;								// ͨ����it��ֵ�������Ԫ�ص�vi��
	fill_n(back_inserter(vi), 5, 3);		// ���5��Ԫ��
	for (const auto &i : vi)
		cout << i << " ";
	cout << endl;
	// copy
	vector<int> vi_cp(vi.size(), 0);
	copy(vi.begin(), vi.end(), vi_cp.begin());		// ��vi������vi_cp���豣֤vi_cp.size() >= vi.size()
	// replace
	replace(vi.begin(), vi.end(), 1, 13);			// ��vi�е�1�滻Ϊ13
	replace_copy(vi.begin(), vi.end(), back_inserter(vi_cp), 1, 13);	// ���ı�ԭ���ݣ��滻���������ӵ�vi_cp
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
	// sortʹ��<�����
	sort(ls.begin(), ls.end());							// ����,sortҪ�������ĵ����������������
	auto unique_pos = unique(ls.begin(), ls.end());		// ���ظ�Ԫ�����е�����ĩβ
	ls.erase(unique_pos, ls.end());						// ɾ��
	cout << "sort and unique: \n\t";
	for (const auto &it : ls)
		cout << it.c_str() << " ";
	cout << endl;
	// �Զ�������ʽ
	sort(ls.begin(), ls.end(), isShorter);				// ����������
	cout << "sort by length: \n\t";
	for (const auto &it : ls)
		cout << it.c_str() << " ";
	cout << endl;
	// ���ݻ���
	auto part_itr = partition(ls.begin(), ls.end(), isLonger);		// ���ȴ����5�ı�����ǰ��
	auto it = ls.begin();
	cout << "partition by length bigger then 5: \n\t";
	for (const auto &it : ls)
		cout << it.c_str() << " ";
	cout << endl;
}

// lambdaʹ��
// ����ʽ��[] �ղ����б�	[names] ��ʽ����ֵ	[&] ��ʽ��������	[=] ��ʾ��������
// ��ʽ��ʽ�ɻ��ã�����ָ��Ĭ�Ϸ�ʽ&��=
void chapter_10_func3()
{
	// stable_sort ��ͬ��sort:ά�����Ԫ�ص�ԭ��λ��
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
		[len](const string &str){return str.size() > len; });	// ʹ�þֲ�����len�����ҵ�һ�����ȴ���len��Ԫ��
	if (ls.end() == result)
		cout << "no found" << endl;
	else
		cout << "found: " << result->c_str() << endl;
	// for_each		��ÿ������������ν��
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

// bind	���ദ��Ҫʹ����ͬlambdaʱ��������bind
void chapter_10_func4()
{
	vector<string> ls{ "red", "blue", "yellow", "grey", "orange" };
	int len = 5;
	auto c = count_if(ls.begin(), ls.end(), bind(check_size, placeholders::_1, len, ref(cout)));	// bind����ref��cref
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
	auto sum1 = [r](int a){return a + r; };				// ��ʱr��������֮��r�ı䣬sum1�е�r������Ӱ��
	cout << r << " + 2 = " << sum1(2) << endl;			// ���������÷�ʽ�����Ӱ��

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

// ������
void chapter_10_func6()
{
	// �����������front_inserter back_inserter inserter
	list<int> ls1 = { 1, 1, 2, 2, 3, 3, 4, 4 };
	list<int> ls2, ls3, ls4, ls5;
	copy(ls1.begin(), ls1.end(), front_inserter(ls2));			// ʹ��push_front�ĵ�����
	copy(ls1.begin(), ls1.end(), back_inserter(ls3));			// ʹ��push_back�ĵ�����
	copy(ls1.begin(), ls1.end(), inserter(ls4, ls4.begin()));	// ʹ��insert�ĵ�����(��ͬ�ڣ�insert(it,val);++it;)
	unique_copy(ls1.begin(), ls1.end(), back_inserter(ls5));
	show("ls2", ls2); show("ls3", ls3); show("ls4", ls4); show("ls5", ls5);

	// ��������

	// �����������forward_list��֧�֣�
	for (auto r_itr = ls1.rbegin(); r_itr != ls1.rend(); ++r_itr)
		cout << *r_itr << " ";					// ���������++�������Ƶ�ǰһ��Ԫ�أ�--�Ƶ���һ��Ԫ��
}