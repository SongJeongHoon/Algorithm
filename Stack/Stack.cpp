#include <iostream>
#include <algorithm>

#define MAGICNUM -1

using namespace std;

int* MyStack = nullptr;
int Size = 0;
int InputData = 0;
int InputValue = 0;
int CurrentSelectIndex = 0;

void Push(int*& _array, int& _curIndex, int& _size, int _value);
void Pop(int*& _array, int& _curIndex);
void ShowStack(int* _array, int _size);
void Print_fuc(int _data);

int main()
{
	cout << "Size of stack_";
	cin >> Size;
	cout << "\n";

	MyStack = new int[Size];

	for (int i = 0; i < Size; i++) {
		MyStack[i] = MAGICNUM;
	}

	while (true) {
		cout << "\n(int)[STACK]\n\t1.PUSH 2.POP\n" << "\tChoice_";
		cin >> InputData;
		cout << "\n";

		switch (InputData)
		{
		case 1:
			cout << "Enter an integer value for the stack_";
			cin >> InputValue;
			cout << "\n";
			Push(MyStack, CurrentSelectIndex, Size, InputValue);
			break;

		case 2:
			Pop(MyStack, CurrentSelectIndex);
			break;

		default:
			cout << "YOU CHOSE THE WRONG NUMBER!!\n";
			break;
		}
	}

	delete[] MyStack;

	return 0;
}

void Push(int*& _array, int& _curIndex, int& _size, int _value)
{
	// 만약 스택의 크기만큼 꽉 차있다면
	if (_curIndex >= _size) {
		// 스택의 크기는 하나 늘어난다
		int newSize = _size + 1;
		// 새로운 스택의 크기만큼 임시 스택생성
		int* tempStack = new int[newSize];

		// 임시 스택에 기존스택 데이터 저장
		for (int i = 0; i < newSize; i++) {
			if (i == newSize - 1)
				tempStack[i] = MAGICNUM;
			else
				tempStack[i] = _array[i];
		}

		// 스택 사용 해제
		delete[] _array;

		// 새로운 크기만큼 스택 재할당
		_array = new int[newSize];
		// 기존 스택에 임시 스택 삽입
		_array = tempStack;
		// 최종 스택의 크기 초기화
		_size = newSize;
	}

	// 입력받은 값을 스택[현재 선택된 인덱스 값] 에 넣어주기
	_array[_curIndex] = _value;
	// 다음 입력받은 값이 들어가게될 인덱스 값 설정
	_curIndex++;

	// 스택 출력
	ShowStack(_array, _size);
}

void Pop(int*& _array, int& _curIndex)
{
	
}

void ShowStack(int* _array, int _size)
{
	cout << "(int)STACK\n";

	for_each(_array, &_array[_size], Print_fuc);

	cout << "\n";
}

void Print_fuc(int _data)
{
	cout << "[" << _data << "]";
}
