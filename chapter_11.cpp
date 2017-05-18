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

// ����ؼ��ֱ��붨����<�����
// ����Ϊһ���ϸ����򣬼���С�ڵ��ڡ�
// �����ؼ��ֲ���ͬʱ��С�ڵ��ڡ��Է�
// k1��С�ڵ��ڡ�k2��k2��С�ڵ��ڡ�k3����ôk1���롰С�ڵ��ڡ�k3
// �������ؼ��ֶ�������С�ڡ��Է����򡰵ȼۡ���k1���ȼۡ�k2��k2���ȼۡ�k3����k1���롰�ȼۡ�k3

void chapter_11_func1()
{
	// �б��ʼ��
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
		// תСд
		for (auto &c : word)
			c = tolower(c);
		// ɾ���������
		word.erase(remove_if(word.begin(), word.end(), ispunct));		// removeֻ�ǽ�Ԫ���Ƶ�ĩβ��erase��ɾ��
		// ͳ�Ʋ���set�ڵĴ�
		if (exclude.end() == exclude.find(word))
			// ������word�ؼ���ʱ����ӹؼ��ֲ���ʼ��
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
	// insert����
	map<string, size_t> word_count;
	string word;
	while (cin >> word)
	{
		// insert����һ��pair
		// first��map�ĵ�������ָ������ؼ��ֵ�Ԫ��
		// second��bool�ͣ���ʾ�Ƿ�ɹ�����key�Ѵ���ʱʧ�ܣ���
		auto ret = word_count.insert(make_pair(word, 1));
		if (!ret.second)				// word�Ѵ���
			++ret.first->second;		// ����������
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
		if (!ret.second)							// word�Ѵ���
			(ret.first->second).push_back(i);		// ���ݼ���vector
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
	// lower_bound(k) ���ص�������ָ���һ���ؼ��ֲ�С��k��Ԫ��
	// upper_bound(k) ���ص�������ָ���һ���ؼ��ִ���k��Ԫ��
	// ���ʹ�ã��õ����о��иùؼ��ֵ�Ԫ�ط�Χ
	for (auto beg = name_lang.lower_bound("John"), end = name_lang.upper_bound("John");
		beg != end;
		++beg)
	{
		cout << beg->first << ": " << beg->second << endl;
	}
	// equal_range ����pair<>������Ԫ��Ϊ��������Ϊ���иùؼ��ֵķ�Χ
	auto pos = name_lang.equal_range("John");
	while (pos.first != pos.second)
	{
		cout << pos.first->first << ": " << pos.first->second << endl;
		++pos.first;
	}
	cout << name_lang.count("John") << endl;
}

//*************
// ����ת��
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