#include<iostream>
#include<conio.h>

using namespace std;

class node{ 
public:
	node(int);
	~node();
	int value;
	node *left;
	node *right;
};

node::node(int val){
	value = val;
	left = NULL;
	right = NULL;
}

class bst{
private:
	// variable
	node *root;
	// functions
	void insert(node**,node*);
	void inordertraverse(node*);
	void preordertraverse(node*);
	void postordertraverse(node*);
	int sumofnodes(node *);
	void mirrorbst(node *);
	int bstdepth(node *);
public:
	// Constructor & Destructor
	bst();
	~bst(){};
	// functions
	void push(int);
	void print(char *);
	int sum(void);
	void mirror(void);
	bool searchnode(int);
	int levelOfNode(int);
	int depth();
};

bst::bst(){
	root = NULL;
}

void bst::push(int val){
	node *newnode = new node(val);
	insert(&root,newnode);
}

void bst::insert(node **rootnode,node *newnode){
	if(*rootnode == NULL)
		*rootnode = newnode;
	else{
		if((*rootnode)->value<newnode->value){
			((*rootnode)->right)?insert(&((*rootnode)->right) , newnode):((*rootnode)->right)=newnode;
		}
		else{
			((*rootnode)->left)?insert(&((*rootnode)->left) , newnode):((*rootnode)->left)=newnode;
		}
	}
}

void bst::print(char* type){
	if(type == "inorder")
		inordertraverse(root);
	else if(type == "preorder")
		preordertraverse(root);
	else if(type == "postorder")
		postordertraverse(root);
	else
		cout<<"Invalid selection ! Valid choices are : inorder , preorder or postorder."<<endl;
}

void bst::inordertraverse(node *rootnode){
	if(rootnode){
		inordertraverse(rootnode->left);
		cout<<rootnode->value<<endl;
		inordertraverse(rootnode->right);
	}
}

void bst::preordertraverse(node *rootnode){
	if(rootnode){
		cout<<rootnode->value<<endl;
		preordertraverse(rootnode->left);
		preordertraverse(rootnode->right);
	}
}

void bst::postordertraverse(node *rootnode){
	if(rootnode){
		postordertraverse(rootnode->left);
		postordertraverse(rootnode->right);
		cout<<rootnode->value<<endl;
	}
}

int bst::sum(){
	return sumofnodes(root);
}
int bst::sumofnodes(node *rootnode){
	int sum = 0;
	if(rootnode){
		sum += sumofnodes(rootnode->left);
		sum += rootnode->value;
		sum += sumofnodes(rootnode->right);		
	}
	return sum;
}

void bst::mirror(){
	mirrorbst(root);
}

void bst::mirrorbst(node *rootnode){
	if(rootnode == NULL)
		return;
	else{
		mirrorbst(rootnode->left);
		mirrorbst(rootnode->right);
		node *temp = rootnode->left;
		rootnode->left = rootnode->right;
		rootnode->right = temp;
	}
}

bool bst::searchnode(int element){
	node* rootnode = root;
	while(rootnode){
		if(rootnode->value == element)
			return 1;
		(rootnode->value < element)?rootnode = rootnode->right : rootnode = rootnode->left;
	}
	return 0;
}

int bst::levelOfNode(int element){
	int level = 0;
	node *rootnode = root;
	
	while(rootnode){
		if(rootnode->value == element)
			return level;
		(rootnode->value < element)?rootnode = rootnode->right : rootnode = rootnode->left;
		level++;
	}
	return -1;
}

int bst::depth(){
	return bstdepth(root);
}

int bst::bstdepth(node *rootnode){
	if(rootnode == NULL)
		return 0;
	else{
		int ld = bstdepth(rootnode->left);
		int rd = bstdepth(rootnode->right);
		
		if(ld>rd)
			return (ld+1) ;
		else
			return (rd+1);
	}
}


int main(int argc , char**argv){
	bst b;
	b.push(5);
	b.push(2);
	b.push(1);
	b.push(3);
	b.push(7);
	b.push(6);
	b.push(8);
	/* Traversal example */
	// b.print("inorder");
	// b.print("preorder");
	b.print("postorder");

	/* Sum of nodes */
	int sum = b.sum();
	cout<<"Sum of nodes is: "<<sum<<endl;

	/* Mirroring BST */
	b.mirror();
	b.print("postorder");
	b.mirror();

	/* Element Search */
	b.searchnode(6)?cout<<"Element Found"<<endl:cout<<"Element Not Found"<<endl;
	b.searchnode(4)?cout<<"Element Found"<<endl:cout<<"Element Not Found"<<endl;

	/* Level of element L0,L1,L2.. */
	int level = b.levelOfNode(4);
	(level >=0)?cout<<"Level of node is "<<level<<endl:cout<<"Element not found in BST"<<endl;

	/* Depth of BST */
	cout<<"Depth of bst is "<<b.depth()<<endl;

	getch();
	return 0;
}