//********************************************************
// chapter_12����̬�ڴ�
// new��allocator��smart pointer
//********************************************************
#ifndef CHAPTER_12_HPP_
#define CHAPTER_12_HPP_

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <list>

class StrBlob
{
	// ����StrBlobPtr����˽�г�Ա
	friend class StrBlobPtr;
public:
	StrBlob() 
		:data_(std::make_shared<std::vector<std::string>>())
	{
	}

	StrBlob(std::initializer_list<std::string> il)
		:data_(std::make_shared<std::vector<std::string>>(il))
	{
	}

	size_t size() const
	{
		// ������������const�������ڲ�����Զ����Ա���޸Ĳ���
		return data_->size();
	}

	bool empty() const
	{
		return data_->empty();
	}

	void push_back(const std::string &str)
	{
		data_->push_back(str);
	}

	void pop_back()
	{
		check(0, "pop_back on empty StrBlob");
		data_->pop_back();
	}

	std::string& front()
	{
		check(0, "front on empty StrBlob");
		return data_->front();
	}

	std::string& back()
	{
		check(0, "back on empty StrBlob");
		return data_->back();
	}

private:
	void check(size_t i, const std::string &msg)
	{
		if (i >= data_->size())
			throw std::out_of_range(msg);
	}

private:
	std::shared_ptr<std::vector<std::string>> data_;
};

class StrBlobPtr
{
public:
	StrBlobPtr()
		:curr_index_(0)
	{
	}

	StrBlobPtr(StrBlob& sb, size_t index = 0)
		:wptr_(sb.data_)				// �����ã�������shared_ptr����
		, curr_index_(index)
	{
	}

	// ������
	std::string& deref() const
	{
		// const�������ܵ��÷�const��Ա����
		auto p = check(curr_index_, "dereference past end");
		return (*p)[curr_index_];
	}

	StrBlobPtr& incr()
	{
		check(curr_index_, "increment past end of StrBlobPtr");
		++curr_index_;
		return *this;
	}

private:
	std::shared_ptr<std::vector<std::string>> check(size_t index, const std::string& msg) const
	{
		// ���weak_ptr��ָ�����Ƿ��ͷ�
		auto ret = wptr_.lock();
		if (!ret)
			throw std::runtime_error("unbond StrBlobPtr");
		if (index >= ret->size())
			throw std::out_of_range(msg);
		return ret;
	}

private:
	size_t curr_index_;
	std::weak_ptr<std::vector<std::string>> wptr_;
};

//*************
// �ı���ѯ
//*************

class QueryResult
{
	friend std::ostream& print(std::ostream& os, const QueryResult& qr)
	{
		os << qr.sought_ << " occur " << qr.lines_->size() << " times" << std::endl;
		for (auto num : *qr.lines_)
		{
			os << "\t(line " << num + 1 << ") "
				<< *(qr.file_text_->begin() + num) << std::endl;
		}
		return os;
	}

public:
	using line_no = std::vector<std::string>::size_type;

	QueryResult(std::string s,
		std::shared_ptr<std::set<line_no>> l,
		std::shared_ptr<std::vector<std::string>> f
		)
		:sought_(s), file_text_(f), lines_(l)
	{
	}

private:
	std::string sought_;
	std::shared_ptr<std::vector<std::string>> file_text_;
	std::shared_ptr<std::set<line_no>> lines_;
};

class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	// ��ȡ�ļ������������ʵ��кŵ�ӳ��
	TextQuery(std::ifstream &is) :file_text_(new std::vector<std::string>)
	{
		std::string line_text;
		while (std::getline(is, line_text))
		{
			file_text_->push_back(line_text);
			int n = file_text_->size() - 1;
			std::istringstream stream(line_text);
			std::string word;
			while (stream >> word)
			{
				auto &lines = word_line_[word];
				if (!lines)
					lines.reset(new std::set<line_no>);
				lines->insert(n);
			}
		}
	}

	QueryResult query(const std::string sought) const
	{
		static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
		auto loc = word_line_.find(sought);
		if (word_line_.end() == loc)
			return QueryResult(sought, nodata, file_text_);
		else
			return QueryResult(sought, loc->second, file_text_);
	}

private:
	std::string in_file_;
	std::shared_ptr<std::vector<std::string>> file_text_;		// �ļ�����
	// ÿ�����ʵ������ڵ��кŵļ��ϵ�ӳ��
	std::map<std::string,
			std::shared_ptr<std::set<line_no>>> word_line_;
};


void chapter_12_func1();
void chapter_12_func2();
void chapter_12_func3();

#endif	//	CHAPTER_12_HPP_