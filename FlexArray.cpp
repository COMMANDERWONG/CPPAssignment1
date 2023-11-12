#include "FlexArray.h"
#include <iostream>

using namespace std;

FlexArray::FlexArray()
{
	size_ = 0;
	capacity_ = INITIALCAP; 
	arr_ = new int[capacity_];
	arrCheck_ = new int[capacity_];
}

FlexArray::FlexArray(const int *arr, int size_)
{
	this->size_ = size_;
	capacity_ = LO_THRESHOLD * size_;
	arr_ = new int[capacity_];
	arrCheck_ = new int[capacity_];
	int headroom = (capacity_ - size_) / 2;

	for (int i = 0; i < size_; i++)
	{
		arr_[i + headroom] = arr[i];
		arrCheck_[i + headroom] = 1;
	}
}

FlexArray::~FlexArray()
{
	delete[] arr_;
	delete[] arrCheck_;
	arr_ = nullptr;
	arrCheck_ = nullptr;
}

FlexArray::FlexArray(const FlexArray &other)
{
	capacity_ = other.capacity_;
	size_ = other.size_;
	arr_ = new int[capacity_];
	arrCheck_ = new int[capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		arr_[i] = other.arr_[i];
		arrCheck_[i] = other.arrCheck_[i];
	}
}

FlexArray &FlexArray::operator=(const FlexArray &other)
{
	if (this == &other)
	{
		return *this;
	}

	capacity_ = other.capacity_;
	size_ = other.size_;
	int *newArr = new int[capacity_];
	int *newArrCheck = new int[capacity_];

	for (int i = 0; i < capacity_; i++)
	{
		newArr[i] = other.arr_[i];
		newArrCheck[i] = other.arrCheck_[i];
	}
	arr_ = newArr;
	arrCheck_ = newArrCheck;
	return *this;
}

int FlexArray::getSize() const
{
	return size_;
}

int FlexArray::getCapacity() const
{
	return capacity_;
}

string FlexArray::print() const
{
	string result = "[";
	int temp = size_;

	for (int i = 0; i < capacity_; i++)
	{
		if (arrCheck_[i] == 1)
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

	for (int i = 0; i < capacity_; i++)
	{

		if (arrCheck_[i] == 1)
		{
			result += to_string(arr_[i]);
		}
		else
		{
			result += "X";
		}

		if (i < capacity_ - 1)
		{
			result += ", ";
		}
	}

	result += "]";
	return result;
}

int FlexArray::get(int i) const
{
	if (i >= 0 && i < size_)
	{
		for (int j = 0; j < capacity_; j++)
		{
			if (arrCheck_[j] != 1)
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
	if (i >= 0 && i < size_)
	{
		for (int j = 0; j < capacity_; j++)
		{
			if (arrCheck_[j] != 1)
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

	if (arrCheck_[capacity_ - 1] == 1)
	{
		resizeAndRecenter();
	}

	if (size_ == 0)
	{
		if (capacity_ % 2 == 0)
		{
			arr_[capacity_ / 2 + size_ - 1] = v;
			arrCheck_[capacity_ / 2 + size_ - 1] = 1;
		}
		else
		{
			arr_[capacity_ / 2 + size_] = v;
			arrCheck_[capacity_ / 2 + size_] = 1;
		}
	}
	else
	{
		for (int i = 0; i < capacity_; i++)
		{
			if (arrCheck_[i] != 1)
			{
				continue;
			}
			else
			{
				arr_[i + size_] = v;
				arrCheck_[i + size_] = 1;
				break;
			}
		}
	}
	size_++;
	if (capacity_ > HI_THRESHOLD * size_ && size_ != 0)
	{
		resizeAndRecenter();
	}
}

bool FlexArray::pop_back()
{
	if (size_ <= 0)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < capacity_; i++)
		{
			if (arrCheck_[i] != 1)
			{
				continue;
			}
			else
			{
				if (size_ == 0)
				{
					arr_[i] = 0;
					arrCheck_[i] = 0;
				}
				else
				{
					arr_[i + size_ - 1] = 0;
					arrCheck_[i + size_ - 1] = 0;
				}

				break;
			}
		}
		size_--;
		if (capacity_ > HI_THRESHOLD * size_ && size_ != 0)
		{
			resizeAndRecenter();
		}
		return true;
	}
}

void FlexArray::push_front(int v)
{
	if (arrCheck_[0] == 1)
	{
		resizeAndRecenter();
	}

	if (size_ == 0)
	{
		if (capacity_ % 2 == 0)
		{
			arr_[capacity_ / 2 + size_ - 1] = v;
			arrCheck_[capacity_ / 2 + size_ - 1] = 1;
		}
		else
		{
			arr_[capacity_ / 2 + size_] = v;
			arrCheck_[capacity_ / 2 + size_] = 1;
		}
	}
	else
	{
		for (int i = 0; i < capacity_; i++)
		{
			if (arrCheck_[i] != 1)
			{
				continue;
			}
			else
			{
				arr_[i - 1] = v;
				arrCheck_[i - 1] = 1;
				break;
			}
		}
	}
	size_++;
	if (capacity_ > HI_THRESHOLD * size_ && size_ != 0)
	{
		resizeAndRecenter();
	}
}

bool FlexArray::pop_front()
{
	if (size_ <= 0)
	{
		return false;
	}
	else
	{

		for (int i = 0; i < capacity_; i++)
		{
			if (arrCheck_[i] != 1)
			{
				continue;
			}
			else
			{
				arr_[i] = 0;
				arrCheck_[i] = 0;
				break;
			}
		}
		size_--;
		if (capacity_ > HI_THRESHOLD * size_ && size_ != 0)
		{
			resizeAndRecenter();
		}
		return true;
	}
}

bool FlexArray::insert(int i, int v)
{

	if (i < 0 || i > size_)
	{
		return false;
	}

	if (size_ == 0)
	{
		if (capacity_ % 2 == 0)
		{
			arr_[capacity_ / 2 + size_ - 1] = v;
			arrCheck_[capacity_ / 2 + size_ - 1] = 1;
		}
		else
		{
			arr_[capacity_ / 2 + size_] = v;
			arrCheck_[capacity_ / 2 + size_] = 1;
		}
		size_++;
		return true;
	}

	if ((arrCheck_[capacity_ - 1] == 1 && arrCheck_[0] == 1) || capacity_ > HI_THRESHOLD * size_ && size_ != 0)
	{
		resizeAndRecenter();
	}

	for (int j = 0; j < capacity_; j++)
	{

		if (arrCheck_[j] != 1)
		{
			continue;
		}
		if (i == 0 && arrCheck_[0] != 1)
		{

			arr_[j - 1] = v;
			arrCheck_[j - 1] = 1;
			break;
		}
		else if (i == size_ && arrCheck_[capacity_ - 1] != 1)
		{
			arr_[j + i] = v;
			arrCheck_[j + i] = 1;
			break;
		}
		else if (i >= (size_ - i) && arrCheck_[capacity_ - 1] != 1 || arrCheck_[0] == 1 && arrCheck_[capacity_ - 1] != 1)
		{
			for (int k = capacity_ - 2; k >= j + i; k--)
			{
				arr_[k + 1] = arr_[k];
				arrCheck_[k + 1] = arrCheck_[k];
			}
			arr_[j + i] = v;
			break;
		}
		else if (i < (size_ - i) && arrCheck_[0] != 1 || arrCheck_[capacity_ - 1] == 1 && arrCheck_[0] != 1)
		{
			for (int k = 1; k < j + i; k++)
			{
				arr_[k - 1] = arr_[k];
				arrCheck_[k - 1] = arrCheck_[k];
			}
			arr_[j + i - 1] = v;
			break;
		}
	}
	size_++;
	return true;
}

bool FlexArray::erase(int i)
{
	if (i < 0 || i >= size_)
	{
		return false;
	}

	for (int j = 0; j < capacity_; j++)
	{
		if (arrCheck_[j] != 1)
		{
			continue;
		}
		if (i == 0)
		{
			arr_[j] = 0;
			arrCheck_[j] = 0;
			break;
		}
		else if (i == size_ - 1)
		{
			arr_[j + i] = 0;
			arrCheck_[j + i] = 0;
			break;
		}
		else if (i < (size_ - i) - 1)
		{
			arr_[0] = 0;
			arrCheck_[0] = 0;
			for (int k = (j + i) - 1; k >= 0; k--)
			{
				arr_[k + 1] = arr_[k];
				arrCheck_[k + 1] = arrCheck_[k];
			}
			break;
		}
		else if (i >= (size_ - i) - 1)
		{
			arr_[capacity_ - 1] = 0;
			arrCheck_[capacity_ - 1] = 0;
			for (int k = (j + i) + 1; k < capacity_; k++)
			{
				arr_[k - 1] = arr_[k];
				arrCheck_[k - 1] = arrCheck_[k];
			}
			break;
		}
	}
	size_--;
	if (capacity_ > HI_THRESHOLD * size_ && size_ != 0)
	{
		resizeAndRecenter();
	}
	return true;
}

void FlexArray::resizeAndRecenter()
{
	int tempIndex = 0;
	int newcapacity_ = LO_THRESHOLD * size_;
	int *newArr = new int[newcapacity_];
	int *newCheckArr = new int[newcapacity_];
	int start = (newcapacity_ - size_) / 2;
	int temp = 0;
	for (int i = 0; i < capacity_; i++)
	{
		if (arrCheck_[i] == 1)
		{
			newArr[start + temp] = arr_[i];
			newCheckArr[start + temp] = 1;
			temp++;
		}
	}
	delete[] arr_;
	delete[] arrCheck_;
	arr_ = newArr;
	arrCheck_ = newCheckArr;
	capacity_ = newcapacity_;
}
