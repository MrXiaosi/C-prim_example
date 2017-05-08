//********************************************************
// chapter_13������ƹ���
// ���캯�����������캯����������ֵ�����������������
//********************************************************
#ifndef CHAPTER_13_HPP_
#define CHAPTER_13_HPP_

#include <set>

//*************
// HasPtr1��
// ָ��string
// ��������ֵ������������string��ʽ��ÿ�ζ���Ҫ�ͷž�string
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
		// ��ֵ��������ס���£�
		// 1.��������������ֵ�������������ȷ�������Ƚ��Ҳ���󿽱�����ʱ����֤��
		// 2.�������ֵ�������������������Ϳ������캯���Ĺ���
		auto new_ps = new std::string(*p.ps_);
		delete ps_;								// �ͷž��ڴ�
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
		// ͨ������£������Ҫ�Զ�����������
		// ��ô�������졢��ֵ����Ҳ���Զ���
		delete ps_;
	}

private:
	std::string *ps_;
	int i_;
};

//*************
// HasPtr2��
// ָ��string
// ��������ֵ������������ָ�룬ָ����ͬstring����string�û���0ʱstring���ͷ�
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
			// ���û�������û����ͷŶ���
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
	size_t *use_;		// ��¼���������string
};

//*************
// Message�ࡢFolder��
// ��Զ��ϵ
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
	// һ��Folder�п��Ա�����Message
	std::set<Message *> messages_;
};

class Message
{
	// ���캯��������������������������Ӧ�з���ֵ
public:
	explicit Message(const std::string &str = "")
		:contents_(str)
	{	// ���캯��
	}

	Message(const Message &message)
		:contents_(message.contents_), folders_(message.folders_)
	{
		// �������캯��
		add_to_folders(message);
	}

	Message& operator=(const Message &message)
	{
		// ������ֵ�����
		remove_from_folders(message);
		contents_ = message.contents_;
		folders_ = message.folders_;
		add_to_folders(*this);
		return *this;
	}

	void save(Folder& folder)
	{
		// ���浽ָ��folder
		folders_.insert(&folder);
		folder.addMsg(*this);
	}

	void remove(Folder& folder)
	{
		// ��ָ��folderɾ��
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
		// ��ӱ�message��folders��
		for (auto folder : message.folders_)
		{
			folder->addMsg(*this);
		}
	}

	void remove_from_folders(const Message &message)
	{
		// ��folders��ɾ����message
		for (auto folder : message.folders_)
		{
			folder->remMsg(*this);
		}
	}

private:
	std::string contents_;
	// һ��Message���Ա����Folder����
	std::set<Folder *> folders_;
};


//*************
// StrVec��
// ʵ��vector�˸�棨��string��Ա��
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

	std::string *head_;				// ָ���ڴ�ͷ��
	std::string *tail_;				// ָ���ڴ�β��
	std::string *first_free_;		// ָ��δʹ���ڴ�
};


#endif	// CHAPTER_13_HPP_