#include "stdafx.h"
#include "chapter_12.hpp"

#include <iostream>
#include <fstream>

void chapter_12_func1()
{
	// StrBlob�ĳ�Աdata_��shared_ptr���ͣ�
	// ���b1��b2ָ�����ͬһ���ڴ棬��b2�뿪����������ʱ��b1�����ڣ����ڴ����ݲ��ᱻ����
	// ��������Ϊ4
	StrBlob b1;
	{
		StrBlob b2 = { "a", "b", "c" };
		b1 = b2;
		b2.push_back("d");
		std::cout << "b2 size:" << b2.size() << std::endl;
	}
	std::cout << "b1 size:" << b1.size() << std::endl;
}

void chapter_12_func2()
{
	// new�����ڴ�ʱ���������ڴ�Ͷ���������һ������new std::string[10]���ڷ���10��string�ռ��ͬʱ��������10����string
	// allcator�������ڴ�ռ��빹�������룬����ռ�󣬵���Ҫʱ�ٹ�����󣬼����˷ѣ�Ч�ʸ���
	int n = 4;
	std::allocator<std::string> string_allocator;
	auto const strings_ptr = string_allocator.allocate(n);			// ����n��δ��ʼ��string����
	auto curr_ptr1 = strings_ptr;
	string_allocator.construct(curr_ptr1++, "hello");				// �������
	string_allocator.construct(curr_ptr1++, 10, 'c');
	std::cout << strings_ptr->c_str() << std::endl;
	std::cout << (strings_ptr + 1)->c_str() << std::endl;

	while (curr_ptr1 != strings_ptr)						// ���ٶ��󣬵���string������
		string_allocator.destroy(--curr_ptr1);
	string_allocator.deallocate(strings_ptr, n);			// ���ٺ��ͷţ�Ҳ�ɼ���ʹ�ã����¹������

	// ******
	// uninitialized_copy��uninitialized_fill_nʹ��
	std::vector<int> vi = { 1, 2, 3, 4, 5 };
	std::allocator<int> int_allocator;
	auto const ints_ptr = int_allocator.allocate(vi.size() * 2);
	auto q = std::uninitialized_copy(vi.begin(), vi.end(), ints_ptr);		// ����Ԫ�أ��������һ�������Ԫ�غ�һ��λ��
	std::uninitialized_fill_n(q, vi.size(), 10);							// ���Ԫ��

	auto curr_ptr2 = ints_ptr;
	while (curr_ptr2 != ints_ptr + vi.size() * 2)
		std::cout << *(curr_ptr2++) << " ";
	std::cout << std::endl;
	while (curr_ptr2 != ints_ptr)					// ����
		int_allocator.destroy(--curr_ptr2);
	int_allocator.deallocate(ints_ptr, vi.size() * 2);
}

void chapter_12_func3()
{
	std::ifstream infile;
	infile.open("chapter_12.hpp");
	TextQuery tq(infile);
	while (true)
	{
		std::cout << "enter word to look for, or q to quit: ";
		std::string s;
		if (!(std::cin >> s) || "q" == s) break;
		print(std::cout, tq.query(s));
	}
}