#include <iostream>
#include <Windows.h>

#define ARRAY_SIZE 1000

using namespace std;

void ArrayShuffle(int*& _array);
void ArrayPrint(int* _array);

int main()
{
	// 수행시간 측정용 변수
	LARGE_INTEGER Frequency;
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER Endtime;

	QueryPerformanceFrequency(&Frequency);

	// 정렬 해야할 배열
	int* IntergerArray = new int[ARRAY_SIZE];

	// 측정 시작
	QueryPerformanceCounter(&BeginTime);

	// 측정 끝
	QueryPerformanceCounter(&Endtime);

	__int64 elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;

	cout << "수행 시간 : " << duringtime << endl;

	delete[] IntergerArray;
	IntergerArray = nullptr;

	return 0;
}
