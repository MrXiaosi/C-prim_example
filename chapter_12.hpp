//********************************************************
// chapter_12、动态内存
// new、allocator、smart pointer
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
	// 允许StrBlobPtr访问私有成员
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
		// 函数名后增加const，则函数内不允许对对象成员做修改操作
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
		:wptr_(sb.data_)				// 弱引用，不增加shared_ptr计数
		, curr_index_(index)
	{
	}

	// 解引用
	std::string& deref() const
	{
		// const函数不能调用非const成员函数
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
		// 检查weak_ptr所指对象是否被释放
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
// 文本查询
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
	// 读取文件，并建立单词到行号的映射
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
	std::shared_ptr<std::vector<std::string>> file_text_;		// 文件内容
	// 每个单词到它所在的行号的集合的映射
	std::map<std::string,
			std::shared_ptr<std::set<line_no>>> word_line_;
};


void chapter_12_func1();
void chapter_12_func2();
void chapter_12_func3();

#endif	//	CHAPTER_12_HPP_