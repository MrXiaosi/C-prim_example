#include "stdafx.h"
#include "chapter_8.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void chapter_8_func1()
{
	using namespace std;
	int inval;
	// 以这种方式，保证读取正确
	while (cin >> inval)
	{
		// 读取操作成功
		cout << inval << endl;
		break;
	}
}

//*************
// 文件读取
//*************
void chapter_8_func2()
{
	using namespace std;
	vector<string> text_words;
	fstream in;
	in.open("chapter_12.hpp");
	if (in)
	{
		string line;
		while (getline(in, line))
		{
			//istringstream is(line);
			//string word;
			//is >> word;
			text_words.push_back(line);
		}
	}

	cout << "line num: " << text_words.size() << endl;
	for (const auto &word : text_words)
		cout << word << endl;
}