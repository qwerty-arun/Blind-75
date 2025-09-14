#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
class Node
{
public:
	int data;
	Node* left;
	Node* right;

	Node(int val)
	{
		data = val;
		left = right = nullptr;
	}
};

static int idx = -1;
Node* buildTree(std::vector<int> preorder)
{
	idx++;

	if(preorder[idx] == -1)
		return nullptr;

	Node* root = new Node(preorder[idx]);
	root->left = buildTree(preorder); //LEFT
	root->right= buildTree(preorder); //RIGHT

	return root;
}

int height(Node* root)
{
	int leftHt, rightHt;
	if(root==nullptr)
		return 0;

	leftHt = height(root->left);
	rightHt = height(root->right);

	return max(leftHt, rightHt)+1;
}

int diameter(Node* root) //O(n^2)
{
	if(root == nullptr)
		return 0;
	int leftDiam = diameter(root->left);
	int rightDiam = diameter(root->right);
	int currDiam = height(root->left) + height(root->right);
	return max(leftDiam,max(rightDiam,currDiam));
}
//TC: O(nlogn)
void topView(Node* root) //we need a queue and a map(horizontal distance, node), the map should be ordered map, not unordered, becoz we want the answers to be printed that way
{
	queue<pair<Node*, int>> q;
	map<int, int> m; //HD, node val
	q.push({root,0});

	while(q.size()>0)
	{
		Node* curr = q.front().first;
		int currHD = q.front().second;
		q.pop();

		if(m.find(currHD) ==m.end())
		{
			m[currHD] = curr->data;
		}

		if(curr->left!=nullptr)
			q.push({curr->left, currHD-1});

		if(curr->right!=nullptr)
			q.push({curr->right, currHD+1});
	}
	for(auto it:m)
		cout<<it.second<< " ";
	cout<<endl;
	
}
int main()
{
	std::vector<int> preorder = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};
	Node* root = buildTree(preorder);
	std::cout << "Height: " << height(root) << std::endl;
	std::cout << "Diameter: " << diameter(root) << std::endl;
	std::cout << "Top View: " << endl;
	topView(root);
	return 0;
}