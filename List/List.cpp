#include <iostream>
#include <algorithm>

using namespace std;

struct Node 
{
	int Data;			// 값
	Node* pPrevNode;	// 이전 노드
	Node* pNextNode;	// 다음 노드
};

// 순서대로 리스트 추가
void AddNode(Node*& _headNode, int _data);
// 원하는 위치에 노드 추가
void AddNode(Node* _headNode, int _index, int _data);
// 모든 노드삭제
void DeleteNodeAll(Node* _headNode);
// 원하는 위치의 노드삭제
void DeleteNode(Node*& _headNode, int _index);
// 순서대로 노드들 출력
void PrintNodes(Node* _headNode);
// 뒤에서부터 노드들 출력
void PrintNodesRevert(Node* _headNode);

int main()
{
	Node* HeadNode = new Node;
	HeadNode->Data = 10;
	HeadNode->pPrevNode = nullptr;
	HeadNode->pNextNode = nullptr;

	AddNode(HeadNode, 1);
	AddNode(HeadNode, 4);
	AddNode(HeadNode, 7);

	PrintNodes(HeadNode);

	DeleteNode(HeadNode, 1);
	//DeleteNode(HeadNode, 0);

	PrintNodes(HeadNode);
}

void AddNode(Node*& _headNode, int _data)
{
	// 리스트를 찾기위한 순회용 노드는 머리 노드부터 시작한다
	Node* pSearchNode = _headNode;	

	// 첫 번째 노드의 다음노드가 비어있지 않을때 까지 반복
	while (pSearchNode->pNextNode != nullptr)
	{
		// 첫 번째 노드가 비어있지 않다면 순회용 노드는 첫 번째 노드의 다음노드가 된다
		pSearchNode = pSearchNode->pNextNode;
	}	

	// 새로 추가할 노드 할당
	Node* newNode = new Node;
	// 맨 마지막 노드의 다음 노드는 새로 들어갈 노드가 들어가므로, 순회용 노드의 다음 노드는 새로운 노드가 된다
	pSearchNode->pNextNode = newNode;

	// 새로운 노드의 값 대입
	newNode->Data = _data;
	// 새로운 노드의 이전 노드는 순회용 노드
	newNode->pPrevNode = pSearchNode;
	// 새로운 노드의 다음 노드는 비어있다
	newNode->pNextNode = nullptr;	
}

void AddNode(Node* _headNode, int _index, int _data)
{
	
}

void DeleteNodeAll(Node* _headNode)
{

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
		int countIndex = 0;
		// 삭제될 노드의 인덱스 값이 입력한 인덱스 값이 아닐때 까지 반복
		while (countIndex != _index)
		{
			// 찾고자 하는 노드의 이전 노드는 순회 노드가 되고
			pSearchPrevNode = pSearchNode;
			// 찾고자 하는 노드의 다음 노드는 순회용 다음노드의 다음노드가 된다
			pSearchNextNode = pSearchNextNode->pNextNode;
			// 찾아낸 노드는 찾고자 하는 노드의 다음노드가 된다
			pSearchNode = pSearchNode->pNextNode;
			// 반복문을 순회하기 위해 값 증가
			countIndex++;
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
	// 순회용 노드는 머리 노드부터 시작한다
	Node* pSearchNode = _headNode;
	// 노드들의 인덱스 값을 보여주기 위한 변수
	int count = 0;

	// 현재 노드가 비어있지 않을 때까지 순회
	while (pSearchNode != nullptr)
	{
		// 현재 노드의 인덱스와 값 출력
		printf("[%d] 번째 노드 의 값 : %d\n", count++, pSearchNode->Data);
		// 순회하고자 하는 노드 갱신 (현재노드는 현재노드의 다음노드가 되어야한다)
		pSearchNode = pSearchNode->pNextNode;
	}

	puts("=============================================================");
}

void PrintNodesRevert(Node* _headNode)
{
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

	// 현재 노드의 다음노드는 비어있으므로, 위 반복문을 다돌면 현재 노드는 맨 마지막 노드가 된다
	while (pSearchNode->pPrevNode != )
}
