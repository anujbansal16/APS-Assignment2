#include <bits/stdc++.h>
typedef struct Node Node;
using namespace std;
Node *root=NULL;
Node *newRoot=NULL;
struct Node
{
	int *keys;
	int t;
	struct Node **childs;
	int n;
	bool isLeaf;
};

Node * createNode(int t, bool isLeaf){
	Node *newnode=new Node;
	newnode->t=t;
    newnode->isLeaf=isLeaf;
    newnode->keys=new int[2*t-1];     
    newnode->childs=new Node *[2*t];
    newnode->n=0; 
    return newnode;
}


Node * splitChild(int i,Node *y,Node *newnode){
	// cout<<"splitChild "<<(y->n)<<"\n";
	int t=(newnode->t);
	Node *z=createNode(y->t,y->isLeaf);
	z->n=t-1;
	for (int j = 0;j<t-1;j++) 
        z->keys[j]=y->keys[j+t]; 
    if (y->isLeaf == false) { 
        for (int j = 0;j<t;j++) 
            z->childs[j]=y->childs[j+t]; 
    } 
    y->n=t-1;
    for (int j=newnode->n;j>=i+1;j--) 
        newnode->childs[j+1]=newnode->childs[j]; 
    
    newnode->childs[i+1]=z;
    for (int j=(newnode->n)-1;j>=i;j--) 
        newnode->keys[j+1] = newnode->keys[j]; 

    newnode->keys[i]=y->keys[t-1];
    (newnode->n)++;
    return newnode;
}

Node * insertIFNonFull(Node *root,int key){
	// cout<<"insertIFNonFull\n";
	int i=(root->n)-1;
	if(root->isLeaf){
		// cout<<"root is leaf "<<(root->n)<<endl;
		while(i>=0 && key<root->keys[i]){
			root->keys[i+1]=root->keys[i];
			i--;
		}
		root->keys[i+1]=key; 
        (root->n)++;
        return root;
	}
	else{
		// cout<<"root is internal\n";
		while(i>=0 && key<root->keys[i])
            i--; 
        if(root->childs[i+1]->n==2*(root->t)-1){
        	//split with root no new node
			root=splitChild(i+1,root->childs[i+1],root); 
            if (root->keys[i+1]<key) 
                i++; 
        }
        root->childs[i+1]=insertIFNonFull(root->childs[i+1],key);
        return root;
	}

}


Node *insert(Node *root,int key,int t){
	// cout<<"value "<<key<<endl;
	if(root==NULL){
		// cout<<"Root null\n";
		root=createNode(t,true);
		root->keys[0]=key;
		(root->n)++;
		return root;
	}
	else{
		// cout<<(root->n)<<endl;
		// cout<<"Root not null\n";
		//check of root is full
		if(root->n==2*t-1){
			// cout<<"Root full\n";
			newRoot=createNode(t,false);
			newRoot->childs[0]=root;
			newRoot=splitChild(0,root,newRoot);
			// cout<<(newRoot->isLeaf)<<endl;
			if(newRoot->keys[0]<key)
				newRoot->childs[1]=insertIFNonFull(newRoot->childs[1],key);
			else
				newRoot->childs[0]=insertIFNonFull(newRoot->childs[0],key);
			root=newRoot;
			return root;
		}
		else{//tree not full simply insert in it by calling helper function
			// cout<<"root not null not empty\n";
			root=insertIFNonFull(root,key);
			return root;
			
		}		
	}
}

void traverse(Node *root) { 
    int i; 
    for (i=0;i<(root->n);i++){ 
        if (root->isLeaf==false) {
            traverse(root->childs[i]);
        }
        // cout<<"size "<<(root->n)<<"\n";
        cout<<root->keys[i]<<" "; 
    } 
    if (root->isLeaf==false){
    	// cout<<"herereere\n";
    	traverse(root->childs[i]);
    }
} 


Node * search(Node *root, int key){
	int n=(root->n)-1;
	int i=0;
	while(i<=n && key>root->keys[i])
		i++;
	if(i<=n && root->keys[i]==key)
		return root;
	if(root->isLeaf)
		return NULL;
	return search(root->childs[i],key);


}
int main(){
	int choice,q,k,t,x;
	cout<<"Please enter minimum number of keys you want in B-Tree\n";
	cin>>t;
	cout<<"Enter Q\n";
	cin>>q;
	while(q--){
		cin>>x>>k;
		switch(x){
			case 1:
				root=insert(root,k,t);			
				traverse(root);
				cout<<endl;
				break;
			case 2:
				search(root,k)?cout<<"Present\n":cout<<"Not present\n";

		}
	}

	// root=insert(root,10,3);
	// root=insert(root,20,3); 
 //    root=insert(root,5,3); 
 //    root=insert(root,6,3); 
 //    root=insert(root,12,3); 
 //    root=insert(root,30,3); 
 //    root=insert(root,7,3); 
 //    root=insert(root,27,3); 
 //    root=insert(root,57,3); 
 //    root=insert(root,37,3); 
 //    root=insert(root,1,3); 
 //    root=insert(root,8,3); 
 //    root=insert(root,51,3); 
 	// cout<<"-------------------\n";
    // search(root,28)?cout<<"Present":cout<<"Not present";
    // cout<<root->n<<"\n";
	return 0;
}