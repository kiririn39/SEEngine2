//
// Created by Vlad Boroday on 2024-12-30.
//

#ifndef UNTITLED4_STRING_H
#define UNTITLED4_STRING_H

#include "includes.h"
#include "simpleTypes.h"
#include "fmt/format.h"

template<u64 StaticSize>
class FixedString {
	char data[StaticSize] = {};

	u64 _size = 0;
public:
	static constexpr u64 Capacity = StaticSize;

	pcstr Begin() const
	{
		return &data[0];
	}

	pcstr End() const
	{
		return Begin() + _size;
	}

	u64 Size() const
	{
		return _size;
	}

	bool IsEmpty() const
	{
		return _size == 0;
	}

	template<typename... T>
	FixedString& Format(pcstr format, T&& ... args)
	{
		auto result = fmt::format_to_n(data, StaticSize, fmt::runtime(format), std::forward<T>(args)...);
		ASSERT(result.size < StaticSize);

		_size = result.size;
		*result.out = 0;

		return *this;
	}
};

typedef FixedString<1024> String;


#endif //UNTITLED4_STRING_H
