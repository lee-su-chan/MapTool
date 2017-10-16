#pragma once

#include <iostream>

template <typename T>
class BaseSingleton
{
private:
	BaseSingleton() = default;
	~BaseSingleton() = default;

public:
	static T *GetInstance()
	{
		if (instance == nullptr)
			instance = new T();

		return instance;
	}

private:
	static T *instance;
};

template<typename T> T *BaseSingleton<T>::instance = nullptr;