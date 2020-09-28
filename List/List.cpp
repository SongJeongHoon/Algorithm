/*
	list
		- 배열과 다르게 삽입 삭제가 용이한 형태이다.
		- 원소는 다음 원소를 가리키는 포인터를 가지고있다. 이를 링크드리스트(Linked List)라고 부르더라.
		- 원소가 이전 원소를 가리키는 포인터도 가지고있다면 이는 더블 링크드 리스트(Double Linked List)가 된다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

enum MENU
{
	Insert = 1, Pull,
	Auto_Insert = 1, Select_Index_Insert,
	Delete_All = 1, Select_Index_Delete
};

struct Node				// 리스트의 원소가되는 노드 구조체
{
	int Data;			// 값
	Node* pPrevNode;	// 이전 노드
	Node* pNextNode;	// 다음 노드
};

// 순서대로 노드 추가
void AddNode(Node*& _headNode, int _data);
// 원하는 위치에 노드 추가
void AddNode(Node*& _headNode, int _index, int _data);
// 모든 노드삭제
void DeleteNodeAll(Node*& _headNode);
// 원하는 위치의 노드삭제
void DeleteNode(Node*& _headNode, int _index);
// 순서대로 노드들 출력
void PrintNodes(Node* _headNode);
// 뒤에서부터 노드들 출력
void PrintNodesRevert(Node* _headNode);

int main()
{
	Node* HeadNode = nullptr;

	int inputData = 0;
	int elementValue = 0;
	int indexValue = 0;

	while (true)
	{
		cout << "(int)[Double Linked List]\n";
		cout << "(1)Insert (2)Pull\n";
		cout << "->";
		cin >> inputData;

		switch (inputData)
		{
		case Insert:
			cout << "(1)Auto Insert (2)Select Index Insert\n";
			cout << "->";
			cin >> inputData;

			cout << "Input Value ->";
			cin >> elementValue;

			if (inputData == Auto_Insert)
			{
				AddNode(HeadNode, elementValue);
			}
			else if (inputData == Select_Index_Insert)
			{
				cout << "Input Index ->";
				cin >> indexValue;

				AddNode(HeadNode, indexValue, elementValue);
			}
			break;

		case Pull:
			cout << "(1)Delete All (2)Select Index Delete\n";
			cout << "->";
			cin >> inputData;

			if (inputData == Delete_All)
			{
				DeleteNodeAll(HeadNode);
			}
			else if (inputData == Select_Index_Delete)
			{
				cout << "Input Index ->";
				cin >> indexValue;

				DeleteNode(HeadNode, indexValue);
			}
			break;

		default:
			break;
		}

		PrintNodes(HeadNode);
		//PrintNodesRevert(HeadNode);
	}	

	DeleteNodeAll(HeadNode);
}

void AddNode(Node*& _headNode, int _data)
{
	// 리스트를 찾기위한 순회용 노드는 머리 노드부터 시작한다
	Node* pSearchNode = _headNode;
	// 새로운 노드를 할당
	Node* newNode = new Node;

	// 순회노드가 비어있다면 
	if (pSearchNode == nullptr)
	{
		// 입력받은 데이터 저장
		newNode->Data = _data;
		// 최초 부모노드의 이전 노드는 비어있고
		newNode->pPrevNode = nullptr;
		// 마찬가지로 다음 노드 또한 비어있어야한다
		newNode->pNextNode = nullptr;
		// 새로운 노드를 머리노드로 지정
		_headNode = newNode;
		// 함수 탈출
		return;
	}

	// 첫 번째 노드의 다음노드가 비어있지 않을때 까지 반복
	while (pSearchNode->pNextNode != nullptr)
	{
		// 첫 번째 노드가 비어있지 않다면 순회용 노드는 첫 번째 노드의 다음노드가 된다
		pSearchNode = pSearchNode->pNextNode;
	}

	// 맨 마지막 노드의 다음 노드는 새로 들어갈 노드가 들어가므로, 순회용 노드의 다음 노드는 새로운 노드가 된다
	pSearchNode->pNextNode = newNode;
	// 새로운 노드의 값 대입
	newNode->Data = _data;
	// 새로운 노드의 이전 노드는 순회용 노드
	newNode->pPrevNode = pSearchNode;
	// 새로운 노드의 다음 노드는 비어있다
	newNode->pNextNode = nullptr;
}

void AddNode(Node*& _headNode, int _index, int _data)
{
	// 리스트를 찾기위한 순회용 노드는 머리 노드부터 시작한다
	Node* pSearchNode = _headNode;
	// 이전 노드는 머리노드의 이전 노드로 초기화
	Node* pSearchPrevNode = _headNode->pPrevNode;
	// 다음 노드는 머리노드의 다음 노드로 초기화
	Node* pSearchNextNode = _headNode->pNextNode;
	// 새로운 노드를 할당
	Node* newNode = new Node;

	// 맨 첫 번째에 추가하겠다고한다면
	if (_index == 0)
	{
		// 새로운 노드의 값을 입력한 값으로 초기화
		newNode->Data = _data;
		// 새로운 노드의 이전 노드는 비어있는채로
		newNode->pPrevNode = nullptr;
		// 새로운 노드의 다음노드는 머리노드
		newNode->pNextNode = _headNode;
		// 과거 머리노드의 이전노드는 새로운 노드가 된다
		_headNode->pPrevNode = newNode;
		// 최종적으로 머리노드는 새로운 노드로 바꿔주기
		_headNode = newNode;
	}
	else
	{
		// 사용자가 입력한 원하는 위치의 인덱스 값을 찾기위한 변수 (추가될 노드의 인덱스)
		int indexCount = 0;
		// 추가될 노드의 인덱스 값이 입력한 인덱스 값이 아닐때 까지 반복
		while (indexCount != _index)
		{
			// 찾고자 하는 노드의 이전 노드는 순회 노드가 되고
			pSearchPrevNode = pSearchNode;
			// 찾고자 하는 노드의 다음 노드는 순회용 다음노드의 다음노드가 된다
			pSearchNextNode = pSearchNextNode->pNextNode;
			// 찾아낸 노드는 찾고자 하는 노드의 다음노드가 된다
			pSearchNode = pSearchNode->pNextNode;
			// 반복문을 순회하기 위해 값 증가
			indexCount++;
		}

		// 찾아낸 노드가 비어있다면 (리스트의 크기보다 더 뒤에 값을 입력했다면)
		if (pSearchNode == nullptr)
		{
			puts("Index out of range!!");
			return;
		}

		// 새로운 노드의 값을 입력한 값으로 초기화
		newNode->Data = _data;
		// 새로운 노드의 이전노드는 사용자가 입력하 위치의 노드(찾아낸 노드)의 이전노드
		newNode->pPrevNode = pSearchPrevNode;
		// 새로운 노드의 다음 노드는 찾아낸 노드가 된다
		newNode->pNextNode = pSearchNode;
		// 찾아낸 노드의 이전노드의 다음노드는 새로운 노드
		pSearchPrevNode->pNextNode = newNode;
		// 찾아낸 노드의 이전노드는 새로운 도드가 된다
		pSearchNode->pPrevNode = newNode;
	}
}

void DeleteNodeAll(Node*& _headNode)
{
	if (_headNode == nullptr)
	{
		puts("List is empty!!");
		return;
	}

	// 머리노드만 삭제하면 뒤에 연결된 노드들을 잃게된다. 즉, 메모리 누수가 일어난다.
	// 탐색할 노드(반복문을 돌며 삭제할 노드)는 머리노드의 다음노드
	Node* pTargetNode = _headNode->pNextNode;

	// 머리노드는 맨 마지막에 삭제하며 머리노드 다음을 삭제, 삭제, 삭제 ... 최종 머리노드만 남을 때 까지 반복한다
	while (pTargetNode != nullptr) 
	{
		// 머리노드의 다음 노드는, 삭제할 노드의 다음노드로 연결
		_headNode->pNextNode = pTargetNode->pNextNode;

		// 타겟 노드를 해제 (머리노드의 바로앞 노드를 해제)
		delete pTargetNode;
		
		// 타겟노드 비게 한다
		pTargetNode = nullptr;

		// 그다음 타겟 노드는 머리노드의 다음 노드로 갱신
		pTargetNode = _headNode->pNextNode;
	}

	// 반복문을 빠져나오면 머리노드밖에 남지않는다
	// 최종적으로 머리노드 해제
	delete _headNode;

	// 머리노드 빈공간으로
	_headNode = nullptr;	
}

void DeleteNode(Node*& _headNode, int _index)
{
	// 리스트를 찾기위한 순회용 노드는 머리 노드부터 시작한다
	Node* pSearchNode = _headNode;
	// 이전 노드는 머리노드의 이전 노드로 초기화
	Node* pSearchPrevNode = _headNode->pPrevNode;
	// 다음 노드는 머리노드의 다음 노드로 초기화
	Node* pSearchNextNode = _headNode->pNextNode;

	// 만약 머리노드를 삭제한다면
	if (_index == 0)
	{
		// 머리노드는 머리노드의 다음노드가 되고
		_headNode = pSearchNextNode;
		// 머리노드의 이전 노드는 비어있게된다
		_headNode->pPrevNode = nullptr;
		// 과거의 머리노드를 해제
		delete pSearchPrevNode;
		// 과거의 머리노드를 비어있는채로 두기
		pSearchNextNode = nullptr;
	}
	else
	{
		// 사용자가 입력한 원하는 위치의 인덱스 값을 찾기위한 변수 (삭제될 노드의 인덱스)
		int indexCount = 0;
		// 삭제될 노드의 인덱스 값이 입력한 인덱스 값이 아닐때 까지 반복
		while (indexCount != _index)
		{
			// 찾고자 하는 노드의 이전 노드는 순회 노드가 되고
			pSearchPrevNode = pSearchNode;
			// 찾고자 하는 노드의 다음 노드는 순회용 다음노드의 다음노드가 된다
			pSearchNextNode = pSearchNextNode->pNextNode;
			// 찾아낸 노드는 찾고자 하는 노드의 다음노드가 된다
			pSearchNode = pSearchNode->pNextNode;
			// 반복문을 순회하기 위해 값 증가
			indexCount++;
		}

		// 찾아낸 노드의 다음노드(삭제하려는 노드의 다음노드)가 빈 노드가 아니라면
		if (pSearchNextNode != nullptr)
		{
			// 찾아낸 노드의 이전 노드의 다음 노드는, 찾아낸 노드의 다음노드로 연결
			pSearchPrevNode->pNextNode = pSearchNextNode;
		}
		// 찾아낸 노드의 다음노드(삭제하려는 노드의 다음노드)가 빈 노드라면
		else
		{
			// 찾아낸 노드의 이전 노드의 다음 노드는 빈 공간을 가리키게한다
			pSearchPrevNode->pNextNode = nullptr;
		}

		// 찾아낸 노드의 다음 노드가 빈 노드가 아니라면
		if (pSearchNextNode != nullptr)
		{
			// 찾아낸 노드의 다음 노드의 이전 노드는, 찾아낸 노드의 이전 노드가 된다
			pSearchNextNode->pPrevNode = pSearchPrevNode;
		}

		// 찾아낸 노드 해제
		delete pSearchNode;
		// 찾아낸 노드 비어있게
		pSearchNode = nullptr;
	}
}

void PrintNodes(Node* _headNode)
{
	if (_headNode == nullptr)
	{
		puts("List is empty!!");
		return;
	}

	// 순회용 노드는 머리 노드부터 시작한다
	Node* pSearchNode = _headNode;
	// 노드들의 인덱스 값을 보여주기 위한 변수
	int indexCount = 0;

	// 현재 노드가 비어있지 않을 때까지 순회
	while (pSearchNode != nullptr)
	{
		// 현재 노드의 인덱스와 값 출력
		printf("Node[%d]:%d-> ", indexCount++, pSearchNode->Data);
		// 순회하고자 하는 노드 갱신 (현재노드는 현재노드의 다음노드가 되어야한다)
		pSearchNode = pSearchNode->pNextNode;
	}
	puts("NULL");
	puts("=============================================================");
}

void PrintNodesRevert(Node* _headNode)
{
	if (_headNode == nullptr)
	{
		puts("List is empty!!");
		return;
	}

	// 맨뒤의 노드를 찾기위한 순회용 노드
	Node* pSearchNode = _headNode;
	// 노드들의 인덱스 값을 보여주기 위한 변수
	int indexCount = 0;

	// 현재 노드의 다음노드가가 비어있지 않을 때까지 순회
	while (pSearchNode->pNextNode != nullptr)
	{
		// 순회하고자 하는 노드 갱신 (현재노드는 현재노드의 다음노드가 되어야한다)
		pSearchNode = pSearchNode->pNextNode;
		// 노드들의 인덱스 값 갱신
		indexCount++;
	}

	// 찾아낸 노드의 다음노드는 비어있으므로, 위 반복문을 다돌면 현재 노드는 맨 마지막 노드가 된다
	// 현재 노드가 비어있지 않을때 까지 순회
	while (pSearchNode != nullptr)
	{
		// 현재 노드의 인덱스와 값 출력
		printf("[%d] 번째 노드의 값 : %d\n", indexCount--, pSearchNode->Data);
		// 순회되는 노드는 다시 이전 노드로 바꿔줘야한다
		pSearchNode = pSearchNode->pPrevNode;
	}

	puts("=============================================================");
}