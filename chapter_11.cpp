#include "stdafx.h"
#include "chapter_11.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <utility>				// pair
#include <set>

using namespace std;

// 有序关键字必须定义了<运算符
// 定义为一个严格弱序，即“小于等于”
// 两个关键字不能同时“小于等于”对方
// k1“小于等于”k2，k2“小于等于”k3，那么k1必须“小于等于”k3
// 若两个关键字都“等于小于”对方，则“等价”，k1“等价”k2，k2“等价”k3，则k1必须“等价”k3

void chapter_11_func1()
{
	// 列表初始化
	map<string, size_t> word_num = {
		{ "one", 1 },
		{ "two", 2 },
		{ "three", 3 }
	};

	map<string, size_t> word_count;
	set<string> exclude = { "the", "but", "and", "or" };
	string word;
	while (cin >> word)
	{
		// 转小写
		for (auto &c : word)
			c = tolower(c);
		// 删除特殊符号
		word.erase(remove_if(word.begin(), word.end(), ispunct));		// remove只是将元素移到末尾，erase才删除
		// 统计不在set内的词
		if (exclude.end() == exclude.find(word))
			// 不存在word关键字时会添加关键字并初始化
			++word_count[word];
	}
	for (const auto &w : word_count)
		cout << w.first << ": " << w.second << endl;
}

void chapter_11_func2()
{
	// pair
	string str;
	int i;
	vector<pair<string, int>> vec;
	while (cin >> str >> i)
	{
		vec.push_back(make_pair(str, i));
		//vec.push_back({ str, i });
		//vec.push_back(pair<string, int>(str, i));
	}
	for (const auto &p : vec)
		cout << p.first << ": " << p.second << endl;
}

void chapter_11_func3()
{
	// insert操作
	map<string, size_t> word_count;
	string word;
	while (cin >> word)
	{
		// insert返回一个pair
		// first是map的迭代器：指向给定关键字的元素
		// second是bool型，表示是否成功（当key已存在时失败）。
		auto ret = word_count.insert(make_pair(word, 1));
		if (!ret.second)				// word已存在
			++ret.first->second;		// 递增计数器
	}
	for (const auto &w : word_count)
		cout << w.first << ": " << w.second << endl;
}

void chapter_11_func4()
{
	map<string, vector<int>> str_ivec;
	string word;
	int i;
	while (cin >> word >> i)
	{
		auto ret = str_ivec.insert({ word, vector<int>(1, i) });
		if (!ret.second)							// word已存在
			(ret.first->second).push_back(i);		// 数据加入vector
	}
	for (const auto &m : str_ivec)
	{
		cout << m.first << ": ";
		for (const auto &i : m.second)
			cout << i << " ";
		cout << endl;
	}
}

void chapter_11_func5()
{
	multimap<string, string> name_lang = {
		{"John", "C++"},
		{"Bowen", "IOS"}, 
		{"Linqun", "Python"},
		{ "John", "Java" }
	};
	// lower_bound(k) 返回迭代器，指向第一个关键字不小于k的元素
	// upper_bound(k) 返回迭代器，指向第一个关键字大于k的元素
	// 配合使用，得到所有具有该关键字的元素范围
	for (auto beg = name_lang.lower_bound("John"), end = name_lang.upper_bound("John");
		beg != end;
		++beg)
	{
		cout << beg->first << ": " << beg->second << endl;
	}
	// equal_range 返回pair<>，两个元素为迭代器，为具有该关键字的范围
	auto pos = name_lang.equal_range("John");
	while (pos.first != pos.second)
	{
		cout << pos.first->first << ": " << pos.first->second << endl;
		++pos.first;
	}
	cout << name_lang.count("John") << endl;
}

//*************
// 单词转换
//*************

map<string, string> build_map(ifstream &relu_file)
{
	map<string, string> trans_map;
	string key;
	string value;
	while (relu_file >> key && getline(relu_file, value))
	{
		if (value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	}
	return trans_map;
}

string trans_word(const string&str, const map<string, string>&trans_map)
{
	auto pos = trans_map.find(str);
	if (pos == trans_map.cend())
		return str;
	else
		return pos->second;
}

void chapter_11_func6()
{
	ifstream relu_file;
	ifstream trans_file;
	relu_file.open("relu_file.txt");
	trans_file.open("trans_file.txt");

	map<string, string>trans_map = build_map(relu_file);
	string line;
	while (getline(trans_file, line))
	{
		istringstream stream(line);
		string word;
		bool first_wrod = true;
		while (stream >> word)
		{
			if (first_wrod)
				first_wrod = false;
			else
				cout << " ";
			cout << trans_word(word, trans_map);
		}
		cout << endl;
	}
}