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
	Node* prevSearchNode = nullptr;
	Node* SearchNode = _rootNode;

	while (SearchNode->Data != _data)
	{
		prevSearchNode = SearchNode;

		if (SearchNode->Data < _data)
		{
			SearchNode = SearchNode->LeftChild;
		}
		else if (SearchNode->Data > _data)
		{
			SearchNode = SearchNode->RightChild;
		}
	}

	// 왼쪽자식은 있고 오른쪽 자식은 없다면
	if (SearchNode->LeftChild && !SearchNode->RightChild)
	{	
		Node* prevNode = 
	}
}

void Inorder(Node* _rootNode)
{
	if (!_rootNode) return;

	Inorder(_rootNode->LeftChild);
	cout << _rootNode->Data << " - ";
	Inorder(_rootNode->RightChild);
}