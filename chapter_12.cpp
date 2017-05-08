#include "stdafx.h"
#include "chapter_12.hpp"

#include <iostream>
#include <fstream>

void chapter_12_func1()
{
	// StrBlob的成员data_是shared_ptr类型，
	// 因此b1、b2指向的是同一块内存，当b2离开作用域被销毁时，b1还存在，该内存数据不会被销毁
	// 输出结果都为4
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
	// new分配内存时，将分配内存和对象构造结合在一起。例：new std::string[10]，在分配10个string空间的同时，构造了10个空string
	// allcator将分配内存空间与构造对象分离，分配空间后，当需要时再构造对象，减少浪费，效率更高
	int n = 4;
	std::allocator<std::string> string_allocator;
	auto const strings_ptr = string_allocator.allocate(n);			// 分配n个未初始化string对象
	auto curr_ptr1 = strings_ptr;
	string_allocator.construct(curr_ptr1++, "hello");				// 构造对象
	string_allocator.construct(curr_ptr1++, 10, 'c');
	std::cout << strings_ptr->c_str() << std::endl;
	std::cout << (strings_ptr + 1)->c_str() << std::endl;

	while (curr_ptr1 != strings_ptr)						// 销毁对象，调用string的析构
		string_allocator.destroy(--curr_ptr1);
	string_allocator.deallocate(strings_ptr, n);			// 销毁后释放（也可继续使用，重新构造对象）

	// ******
	// uninitialized_copy、uninitialized_fill_n使用
	std::vector<int> vi = { 1, 2, 3, 4, 5 };
	std::allocator<int> int_allocator;
	auto const ints_ptr = int_allocator.allocate(vi.size() * 2);
	auto q = std::uninitialized_copy(vi.begin(), vi.end(), ints_ptr);		// 拷贝元素，返回最后一个构造的元素后一个位置
	std::uninitialized_fill_n(q, vi.size(), 10);							// 填充元素

	auto curr_ptr2 = ints_ptr;
	while (curr_ptr2 != ints_ptr + vi.size() * 2)
		std::cout << *(curr_ptr2++) << " ";
	std::cout << std::endl;
	while (curr_ptr2 != ints_ptr)					// 销毁
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