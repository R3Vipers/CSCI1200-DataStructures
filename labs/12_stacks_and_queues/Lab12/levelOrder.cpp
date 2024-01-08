#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;
// Definition for a binary tree node.
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void clear(TreeNode* root) {
    if(root->left) {
        clear(root->left);
        //delete root->left;
    }
    if(root->right){
        clear(root->right);
        //delete root->right;
    }
    delete root;
}

template <typename T>
class queue_stack {
public:
    queue_stack(): Size(0){};
    int size() {return Size;}
    void push(T value) {
        int s = stack1.size();
        for(int i=0;i<s;i++){
            stack2.push(stack1.top());
            stack1.pop();
        }
        stack1.push(value);
        for(int i=0;i<s;i++){
            stack1.push(stack2.top());
            stack2.pop();
        }
        Size++;
    }
    void pop() {
        stack1.pop();
        Size--;
    }
    bool empty () {return Size==0;}
    TreeNode* front () {return stack1.top();}
private:
    stack<T> stack1;
    stack<T> stack2;
    int Size;
};

template <typename T>
class queue_list {
public:
    queue_list(): Size(0){};
    int size() {return Size;}
    void push(T value) {
        list1.push_front(value);
        Size++;
    }
    void pop() {
        list1.pop_back();
        Size--;
    }
    bool empty () {return Size ==0;}
    T front () {return list1.back();}
private:
    list<T> list1;
    int Size;
};

std::vector<std::vector<int>> levelOrderTraversal(TreeNode* root) {
	std::vector<std::vector<int>> result;

	if (root == nullptr) {
		return result;
	}

	queue_list<TreeNode*> myQueue;
	myQueue.push(root);

	while (!myQueue.empty()) {
		int size = myQueue.size();
		std::vector<int> current_level;
		for (int i = 0; i < size; i++) {
			TreeNode* current = myQueue.front();
			myQueue.pop();
			std::cout << current->val << " " << endl;

			if (current != nullptr) {
				current_level.push_back(current->val);

				if (current->left != nullptr) {
					myQueue.push(current->left);
				}
				if (current->right != nullptr) {
					myQueue.push(current->right);
				}
			}
		}

		result.push_back(current_level);
	}

	return result;
}

int main() {
	/* test case 1
	*    1
	*   2 3
	* 4 5 6 7
	*/
	TreeNode* root1 = new TreeNode(1);
	root1->left = new TreeNode(2);
	root1->right = new TreeNode(3);
	root1->left->left = new TreeNode(4);
	root1->left->right = new TreeNode(5);
	root1->right->left = new TreeNode(6);
	root1->right->right = new TreeNode(7);

	std::cout << "Level Order Traversal: ";
	levelOrderTraversal(root1);
	std::cout << std::endl;

	/* test case 2
	*    1
	*   2 3
	* 4 5 6 7
	*      8 9
	*/
	TreeNode* root2 = new TreeNode(1);
	root2->left = new TreeNode(2);
	root2->right = new TreeNode(3);
	root2->left->left = new TreeNode(4);
	root2->left->right = new TreeNode(5);
	root2->right->left = new TreeNode(6);
	root2->right->right = new TreeNode(7);
	root2->right->right->left = new TreeNode(8);
	root2->right->right->right = new TreeNode(9);

	std::cout << "Level Order Traversal: ";
	levelOrderTraversal(root2);
	std::cout << std::endl;

	/* test case 3
	*     1
	*    2 3
	*  4 5 6 7
	* 8
	*/
	TreeNode* root3 = new TreeNode(1);
	root3->left = new TreeNode(2);
	root3->right = new TreeNode(3);
	root3->left->left = new TreeNode(4);
	root3->left->right = new TreeNode(5);
	root3->right->left = new TreeNode(6);
	root3->right->right = new TreeNode(7);
	root3->left->left->left = new TreeNode(8);

	std::cout << "Level Order Traversal: ";
	levelOrderTraversal(root3);
	std::cout << std::endl;
    clear(root1);
    clear(root2);
    clear(root3);
	return 0;
}

