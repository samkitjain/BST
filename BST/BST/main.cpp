#include<iostream>
#include<conio.h>
#include<stack>

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

	void inordertraverse_iter(node*);
	void preordertraverse_iter(node*);
	void postordertraverse_iter(node*);

	int sumofnodes(node*);
	void mirrorbst(node*);
	int bstdepth(node*);
	node* deleteMin(node*);
	node* deleteMax(node*);
	node* deleteNode(int,node*);
	node* minNode(node*);
	node* floor(int,node*);
	node* ceil(int,node*);
	node* ksmallest(int,node*); // Selection
	node* klargest(int,node*); // Selection
	node* lowestComAnces(int,int,node*); // Lowest common Ances : Assumption both the nodes are in tree and are not NULL.
										 // Else we have to make query function to find that
	int distBtwNodes(int,int,node*); // Distance in terms of hops to reach b from a. i.e.a->b . Assumtions : a & b are in tree and not null and not a=b
	int distOfNodeFromRoot(int,node*); // Assumption node is in tree and not null
public:
	// Constructor & Destructor
	bst();
	~bst(){};
	// functions
	void push(int);
	void print(char *);
	void print_iter(char *);
	int sum(void);
	void mirror(void);
	bool searchnode(int);
	int levelOfNode(int);
	int depth();
	void deleteMin();
	void deleteMax();
	void deleteNode(int);
	int minNode();
	int floor(int);
	int ceil(int);
	int ksmallest(int);
	int klargest(int);
	int lowestComAnces(int,int); // Lowest common Ances : Assumption both the nodes are in tree and are not NULL and are not equal.
								 // Else we have to make query function to find that
	int distBtwNodes(int,int);   // Distance in terms of hops to reach b from a. i.e.a->b . Assumtions : a & b are in tree and not null and not a=b
	int distOfNodeFromRoot(int); // Assumption node is in tree and not null
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
void bst::print_iter(char* type){
	if(type == "inorder")
		inordertraverse_iter(root);
	else if(type == "preorder")
		preordertraverse_iter(root);
	else if(type == "postorder")
		postordertraverse_iter(root);
	else
		cout<<"Invalid selection ! Valid choices are : inorder , preorder or postorder."<<endl;
}

void bst::inordertraverse_iter(node *rootnode){
	stack<node*> s;
	node* temp;
	if(rootnode == NULL) return;
	while(rootnode){
		s.push(rootnode);
		rootnode = rootnode->left;
	}
	while(!s.empty()){
		rootnode = s.top();
		s.pop();
		cout<<rootnode->value;
		if(rootnode->right){
			rootnode = rootnode->right;
			while(rootnode){
				s.push(rootnode);
				rootnode = rootnode->left;
			}
		}
	}
}

void bst::preordertraverse_iter(node *rootnode){
	stack<node*> s;
	if(rootnode == NULL)
		return;
	s.push(rootnode);
	while(!s.empty()){
		rootnode = s.top();
		s.pop();
		cout<<rootnode->value;
		if(rootnode->right)
			s.push(rootnode->right);
		if(rootnode->left)
			s.push(rootnode->left);
	}
}

void bst::postordertraverse_iter(node *rootnode){

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

int bst::ceil(int key){
	node *temp= ceil(key,root);
	if(temp!=NULL) 
		return temp->value;
	else 
		return NULL;
}

node* bst::ceil(int key,node* root){
	node *ceilnode = NULL ;
	while(root){
		if(root->value == key ){
			ceilnode = root;
			break;
		}
		else if(root->value > key){
			ceilnode =  root;
			root = root->left;
		}
		else
			root = root->right;
	}
	return ceilnode;
}


int bst::floor(int key){
	node *temp= floor(key,root);
	if(temp!=NULL) 
		return temp->value;
	else 
		return NULL;
}

node* bst::floor(int key,node* root){
	node *floornode = NULL;
	while(root){
		if(root->value==key){
			floornode=root;
			break;
		}
		else if(root->value>key)
			root = root->left;
		else{
			floornode = root;
			root=root->right;
		}
	}
	return floornode;
}


int bst::ksmallest(int k){
	node* knode = ksmallest(k,root);
	if(knode == NULL){
		cout<<"kth smallest node does not exist."<<endl;
		return -1;
	}
	return knode->value;
}

node* bst::ksmallest(int k ,node* rootNode){
	if(rootNode==NULL)return NULL;
	
	stack<node*> s;
	while(rootNode){
		s.push(rootNode);
		rootNode = rootNode->left;
	}
	while(!s.empty()){
		rootNode = s.top();
		s.pop();

		if(--k == 0){
			break;
		}
		
		if(rootNode->right){
			rootNode = rootNode->right;
			while(rootNode){
				s.push(rootNode);
				rootNode=rootNode->left;
			}
		}
	}
	if(k==0) return rootNode;
	else return NULL;
}


void bst::deleteMin(){
	root = deleteMin(root);
}

node* bst::deleteMin(node* rootNode){
	if(rootNode == NULL)
		return NULL;
	if(rootNode->left == NULL)
		return rootNode->right;
	rootNode->left = deleteMin(rootNode->left);
	return rootNode;
}

void bst::deleteMax(){
	root = deleteMax(root);
}

node* bst::deleteMax(node* rootNode){
	if(rootNode==NULL)
		return NULL;
	if(rootNode->right==NULL)
		return rootNode->left;
	rootNode->right = deleteMax(rootNode->right);
	return rootNode;
}

node* bst::minNode(node* rootNode){
	if(rootNode->left == NULL)
		return rootNode;
	else 
		return minNode(rootNode->left);
}
void bst::deleteNode(int key){
	root = deleteNode(key,root);
}

node* bst::deleteNode(int key, node* rootNode){
	if(rootNode==NULL)
		return NULL;
	if(rootNode->value > key) 
		rootNode->left = deleteNode(key,rootNode->left);
	else if(rootNode->value < key) 
		rootNode->right = deleteNode(key,rootNode->right);
	else{
		if(rootNode->right == NULL)
			return rootNode->left;
		node* temp = rootNode;
		rootNode = minNode(temp->right);
		rootNode->right = deleteMin(temp->right);
		rootNode->left = temp->left;
	}
	return rootNode;
}

int bst::lowestComAnces(int a,int b){
	node *ances = lowestComAnces(a , b , root);
	if(ances ==NULL){
		cout<<"No common ancestor"<<endl;
		return -1;
	}
	else
		return ances->value;
}

node* bst::lowestComAnces(int a , int b , node* rootNode){
	if(rootNode == NULL)return NULL;

	bool found =0;
	while(rootNode){
		if(rootNode->value >=a && rootNode->value<=b || rootNode->value <=a && rootNode->value>=b){
			found =1;
			break;
		}
		else if(rootNode->value >a && rootNode->value>b)
			rootNode =rootNode->left;
		else
			rootNode =rootNode->right;
	}
	if (found==1) return rootNode;
	else return NULL;
}

int bst::distOfNodeFromRoot(int k){
	return distOfNodeFromRoot(k,root);
}

int bst::distOfNodeFromRoot(int k,node* rootNode){
	if(rootNode==NULL)return -1;
	
	int dist = 0;
	bool found = 0;
	while(rootNode){
		
		if(rootNode->value ==k){
			break;
			found = 1;
		}
		else if(rootNode->value > k)rootNode = rootNode->left;
		else rootNode = rootNode->right;
		
		dist++;
	}

	if(found==1)return dist;
	else return dist;
}

int bst::distBtwNodes(int a,int b){
	return distBtwNodes(a,b,root);
}


int bst::distBtwNodes(int a,int b,node* rootNode){
	if(rootNode==NULL)return -1;

	node* ances = lowestComAnces(a,b,rootNode);
	int distAnces = distOfNodeFromRoot(ances->value,root);
	int dista = distOfNodeFromRoot(a,root);
	int distb = distOfNodeFromRoot(b,root);
	
	return ((dista+distb)-(2*distAnces));
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

	/*After min node deletion */
	b.print("postorder");
	b.deleteMin();
	b.print("postorder");
	cout<<endl;

	/*After max node deletion */
	//b.print("postorder");
	//b.deleteMax();
	//cout<<endl;
	//b.print("postorder");

	b.deleteNode(5);
	cout<<endl;
	b.print("postorder");

	cout<<endl;
	cout<<endl<<b.ceil(1)<<endl;
	cout<<endl<<b.floor(5)<<endl;
	
	cout<<endl;
	b.print("inorder");
	cout<<endl;
	b.print_iter("inorder");
	
	cout<<endl;
	b.print("preorder");
	cout<<endl;
	b.print_iter("preorder");

	cout<<endl;
	cout<<b.ksmallest(7)<<endl;

	cout<<endl;
	cout<<b.lowestComAnces(7,8);

	cout<<endl;
	cout<<"Distance is "<<b.distOfNodeFromRoot(3);

	cout<<endl;
	cout<<"Distance is "<<b.distBtwNodes(3,8);
	
	getch();
	return 0;
}