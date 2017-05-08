//********************************************************
// chapter_13、类设计工具
// 构造函数、拷贝构造函数、拷贝赋值运算符、析构函数等
//********************************************************
#ifndef CHAPTER_13_HPP_
#define CHAPTER_13_HPP_

#include <set>

//*************
// HasPtr1类
// 指向string
// 拷贝、赋值函数以生成新string方式，每次都需要释放旧string
//*************
class HasPtr1
{
public:
	HasPtr1(const std::string &str = std::string())
		:ps_(new std::string(str)), i_(0)
	{
	}

	HasPtr1(const HasPtr1 &p)
		:ps_(new std::string(*p.ps_)), i_(p.i_)
	{
	}

	HasPtr1& operator=(const HasPtr1 &p)
	{
		// 赋值运算符需记住以下：
		// 1.将对象赋予自身，赋值运算符必须能正确工作（先将右侧对象拷贝到临时来保证）
		// 2.大多数赋值运算符组合了析构函数和拷贝构造函数的工作
		auto new_ps = new std::string(*p.ps_);
		delete ps_;								// 释放旧内存
		ps_ = new_ps;
		i_ = p.i_;
		return *this;
	}

	void swap(HasPtr1 &lhs, HasPtr1 &rhs)
	{
		using std::swap;
		swap(lhs.ps_, rhs.ps_);
		swap(lhs.i_, rhs.i_);
	}

	~HasPtr1()
	{
		// 通常情况下，如果需要自定义析构函数
		// 那么拷贝构造、赋值运算也需自定义
		delete ps_;
	}

private:
	std::string *ps_;
	int i_;
};

//*************
// HasPtr2类
// 指向string
// 拷贝、赋值函数以新生成指针，指向相同string，当string用户数0时string被释放
//*************
class HasPtr2
{
public:
	HasPtr2(const std::string &str=std::string())
		:ps_(new std::string(str)), i_(0), use_(new size_t(1))
	{
	}

	HasPtr2(const HasPtr2 &p)
	{
		++(*p.use_);
		check();
		ps_ = p.ps_;
		i_ = p.i_;
		use_ = p.use_;
	}

	HasPtr2& operator=(const HasPtr2 &p)
	{
		ps_ = p.ps_;
		i_ = p.i_;
		return *this;
	}

	void check()
	{
		if (0 == --*use_)
		{
			// 如果没有其他用户，释放对象
			delete ps_;
			delete use_;
		}
	}

	~HasPtr2()
	{
		check();
	}

private:
	std::string *ps_;
	int i_;
	size_t *use_;		// 记录多个对象共享string
};

//*************
// Message类、Folder类
// 多对多关系
//*************

class Message;
class Folder;

class Folder
{
public:
	Folder(const std::set<Message *> &messages = {})
		:messages_(messages)
	{
	}

	size_t size() const
	{
		return messages_.size();
	}

	void addMsg(Message &message)
	{
		messages_.insert(&message);
	}

	void remMsg(Message &message)
	{
		messages_.erase(&message);
	}

private:
	// 一个Folder中可以保存多个Message
	std::set<Message *> messages_;
};

class Message
{
	// 构造函数（包括拷贝）、析构函数不应有返回值
public:
	explicit Message(const std::string &str = "")
		:contents_(str)
	{	// 构造函数
	}

	Message(const Message &message)
		:contents_(message.contents_), folders_(message.folders_)
	{
		// 拷贝构造函数
		add_to_folders(message);
	}

	Message& operator=(const Message &message)
	{
		// 拷贝赋值运算符
		remove_from_folders(message);
		contents_ = message.contents_;
		folders_ = message.folders_;
		add_to_folders(*this);
		return *this;
	}

	void save(Folder& folder)
	{
		// 保存到指定folder
		folders_.insert(&folder);
		folder.addMsg(*this);
	}

	void remove(Folder& folder)
	{
		// 从指定folder删除
		folders_.erase(&folder);
		folder.remMsg(*this);
	}

	void swap(Message & message)
	{
		// swap
		for (auto folder : message.folders_)
			folder->remMsg(message);
		for (auto folder : folders_)
			folder->remMsg(*this);

		std::swap(folders_, message.folders_);
		std::swap(contents_, message.contents_);

		for (auto folder : message.folders_)
			folder->addMsg(message);
		for (auto folder : folders_)
			folder->addMsg(*this);
	}

	~Message()
	{
		remove_from_folders(*this);
	}

private:
	void add_to_folders(const Message &message)
	{
		// 添加本message到folders中
		for (auto folder : message.folders_)
		{
			folder->addMsg(*this);
		}
	}

	void remove_from_folders(const Message &message)
	{
		// 从folders中删除本message
		for (auto folder : message.folders_)
		{
			folder->remMsg(*this);
		}
	}

private:
	std::string contents_;
	// 一个Message可以被多个Folder保存
	std::set<Folder *> folders_;
};


//*************
// StrVec类
// 实现vector阉割版（仅string成员）
//*************
class StrVec

{
public:
	StrVec()
		:head_(nullptr), tail_(nullptr), first_free_(nullptr)
	{
	}

	StrVec(const StrVec &p)
	{
	}

	StrVec& operator=(const StrVec &p)
	{
	}

	~StrVec()
	{
	}


private:
	static std::allocator<std::string> string_allocator_;

	std::string *head_;				// 指向内存头部
	std::string *tail_;				// 指向内存尾部
	std::string *first_free_;		// 指向未使用内存
};


#endif	// CHAPTER_13_HPP_