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
	// �����ַ�ʽ����֤��ȡ��ȷ
	while (cin >> inval)
	{
		// ��ȡ�����ɹ�
		cout << inval << endl;
		break;
	}
}

//*************
// �ļ���ȡ
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