#include "stdafx.h"
#include "chapter_9.hpp"

#include <iostream>
// �ɱ��С���飬֧�ֿ���������ʡ���β��֮��λ�ò����ɾ������
#include <vector>
// �̶���С���飬��֧����ӻ�ɾ��Ԫ��
#include <array>
// ˫�˶��У�֧�ֿ���������ʡ���ͷβλ�ò���/ɾ���ٶȺܿ�
#include <deque>
// ˫������ֻ֧��˫��˳����ʡ���list���κ�λ�ý��в���/ɾ�����ܿ�
#include <list>
// ��������ֻ֧��˫��˳����ʡ���list���κ�λ�ý��в���/ɾ�����ܿ�
#include <forward_list>
// ��vector���ƣ�ר�����ڱ����ַ�
#include <string>

//*************
// ��������������
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
		// li.begin()����iterator,li.cbegin()����const_iterator
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
// ��ʼ������ֵ
//*************
void chapter_9_func2()
{
	using namespace std;
	// ��ʼ��
	list<int> li1;				// ��Ԫ��Ĭ�Ϲ��캯����ʼ��
	list<int> li2(li1);			// ������li1��li2������ͬ����
	list<int> li3(li1.begin(), li1.end());		// ����������ָ����Χ
	list<int> li4(10);			// li4�а���10��Ԫ�أ�Ĭ�Ϸ��纯����ʼ��
	list<int> li5(10, 1);		// li5����10��Ԫ�أ���ʼֵΪ1

	// ��ֵ
	li2 = li1;
	li2 = { 1, 2, 3, 4, 5, 6 };
	swap(li1, li2);
	li2.assign(li1.begin(), li1.end());
	li1.assign({ 1, 2, 3, 4, 5, 6 });
	li1.assign(10, 1);			// ��10��Ԫ���滻Ϊ1

	list<char *> name_list{"Jane", "Tom", "Jack"};
	vector<string> name_vector;
	// name_vector��ֵΪname_list����
	name_vector.assign(name_list.begin(), name_list.end());
	for (const auto &name : name_vector)
		cout << name << " ";
	cout << endl;

	// ���Ԫ��
	li1.push_back(1);
	li1.push_front(1);
	li1.insert(li1.begin(), 4);				// ָ��������֮ǰ����4
	li1.insert(li1.begin(), 1, 4);			// ָ��������֮ǰ����1��4
	li1.insert(li1.begin(), { 1, 2, 3 });
	li1.insert(li1.begin(), li2.begin(), li2.end());	// li1��ͷ����li2 begin��end

	// ɾ��Ԫ��
	li1.pop_back();
	li1.pop_front();
	li1.erase(li1.begin());
	li1.erase(li1.begin(), li1.end());		// ɾ����������Χ
	li1.clear();							// ɾ������

	// ����ia��vector��ɾ������
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
	vector<int> vi1(ia, end(ia));
	for (auto it = vi1.begin(); it != vi1.end();)
		if (*it & 0x1)
			it = vi1.erase(it);				// erase������ɾ��Ԫ��֮��Ԫ��
		else
			++it;
	for (const auto &num : vi1)
		cout << num << " ";
	cout << endl;
	// ɾ������������ż��
	vector<int> vi2(ia, end(ia));
	auto it = vi2.begin();
	while (it != vi2.end())			// ��Ӧ����end��������vi2���޸�end�ᷢ���ı�
	{
		if (*it & 0x1)
			it = vi2.erase(it);
		else
		{
			// ��it֮ǰ�ٲ���һ��*it
			// insert���ز����Ԫ�ص�����
			it = vi2.insert(it, *it);
			it = it + 2;
		}
	}
	for (const auto &num : vi2)
		cout << num << " ";
	cout << endl;
}

//*************
// vector��string��������
//*************
void chapter_9_func3()
{
	using namespace std;
	vector<int> vi{ 0, 1, 2, 3, 4 };
	vi.reserve(10);										// �趨viԤ���ռ�Ϊ10��Ԫ��
	cout << "vi.size: " << vi.size() << endl;			// �ѱ���Ԫ�ظ���
	cout << "vi.capacity: " << vi.capacity() << endl;	// �������¿ռ�������ܱ���ĸ���(Ԥ���ռ�)
}

//*************
// string����ķ���
//*************
void chapter_9_func4()
{
	using namespace std;
	// ����
	const char *cp = "hello world!";
	string s1(cp);						// ����cp
	string s2(cp, 2);					// ��cp����2���ַ�
	string s3(cp, 2, 3);				// ��cp��2�ַ���ʼ������3��
	cout << s1 << " " << s2 << " " << s3 << endl;
	string s4 = s1.substr(0, 5);		// 0~5�ַ�
	string s5 = s1.substr(6);			// 6~end�ַ�
	// �޸�
	s1.insert(0, "h");
	s1.erase(s1.begin());
	s1.append(" hello C++!");
	s1.replace(0, 5, "HELLO");			// ��0λ�ã�ɾ��5���ַ�������"HELLO"
	// ����
	string dept("rs03p714p3");
	string number("0123456789");
	// ���������ӣ�posָ�������￪ʼ����
	auto pos = dept.find("p");				// ����p��һ�γ���λ��
	pos = dept.rfind("p");					// ����p���һ�γ���λ��
	pos = dept.find_first_of(number);		// number���κ�һ���ַ���һ�γ���λ��
	pos = dept.find_last_of(number);		// number���κ�һ���ַ����һ�γ���λ��
	pos = dept.find_first_not_of(number);	// dept�е�һ������number���ֵ��ַ�
}