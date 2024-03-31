#include "iostream"
using namespace std;

struct node{
	int data;
	node* left;
	node* right;
};

// phép toán hợp nhất cây nghiêng s1 và s2 thành cây nghiêng s
void merge(node*& skew, node* firstSkew, node* secondSkew) {
	if (firstSkew == NULL) 
		skew = secondSkew;
	else if (secondSkew == NULL)
		skew = firstSkew;
	else {
		// Lúc nào skew1 cũng phải < skew2
		if (firstSkew->data > secondSkew->data) 
			swap(firstSkew, secondSkew);
		skew = firstSkew;
		merge(skew->right, firstSkew->right, secondSkew);
		swap(skew->left, skew->right);
	}
}

void insert(node*& skew, int value) {
	node* newNode = new node();
	newNode->data = value;
	newNode->left = NULL;
	newNode->right = NULL;
	merge(skew, skew, newNode);
}

void deleteRoot(node*& root) {
	if (root == nullptr) return;

	node* leftChild = root->left;
	node* rightChild = root->right;

	// Xóa nút gốc
	delete root;

	// Hợp nhất hai cây con để tạo lại cây skew heap
	merge(root, leftChild, rightChild);
}

void preOrder(node* root) {
	if (root) {
		cout << root->data << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}


int main() {
	node* root = NULL;
	const int MAX = 5;
	int array[] = { 9,4,7,2,6 };
	for (int i = 0; i < MAX; i++) {
		insert(root, array[i]);
	}
	cout << "\nPreOrder:";
	preOrder(root);

	deleteRoot(root);
	cout << "\nPreOrder after remove root: ";
	preOrder(root);

	return 0;
}