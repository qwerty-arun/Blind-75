#include <iostream>
#include <numeric>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
	int data;
	Node* left;
	Node* right;

	Node(int val){
		data = val;
		left = right = nullptr;
	}
};

static int idx = -1;
Node* buildTree(std::vector<int> preorder){
	idx++;

	if(preorder[idx] == -1)
		return nullptr;

	Node* root = new Node(preorder[idx]);
	root->left = buildTree(preorder); //LEFT
	root->right= buildTree(preorder); //RIGHT

	return root;
}

void inOrder(Node* root){
	if(root==nullptr)
		return;
	else{
		inOrder(root->left);
		cout<<root->data<<" ";
		inOrder(root->right);
	}
}

void levelOrder(Node* root){
	queue<Node*> q;
	q.push(root);
	q.push(nullptr);

	while(q.size()>0){
		Node* curr = q.front();
		q.pop();

		if(curr==nullptr) //Either full traversal is over or a level is done
		{
			if(!q.empty()){
				cout<<endl;
				q.push(nullptr);
				continue;
			}
			else
				break;
		}

		cout<<curr->data<<" ";
		if(curr->left!=nullptr)
			q.push(curr->left);

		if(curr->right!=nullptr)
			q.push(curr->right);
	}
}

void postOrder(Node* root)
{
	if(root==nullptr)
		return;
	else
	{
		postOrder(root->left);
		postOrder(root->right);
		cout<<root->data<<" ";
	}
}

void preOrder(Node* root)
{
	if(root==nullptr)
        return;
	else
	{
		cout<<root->data<<" ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

int main()
{
	std::vector<int> preorder = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};
	Node* root = buildTree(preorder);

    cout << "InOrder Traversal: " << endl;
	inOrder(root);
    cout << endl;

    cout << "LevelOrder Traversal: " << endl;
	levelOrder(root);
    cout << endl;

    cout << "PreOrder Traversal: " << endl;
	preOrder(root);
    cout << endl;

    cout << "PostOrder Traversal: " << endl;
	postOrder(root);
    cout << endl;

	return 0;
}