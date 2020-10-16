#include <iostream>
#include <Windows.h>
#include <algorithm>

using namespace std;

void ArrayInitShuffle(int*& _array, int _size);
void ArrayPrint(int* _array, int _size);
void Swap(int& _temp, int& _sour);

// 버블 정렬
void BubbleSort(int*& _array, int _size);
// 선택 정렬
void SelectionSort(int*& _array, int _size);
// 삽입 정렬
void Insertion(int*& _array);
// 퀵 정렬
void QuickSort(int*& _array);

int main()
{
	// 수행시간 측정용 변수
	LARGE_INTEGER Frequency;
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER Endtime;

	QueryPerformanceFrequency(&Frequency);

	int Size = 1000;
	// 정렬 해야할 배열
	int* IntergerArray = new int[Size];

	// 배열셔플 및 출력
	ArrayInitShuffle(IntergerArray, Size);	
	ArrayPrint(IntergerArray, Size);

	// 측정 시작
	QueryPerformanceCounter(&BeginTime);

	//BubbleSort(IntergerArray, Size);
	SelectionSort(IntergerArray, Size);

	// 측정 끝
	QueryPerformanceCounter(&Endtime);

	ArrayPrint(IntergerArray, Size);

	__int64 elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;

	cout << "수행 시간 : " << duringtime << endl;

	delete[] IntergerArray;
	IntergerArray = nullptr;

	return 0;
}

void ArrayInitShuffle(int*& _array, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		_array[i] = i;
	}

	for (int i = 0; i < _size * 2; i++)
	{
		int firstRandomIndex = rand() % _size;
		int SecondRandomIndex = rand() % _size;

		Swap(_array[firstRandomIndex], _array[SecondRandomIndex]);
	}
}

void ArrayPrint(int* _array, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		cout << "[" << i << "] : " << _array[i] << endl;
	}

	cout << endl;
}

void Swap(int& _temp, int& _sour)
{
	int tempNumber = _temp;
	_temp = _sour;
	_sour = tempNumber;
}

void BubbleSort(int*& _array, int _size)
{
	for (int i = 0; i < _size - 1; i++)
	{
		for (int j = i + 1; j < _size; j++)
		{
			if (_array[i] > _array[j])
			{
				Swap(_array[i], _array[j]);
			}
		}
	}
}

void SelectionSort(int*& _array, int _size)
{
	int minData = 0;
	int findIndex = 0;

	for (int i = 0; i < _size - 1; i++)
	{
		minData = _array[i];

		int nextIndex = i + 1;

		while (nextIndex < _size)
		{
			if (minData > _array[nextIndex])
			{
				minData = _array[nextIndex];
				findIndex = nextIndex;
			}

			nextIndex++;
		}
		
		if (minData != _array[i])
		{
			Swap(_array[i], _array[findIndex]);
			findIndex = 0;
		}

	}
}
