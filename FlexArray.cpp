#include "FlexArray.h"
#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

FlexArray::FlexArray()
{
	capacity = INITIALCAP; // Initial capacity
	size = 0;
	arr_ = new int[capacity];
	arr_check = new int[capacity];
}

FlexArray::FlexArray(const int *arr, int size)
{
	this->size = size;
	capacity = LO_THRESHOLD * size;
	arr_ = new int[capacity];
	arr_check = new int[capacity];
	int headroom = (capacity - size) / 2;

	for (int i = 0; i < size; i++)
	{
		arr_[headroom + i] = arr[i];
		arr_check[headroom + i] = 1;
	}
}

FlexArray::~FlexArray()
{
}

FlexArray::FlexArray(const FlexArray &other)
{
	capacity = other.capacity;
	size = other.size;
	arr_ = new int[capacity];
	arr_check = new int[capacity];

	for (int i = 0; i < capacity; i++)
	{
		arr_[i] = other.arr_[i];
		arr_check[i] = other.arr_check[i];
	}
}

FlexArray &FlexArray::operator=(const FlexArray &other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] arr_;
	delete[] arr_check;
	capacity = other.capacity;
	size = other.size;
	arr_ = new int[capacity];
	arr_check = new int[capacity];

	for (int i = 0; i < capacity; i++)
	{
		arr_[i] = other.arr_[i];
		arr_check[i] = other.arr_check[i];
	}

	return *this;
}

int FlexArray::getSize() const
{
	return size;
}

int FlexArray::getCapacity() const
{
	return capacity;
}

string FlexArray::print() const
{
	string result = "[";
	int temp = size;

	for (int i = 0; i < capacity; i++)
	{
		if (arr_check[i] == 1)
		{

			result += to_string(arr_[i]);
			temp--;
			if (temp != 0)
			{
				result += ", ";
			}
		}
	}

	result += "]";
	return result;
}

string FlexArray::printAll() const
{
	string result = "[";

	for (int i = 0; i < capacity; i++)
	{

		if (arr_check[i] == 1)
		{
			result += to_string(arr_[i]);
		}
		else
		{
			result += "X";
		}

		if (i < capacity - 1)
		{
			result += ", ";
		}
	}

	result += "]";
	return result;
}

int FlexArray::get(int i) const
{
	int tempIndex = 0;
	if (i >= 0 && i < size)
	{
		for (int j = 0; j < capacity; j++)
		{
			if (arr_check[j] == 1)
			{
				if (tempIndex == i)
				{
					return arr_[j];
				}
				else
				{
					tempIndex++;
				}
			}
		}
	}
	return -1;
}

bool FlexArray::set(int i, int v)
{
	if (i >= 0 && i < size)
	{
		arr_[(capacity - size) / 2 + i] = v;
		return true;
	}
	return false;
}

void FlexArray::push_back(int v)
{
	if (arr_check[capacity - 1] == 1 || capacity == size * HI_THRESHOLD)
	{
		resizeAndRecenter();
	}

	insert(size, v);
}

bool FlexArray::pop_back()
{
	if (size > 0)
	{
		int tempIndex = 0;
		for (int i = 0; i < capacity; i++)
		{
			if (arr_check[i] == 1)
			{
				tempIndex++;
				if (tempIndex == size)
				{
					arr_[i] = 0;
					arr_check[i] = 0;
				}
			}
		}
		size--;
		return true;
	}
	return false;
}

void FlexArray::push_front(int v)
{
	if (arr_check[0] == 1 || capacity == size * 7)
	{
		resizeAndRecenter();
	}

	for (int i = 0; i < capacity; i++)
	{
		if (arr_check[i] == 1)
		{
			arr_[i - 1] = v;
			arr_check[i - 1] = 1;
			break;
		}
	}
	size++;
}

bool FlexArray::pop_front()
{
	if (size > 0)
	{
		for (int i = 0; i < capacity; i++)
		{
			if (arr_check[i] == 1)
			{
				arr_[i] = 0;
				arr_check[i] = 0;
				break;
			}
		}
		size--;
		return true;
	}
	return false;
}

bool FlexArray::insert(int i, int v)
{
	int tempIndex = 0;
	if (i < 0 || i > size)
	{
		return false;
	}
	else if (arr_check[capacity - 1] == 1 && arr_check[0] == 1 || capacity == size * 7)
	{
		resizeAndRecenter();
	}
	else if (size == 0)
	{
		size++;
		arr_[(capacity - size) / 2 + i] = v;
		arr_check[(capacity - size) / 2 + i] = 1;
		return true;
	}

	size++;
	for (int j = 0; j < capacity; j++)
	{

		if (arr_check[j] == 1)
		{
			tempIndex++;
			if (tempIndex == i || i == 0)
			{
				if (i == 0 && arr_check[0] != 1)
				{
					arr_[j - 1] = v;
					arr_check[j - 1] = 1;
					return true;
				}
				else if (i >= (size - i) && arr_check[capacity - 1] != 1 || arr_check[0] == 1)
				{

					for (int k = capacity - 1; k > j; k--)
					{
						arr_[k + 1] = arr_[k];
						arr_check[k + 1] = arr_check[k];
					}

					if (i == 0)
					{
						int temp = arr_[0];
						arr_[1] = temp;
						arr_[0] = v;
						return true;
					}
					else
					{
						arr_[j + 1] = v;
						arr_check[j + 1] = 1;
						return true;
					}
				}
				else if (i < (size - i) && arr_check[0] != 1 || arr_check[capacity - 1] == 1)
				{
					for (int k = 1; k <= j; k++)
					{
						arr_[k - 1] = arr_[k];
						arr_check[k - 1] = arr_check[k];
					}
					arr_[j] = v;
					return true;
				}
			}
		}
	}
	return false;
}

bool FlexArray::erase(int i)
{
	if (i < 0 || i >= size)
	{
		return false;
	}

	for (int j = i; j < size - 1; j++)
	{
		arr_[(capacity - size) / 2 + j] = arr_[(capacity - size) / 2 + j + 1];
	}
	size--;
	return true;
}

void FlexArray::resizeAndRecenter()
{
	int tempIndex = 0;
	int newCapacity = LO_THRESHOLD * size;
	int *newArr = new int[newCapacity];
	int *newCheckArr = new int[newCapacity];
	for (int i = 0; i < newCapacity; i++)
	{
		newCheckArr[i] = 0;
	}

	int start = (newCapacity - size) / 2;
	for (int i = 0; i < capacity; i++)
	{
		if (arr_check[i] == 1)
		{
			newArr[start + tempIndex] = arr_[i];
			newCheckArr[start + tempIndex] = 1;
			tempIndex++;
		}
	}
	arr_ = newArr;
	arr_check = newCheckArr;
	capacity = newCapacity;
}
