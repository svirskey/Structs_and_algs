#include "string.hpp"

namespace sv
{
	String::String() :str(nullptr), len(0), capacity(0)
	{
#ifdef _DEBUG
		std::cout << "String()" << std::endl;
#endif
	}

	String::String(const char* str)
	{
#ifdef _DEBUG
		std::cout << "String(const char* str)" << std::endl;
#endif

		len = this->strlen(str);
		capacity = len + 1;
		this->str = new char[len + 1];

		for (int i = 0; i < len; i++)
			this->str[i] = str[i];

		this->str[len] = '\0';
	}

	String::String(const String& other)
	{
#ifdef _DEBUG
		std::cout << "String(const String& other)" << std::endl;
#endif

		this->len = other.len;
		this->capacity = other.capacity;
		this->str = new char[other.capacity];

		for (int i = 0; i < len; i++)
			this->str[i] = other.str[i];

		this->str[len] = '\0';
	}

	String::String(size_t capacity) : len(0), capacity(capacity)
	{
#ifdef _DEBUG
		std::cout << "String(int capacity)" << std::endl;
#endif

		str = new char[capacity];
		str[0] = '\0';
	}

	String& String::operator = (const String& other)
	{
#ifdef _DEBUG
		std::cout << "String& operator = (const String& other)" << std::endl;
#endif

		this->len = other.len;
		this->capacity = other.capacity;

		if (this->str != nullptr)
			delete[] this->str;

		this->str = new char[this->capacity];

		for (int i = 0; i < len; i++)
			this->str[i] = other.str[i];

		this->str[len] = '\0';

		return *this;
	}

	String::String(String&& other) noexcept
	{
#ifdef _DEBUG
		std::cout << "String(String&& other)" << std::endl;
#endif

		this->len = other.len;
		this->str = other.str;
		this->capacity = other.capacity;
		other.str = nullptr;
	}

	String& String::operator = (String&& other) noexcept
	{
#ifdef _DEBUG
		std::cout << "String& operator = (String&& other)" << std::endl;
#endif

		if (this->str != nullptr)
			delete[] this->str;

		this->len = other.len;
		this->str = other.str;
		this->capacity = other.capacity;
		other.str = nullptr;

		return *this;
	}

	String String::operator + (const String& other)
	{
		size_t cap;

		//if (this->capacity + other.capacity > this->begin)
		//	cap = int((this->capacity + other.capacity) * this->increase_coef); // todo
		//else
			cap = this->capacity + other.capacity;

		String tmp(cap);

		tmp += *this;
		tmp += other;

		return tmp;
	}

	String& String::operator += (const String& other)
	{
#ifdef _DEBUG
		std::cout << "String& operator += (const String& other)" << std::endl;
#endif

		if (this->capacity > this->len + other.len)
		{
			for (int i = 0; i < other.len; i++)
			{
				this->str[this->len + i] = other.str[i];
			}
			this->len += other.len;
			this->str[this->len] = '\0';
		}
		else
		{
			char* tmp_str = new char[this->len];

			for (int i = 0; i < this->len; i++)
				tmp_str[i] = this->str[i];

			delete[] this->str;

			if (this->len + other.len > this->begin)
				this->capacity += block_size;
			else
				this->capacity = this->len + other.len + 1;

			this->str = new char[this->capacity];

			for (int i = 0; i < this->len; i++)
				this->str[i] = tmp_str[i];

			delete[] tmp_str;

			for (int i = 0; i < other.len; i++)
				this->str[this->len + i] = other.str[i];

			this->len += other.len;
			this->str[this->len] = '\0';
		}
		return *this;
	}

	size_t String::Length() const
	{
		return len;
	}

	char& String::operator [](int index)
	{
		if (index < 0)
		{
			if (-index > len)
				throw std::exception("Index out of range");

			return str[len + index];
		}
		else
		{
			if (index >= len)
				throw std::exception("Index out of range");

			return str[index];
		}
	}

	void String::reserve(size_t capacity)
	{
		if (this->capacity < capacity)
		{
			//TODO
		}
	}

	const char* String::c_str() const noexcept
	{
		return str;
	}

	String::~String()
	{
		if (str != nullptr)
			delete[] this->str;

#ifdef _DEBUG
		std::cout << "~String()" << std::endl;
#endif
	}

	size_t String::strlen(const char* str)
	{
		size_t i = 0;

		if (!str)
			return 0;
		while (*str++)
			i++;

		return i;
	}

	String& operator + (const char* str, String& string)
	{
		return string; //TODO
	}

	std::ostream& operator<<(std::ostream& os,const String& str)
	{
		os << str.str;
		return os;
	}
}

