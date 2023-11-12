#include "FlexArray.h"
#include <iostream>
#include <algorithm>

using namespace std;

FlexArray::FlexArray()
{
	size = 0;
	capacity = INITIALCAP; // Initial capacity
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
		arr_[i + headroom] = arr[i];
		arr_check[i + headroom] = 1;
	}
}

FlexArray::~FlexArray()
{
	delete[] arr_;
	delete[] arr_check;
	arr_ = nullptr;
	arr_check = nullptr;
}

FlexArray::FlexArray(const FlexArray &other)
{
	capacity = other.getCapacity();
	size = other.getSize();
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

	// Allocate new memory
	int *newArr = new int[other.getCapacity()];
	int *newCheckArr = new int[other.getCapacity()];

	// Copy data
	for (int i = 0; i < other.capacity; i++)
	{
		newArr[i] = other.arr_[i];
		newCheckArr[i] = other.arr_check[i];
	}

	// Deallocate old memory
	delete[] arr_;
	delete[] arr_check;

	// Update pointers and sizes
	arr_ = newArr;
	arr_check = newCheckArr;
	capacity = other.capacity;
	size = other.size;
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
	string result;
	result += "[";

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
	if (i >= 0 && i < size)
	{
		for (int j = 0; j < capacity; j++)
		{
			if (arr_check[j] != 1)
			{
				continue;
			}
			return arr_[j + i];
		}
	}
	return -1;
}

bool FlexArray::set(int i, int v)
{
	if (i >= 0 && i < size)
	{
		for (int j = 0; j < capacity; j++)
		{
			if (arr_check[j] != 1)
			{
				continue;
			}
			arr_[j + i] = v;
			return true;
		}
	}
	return false;
}

void FlexArray::push_back(int v)
{

	if (arr_check[capacity - 1] == 1 || capacity > HI_THRESHOLD * size && size != 0)
	{
		resizeAndRecenter();
	}
	if (size == 0)
	{
		if (capacity % 2 == 0)
		{
			arr_[capacity / 2 + size - 1] = v;
			arr_check[capacity / 2 + size - 1] = 1;
		}
		else
		{
			arr_[capacity / 2 + size] = v;
			arr_check[capacity / 2 + size] = 1;
		}
		
	}
	else
	{
		for (int i = 0; i < capacity; i++)
		{
			if (arr_check[i] != 1)
			{
				continue;
			}
			else
			{
				arr_[i + size] = v;
				arr_check[i + size] = 1;
				break;
			}
		}
	}
	size++;
}

bool FlexArray::pop_back()
{
	if (size <= 0)
	{
		return false;
	}
	else
	{

		for (int i = 0; i < capacity; i++)
		{
			if (arr_check[i] != 1)
			{
				continue;
			}
			else
			{
				arr_[i + size] = 0;
				arr_check[i + size] = 0;
				break;
			}
		}
		size--;
		if (capacity > HI_THRESHOLD * size && size != 0)
		{
			resizeAndRecenter();
		}
		return true;
	}
}

void FlexArray::push_front(int v)
{
	if (arr_check[0] == 1 || capacity > HI_THRESHOLD * size && size != 0)
	{
		resizeAndRecenter();
	}
	if (size == 0)
	{
		if (capacity % 2 == 0)
		{
			arr_[capacity / 2 + size - 1] = v;
			arr_check[capacity / 2 + size - 1] = 1;
		}
		else
		{
			arr_[capacity / 2 + size] = v;
			arr_check[capacity / 2 + size] = 1;
		}
	}
	else
	{
		for (int i = 0; i < capacity; i++)
		{
			if (arr_check[i] != 1)
			{
				continue;
			}
			else
			{
				arr_[i - 1] = v;
				arr_check[i - 1] = 1;
				break;
			}
		}
	}
	size++;
}

bool FlexArray::pop_front()
{
	if (size <= 0)
	{
		return false;
	}
	else
	{

		for (int i = 0; i < capacity; i++)
		{
			if (arr_check[i] != 1)
			{
				continue;
			}
			else
			{
				arr_[i] = 0;
				arr_check[i] = 0;
				break;
			}
		}
		size--;

		if (capacity > HI_THRESHOLD * size && size != 0)
		{
			resizeAndRecenter();
		}
		return true;
	}
}

bool FlexArray::insert(int i, int v)
{

	if (i < 0 || i > size)
	{
		return false;
	}

	if (size == 0)
	{
		if (capacity % 2 == 0)
		{
			arr_[capacity / 2 + size - 1] = v;
			arr_check[capacity / 2 + size - 1] = 1;
		}
		else
		{
			arr_[capacity / 2 + size] = v;
			arr_check[capacity / 2 + size] = 1;
		}
		size++;
		return true;
	}

	if ((arr_check[capacity - 1] == 1 && arr_check[0] == 1) || capacity > HI_THRESHOLD * size && size != 0)
	{
		resizeAndRecenter();
	}

	for (int j = 0; j < capacity; j++)
	{

		if (arr_check[j] != 1)
		{
			continue;
		}
		if (i == 0 && arr_check[0] != 1)
		{

			arr_[j - 1] = v;
			arr_check[j - 1] = 1;
			size++;
			break;
		}
		else if (i == size && arr_check[capacity - 1] != 1)
		{
			arr_[j + i] = v;
			arr_check[j + i] = 1;
			size++;
			break;
		}
		else if (i >= (size - i) && arr_check[capacity - 1] != 1 || arr_check[0] == 1 && arr_check[capacity - 1] != 1)
		{
			for (int k = capacity - 2; k >= j + i; k--)
			{
				arr_[k + 1] = arr_[k];
				arr_check[k + 1] = arr_check[k];
			}
			size++;
			arr_[j + i] = v;
			break;
		}
		else if (i < (size - i) && arr_check[0] != 1 || arr_check[capacity - 1] == 1 && arr_check[0] != 1)
		{
			for (int k = 1; k <= j + i; k++)
			{
				arr_[k - 1] = arr_[k];
				arr_check[k - 1] = arr_check[k];
			}
			size++;
			arr_[j + i - 1] = v;
			break;
		}
	}
	return true;
}

bool FlexArray::erase(int i)
{
	if (i < 0 || i >= size)
	{
		return false;
	}

	for (int j = 0; j < capacity; j++)
	{
		if (arr_check[j] != 1)
		{
			continue;
		}
		if (i == 0)
		{
			arr_check[j] = 0;
			break;
		}
		else if (i == size - 1)
		{
			arr_check[j + i] = 0;
			break;
		}
		else if (i < (size - i) - 1)
		{
			for (int k = (j + i) - 1; k >= 0; k--)
			{
				arr_[k + 1] = arr_[k];
				arr_check[k + 1] = arr_check[k];
			}
			break;
		}
		else if (i >= (size - i) - 1)
		{
			for (int k = (j + i) + 1; k <= capacity; k++)
			{
				arr_[k - 1] = arr_[k];
				arr_check[k - 1] = arr_check[k];
			}
			break;
		}
	}
	size--;
	if (capacity > HI_THRESHOLD * size && size != 0)
	{
		resizeAndRecenter();
	}
	return true;
}

void FlexArray::resizeAndRecenter()
{
	int tempIndex = 0;
	int newCapacity = LO_THRESHOLD * size;
	int *newArr = new int[newCapacity];
	int *newCheckArr = new int[newCapacity];
	int start = (newCapacity - size) / 2;
	int temp = 0;
	for (int i = 0; i < capacity; i++)
	{
		if (arr_check[i] == 1)
		{
			newArr[start + temp] = arr_[i];
			newCheckArr[start + temp] = 1;
			temp++;
		}
	}
	arr_ = newArr;
	arr_check = newCheckArr;
	capacity = newCapacity;
}
