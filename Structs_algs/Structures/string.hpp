#pragma once

#include <iostream>
#include <ostream>

namespace sv
{
	class String
	{
		char* str;	// todo small string optimization with union or std::variant
		size_t len;
		size_t capacity;

		size_t block_size = 16; 
		size_t begin = 0;

		size_t strlen(const char* str);

		friend std::ostream& operator <<(std::ostream& os, const String& str);

		friend String& operator + (const char* str, String& string);

	public:

		String();

		String(const char* str);

		String(const String& other);

		String(String&& other) noexcept;

		String(size_t capacity);

		String& operator = (const String& other);

		String& operator = (String&& other) noexcept;

		String operator + (const String& other);

		String& operator += (const String& other);

		char& operator [](int index);

		size_t Length() const;

		void reserve(size_t capacity);

		const char* c_str() const noexcept;

		~String();
	};

	String& operator + (const char* str, String& string);

	std::ostream& operator <<(std::ostream& os,const String& str);
}
