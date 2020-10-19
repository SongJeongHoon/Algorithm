#include <iostream>

using namespace std;

// Binary Search Tree
struct Node
{
	int Data;
	Node* LeftChild;
	Node* RightChild;

	Node(int _data)
	{
		this->Data = _data;
		this->LeftChild = nullptr;
		this->RightChild = nullptr;
	}
	~Node() { }
};

void Push(int _data, Node*& _rootNode);
void Pop(int _data, Node*& _rootNode);
// 중위 순회 (leftChild -> perant -> rightChild)
void Inorder(Node* _rootNode);

int main()
{
	Node* RootNode = nullptr;

	Push(20, RootNode);
	Push(15, RootNode);
	Push(25, RootNode);
	Push(4, RootNode);
	Push(17, RootNode);
	Push(3, RootNode);
	Push(10, RootNode);
	Push(16, RootNode);
	Push(19, RootNode);
	Push(23, RootNode);
	Push(30, RootNode);

	Inorder(RootNode);
}

void Push(int _data, Node*& _rootNode)
{
	// 왼쪽인지 오른쪽인지 모르겠지만 매개변수로 들어온 노드가 비어있다면
	if (!_rootNode)
	{
		// 새로운 노드생성
		Node* newNode = new Node(_data);
		// 이 노드를 새로운 노드로 지정
		_rootNode = newNode;
		// 함수를 빠져나간다, 재귀 호출을 빠져나간다!
		return;
	}

	// 집어넣으려는 값이 현재노드 보다 작다면
	if (_data < _rootNode->Data)
	{
		// 집어넣는 값은 그대로, 현재노드의 왼쪽 자식으로 이동
		Push(_data, _rootNode->LeftChild);
	}
	// 집어넣으려는 값이 현재노드 보다 크다면
	else if (_data > _rootNode->Data)
	{
		// 집어넣는 값은 그대로, 현재노드의 오른쪽 자식으로 이동
		Push(_data, _rootNode->RightChild);
	}
}

void Pop(int _data, Node*& _rootNode)
{
	// 삭제할 노드 찾아내기
	Node* prevSearchNode = nullptr;
	Node* searchNode = _rootNode;

	while (_data != searchNode->Data)
	{
		prevSearchNode = searchNode;

		if (_data < searchNode->Data)
		{
			searchNode = searchNode->LeftChild;
		}
		else if (_data > searchNode->Data)
		{
			searchNode = searchNode->RightChild;
		}
	}

	// 삭제할 노드의 자식이 왼쪽밖에 없다면
	if (searchNode->LeftChild && !searchNode->RightChild)
	{
		// 삭제할 노드의 자식중 제일큰 값을 가진 노드를 찾아야한다. 그 노드는 제일 오른쪽 잎 노드가 될것이다.		
		Node* prevReafNode = nullptr;
		Node* reafNode = searchNode->LeftChild;

		if (reafNode->RightChild)
		{
			while (reafNode->RightChild)
			{
				prevReafNode = reafNode;
				reafNode = reafNode->RightChild;
			}

			prevReafNode->RightChild = nullptr;

			reafNode->LeftChild = searchNode->LeftChild;
		}

		prevSearchNode->LeftChild = reafNode;

		delete searchNode;
		searchNode = nullptr;
	}
}

void Inorder(Node* _rootNode)
{
	if (!_rootNode) return;

	Inorder(_rootNode->LeftChild);
	cout << _rootNode->Data << " - ";
	Inorder(_rootNode->RightChild);
}