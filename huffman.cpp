#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;
struct TreeNode {
	int val;
	string s;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x),s(""), left(NULL), right(NULL) {}
	TreeNode(pair<string, int> p):val(p.second),s(p.first), left(NULL), right(NULL){}
};
vector<pair<string, int>> v = { {"a",10},{"e",15},{ "i",12 },{"s",3 },{ "t",4 },{ "sp",13 },{ "nl",1 } };
struct cmp
{
	bool operator()(TreeNode* a, TreeNode* b)
	{
		return a->val > b->val;
	}
};
void helper(TreeNode* root, vector<string>& res, string str)
{
	if (!root)
		return;
	else
	{
		if (!root->left && !root->right)
			res.push_back(root->s+": "+str);
		helper(root->left, res, str + '0');
		helper(root->right, res, str + '1');
	}

}
void preorder(TreeNode* root)
{
	if (!root)
		return;
	preorder(root->left);
	cout << root->val << endl;;
	preorder(root->right);
}

int main()
{
	priority_queue<TreeNode*, vector<TreeNode*>, cmp> q;
	for (int i = 0; i < v.size(); ++i)
	{
		TreeNode* temp = new TreeNode(v[i]);
		q.push(temp);
	}

	TreeNode* root = nullptr;
	while (q.size()!=1)
	{
		TreeNode* t1, *t2;
		t1 = q.top();
		q.pop();
		t2 = q.top();
		q.pop();
		int temp = t1->val+t2->val;
		TreeNode* t3 = new TreeNode(temp);
		root = t3;
		t3->left = t1;
		t3->right = t2;
		q.push(t3);
	}
	//preorder(root);
	vector<string> vs;
	string str;
	helper(root, vs, str);
	for (auto ele : vs)
	{
		cout << ele << endl;
	}
	return 0;

}
