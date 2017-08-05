#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

//*********************************************************** README! ********************************************************************//
// This technique creates a well-balanced binary Tree for
// 1) fast element searching in the incoming data (std::vector of std::pair<T1,T2>'s )
// 2) fast sorting the incoming data.
// ( here T1 - is a key value, so it could be typeof int, short, unsigned, long unsigned, long. )
// The height of the Tree is guaranteed to be O(log(N)) at large N, ( N = size of incoming data )
// 
// Typical usage example:
//	Asume, for example,  the incoming data {{int key,double value}} is stored in std::vector<std::pair<int, double> > invector
//
// 1)-------------------------------------------------------------------------------------------------------------------------------------------------
//	 To find double items, relevant to certain int key:
// 	 First of all, we create new instance of tree - an object of class tree:
//
// 		tree <int,double> ob;
//
// 	Then we arrange the incoming data into the tree:
//		ob.makeTree(invector);			//this creates a binary tree
//
//	Searching itself:
//		
// 		std::vector<double*> * ptr=ob.find(key);		// method tree::find(key) returns a pointer to std::vector<T2*> of pointers to relevant items.
//
//	now, for example, we can printout the results:
//
//		for(std::vector<double*>::iterator it=ptr->begin(); it!=ptr->end(); it++)
//		{
//			cout<<"("<< key <<", " << **it << ")\n";	
//		}
//
//	after usage the results, it's better to clear that vector of results, for next search:
//
//		ob.clearResults();

//	After all, we need to fold tree:
//
//		ob.deleteTree();
//
// 2)-------------------------------------------------------------------------------------------------------------------------------------------------
// For fast sorting the incoming data:
// we create new instance of tree - an object of class tree:
//
// 		tree <int,double> ob;
//
//	then:
//
// 		std::vector< std::pair<int,double> >* sortedVector_ptr=ob.Sort(invector); //returns a pointer to std::vector<std::pair<T1,T2> >
// 
//	where the 'sortedVector_ptr' would be the pointer to ordered vector of pairs(int key, double value)
//  (method .Sort() creates binary tree by itself, and folds tree while sorting procedure)
// 
//  do not forget to clear results after all:
// 
//		if(sortedVector_ptr)
//		{
//			sortedVector_ptr->clear();
//			delete sortedVector_ptr; 
//			sortedVector_ptr=NULL;
//		}
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#ifndef TREE_H
#define TREE_H

using namespace std;



template<class T1,class T2>
class tree
{
public:

	typedef size_t ty;
	typedef std::vector<T1> tVector;
	typedef typename tVector::const_iterator  c_vIt;
	typedef typename tVector::iterator  vIt;
	typedef std::pair<T1,T2> mPair;
	typedef std::vector<mPair> pVector;
	typedef typename pVector::const_iterator c_pvIt;
	typedef typename pVector::iterator pvIt;

	typedef std::vector<T2*> rVector;
	// typedef const std::vector<T2*> & constRef;//!

	typedef struct node
	{
		node * parent;
		node * left;
		node * right;
		T1 val; //node key value
		T2 item; // stuff corresponding to this key
		ty size; //number of nodes in subtree with *this node as a root
		node(const T1 &inVal=T1(),const T2 &inItem=T2() )//default constructor:
		{
			parent=NULL;
			left=NULL;
			right=NULL;
			val=inVal;
			item=inItem;
			size=0;
		}
	}node;

	node * rightRotation(node*);
	node * leftRotation(node*);
	node * createNode(node *,const T1&,const T2&);
	node * Tree(const pVector &);
	node * woLeft(node * n); 
	node * findMin(node * root);
	node * deleteWoLeft(node * n,pVector *);
	void foldTree(node * ,pVector * );
	node * findRoot(node *);
	node * justDeleteWoLeft(node *);
	void justfoldTree(node *);
	node * search4Key(node *, const T1&);
	void Show(node * );	// to Show the Tree (recursive!)

	//MAIN functions:

	//find by key:
	void makeTree(const pVector&);
 	rVector * find(const T1&);
 	void clearResults();
	void deleteTree();
	//sorting:
	pVector * Sort(const pVector&);
private:
	node * Root;
	rVector * resVector_ptr;
};
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   IMPLEMENTATION  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

// AUX FUNCTIONs:
template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::rightRotation(node * n) // right rotation node n->left around node n
{
	ty qs=n->size;//for size store
	node * q = n->left; //we want n-> left to be a parent of n
	n->left = q->right; //interesting
	q->right = n; 
	q->parent=n->parent;
	if((q->parent)&&(q->parent->left)&&(q->parent->left==n))
	{
		q->parent->left=q;
	}
	else if((q->parent)&&(q->parent->right)&&(q->parent->right==n))
	{
		q->parent->right=q;
	}
	
	n->parent=q;
	if(n->left)
	{
		n->left->parent=n;	
	}
	//modify size:
	ty ns(0);
	if(n->left)
	{
		ns+=(n->left->size)+1;
	}
	if(n->right)
	{
		ns+=(n->right->size)+1;
	}
	q->size=qs;
	n->size=ns;
	return q; 
}
template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::leftRotation(node * n) // left rotation node n->right around node n
{
	ty qs=n->size;//for size store
	node * q = n->right; //we want n-> right to be a parent of n	
	n->right = q->left; //interesting
	q->left = n; 
	q->parent=n->parent;
	if((q->parent)&&(q->parent->left)&&(q->parent->left==n))
	{
		q->parent->left=q;
	}
	else if((q->parent)&&(q->parent->right)&&(q->parent->right==n))
	{
		q->parent->right=q;
	}

	n->parent=q;
	
	if(n->right)
	{
		n->right->parent=n;
	}
	//modify size:
	ty ns(0);
	if(n->left)
	{
		ns+=n->left->size+1;
	}
	if(n->right)
	{
		ns+=n->right->size+1;
	}
	n->size=ns;
	q->size=qs;
	return q; 
}

template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::createNode(node * prev, const T1 &val, const T2 &item ) //returns  ptr to root of Tree as well
{
	if(!prev)
	{
		node * prev=new node(val,item);
		return prev;
	}
	node *root=prev;
	node *tmp=NULL;
	do
	{
		// Any node may occur to be a root of its subTree  with probability p=1/(n+1)
		// where n — size of subTree before new node insertion
		// Thus we apply the rightRotation (leftRotation) with probability p:

		if(val<prev->val)
		{
			// do smth with right rotation:
			// if((prev->left)&&(prev->left->size>0)&&(rand()%(prev->size+1)==0))   // 1)
			// if((prev->left)&&(prev->left->size>0)&&(rand()%(prev->size)==0)) 	// 2)
			// if((prev->left)&&(prev->left->left)&&(rand()%(prev->size+1)==0))		// 3) best
			if((prev->left)&&(prev->left->left)&&(rand()%(prev->size)==0))		// 4)
			{
				prev=rightRotation(prev);
				if(!prev->parent)
				{	
					root=prev;//new global root:
				}
			}
		}
		else//  val >= prev->val
		{	
			// do smth with left rotation:
			// if((prev->right)&&(prev->right->size>0)&&(prev->val!=prev->right->val)&&(rand()%(prev->size+1)==0)) // 1)
			// if((prev->right)&&(prev->right->size>0)&&(prev->val!=prev->right->val)&&(rand()%(prev->size)==0))   // 2)
			// if((prev->right)&&(prev->right->right)&&(prev->val!=prev->right->val)&&(rand()%(prev->size+1)==0))  // 3) best
			if((prev->right)&&(prev->right->right)&&(prev->val!=prev->right->val)&&(rand()%(prev->size)==0))    // 4)
			{
				prev=leftRotation(prev);
				if(!prev->parent)
				{	
					root=prev;//new global root:
				}
			}
		}
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		if(val<prev->val)
		{
			tmp=prev->left;	
			if(tmp)
			{
				prev->size++;
				prev=tmp;	
			}
		}
		else //val >= prev->val
		{
			tmp=prev->right;
			if(tmp)
			{
				prev->size++;
				prev=tmp;	
			}
		}

	}while(tmp);

	// and now we've arrived to one of leafs:
	if(val<prev->val)
	{

		prev->left= new node(val,item);
		prev->left->parent=prev;
		prev->size++;
	}
	if(val>=prev->val)
	{
		prev->right = new node(val,item);
		prev->right->parent=prev;
		prev->size++;
	}
	prev=root;
	return prev;
}

template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::Tree(const pVector &invector) //creates Tree and returns ptr to root
{
	node * root=NULL;
	for(c_pvIt it=invector.begin(); it!=invector.end();++it)
	{
		root=createNode(root,(*it).first, (*it).second);
	}
	return root;
}
template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::woLeft(node * n)  //to find the most left node in the left branch
{
	if (!n)
	{
		return NULL;
	}
	do
	{
		if(!n->left)
		{
			// std::cout<<"woLeft found: "<<n->val<<"\n";
			return n;
		}
		n=n->left;
				
	}while(n);
}
template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::findMin(node * n) // return ptr to node with min key
{
	if(n)
	{
		n=woLeft(n);	
		// std::cout<<"MIN = "<<n->val<<"\n";
		if (n)
		{
			return n;
		}
	}
}

template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::deleteWoLeft(node * n, pVector * sVector)//delete (using woLeft(n)) from left to right, Add deleted node->val and node->item as pair to sortedVector of sorted pairs
{
	if(!n){return NULL;}
	if((n->right)&&(n->parent))//case of node with right, w right parent
	{
		// std::cout<<"case of node with right, w right parent: "<<n->val<<"\n";	
		node * tmp=n;
		sVector->push_back(mPair(tmp->val,tmp->item));
		n=n->right;
		n->parent=tmp->parent;
		tmp->parent->left=n;
		n=woLeft(n);
		delete tmp;
		tmp=NULL;
		return n;
	}
	if((!n->right)&&(n->parent)) //case of Leaf
	{	
		// std::cout<<"case of leaf: "<<n->val<<"\n";	
		sVector->push_back(mPair(n->val,n->item));
		n=n->parent;
		delete n->left;
		n->left=NULL;
		return n;
	}
	if((n->right)&&(!n->parent)) //case of root 
	{
		// std::cout<<"case of Root: "<<n->val<<"\n";
		sVector->push_back(mPair(n->val,n->item));
		n=n->right;
		delete n->parent;
		n->parent=NULL;
		return woLeft(n);
	}
	if((!n->right)&&(!n->parent)) //case of single root 
	{
		// std::cout<<"case of Single Root: "<<n->val<<"\n";
		sVector->push_back(mPair(n->val,n->item));
		delete n;
		n=NULL;
		// std::cout <<"\tCoMpLeTe!!!\n\n";
		return NULL;
	}
}

template<class T1,class T2>
void tree<T1,T2>::foldTree(node * root, pVector * sVector)//Folds Tree from left to right(in 'post-order', using deleteWoLeft(n)), fills out the sortedVector
{
	std::cout<<"begin sorting:\n";
	std::cout<<"folding Tree...\n";
	node * n=woLeft(root);
	while(n)
	{
		n=deleteWoLeft(n,sVector);
	}
	std::cout <<"\tCoMpLeTe!!!\n\n";
}

template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::findRoot(node * n)//find root node from anywhere
{
	node * tmp;
	do
	{
		tmp=n->parent;
		if(tmp){n=n->parent;}
	}while(tmp);
	std::cout<<"Root found: ("<<n->val<<", "<<n->size<<")\n";
	return n;
}

template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::justDeleteWoLeft(node * n)//just delete from mostLeft
{
	if(!n){return NULL;}

	if((n->right)&&(n->parent))//case of node with right, w right parent: 
	{
		// std::cout<<"case of node with right, w right parent: "<<n->val<<"\n";	
		node * tmp=n;
		n=n->right;
		n->parent=tmp->parent;
		tmp->parent->left=n;
		n=woLeft(n);
		delete tmp;
		tmp=NULL;
		return n;
	}
	if((!n->right)&&(n->parent))// case of Leaf
	{	
		// std::cout<<"case of leaf: "<<n->val<<"\n";	
		n=n->parent;
		delete n->left;
		n->left=NULL;
		return n;
	}
	if((n->right)&&(!n->parent)) //case of root 
	{
		// std::cout<<"case of Root: "<<n->val<<"\n";
		n=n->right;
		delete n->parent;
		n->parent=NULL;
		return woLeft(n);
	}
	if((!n->right)&&(!n->parent)) //case of single root 
	{
		// std::cout<<"case of Single Root: "<<n->val<<"\n";
		delete n;
		n=NULL;
		// std::cout <<"\tCoMpLeTe!!!\n\n";
		return NULL;
	}
}

template<class T1,class T2>
void tree<T1,T2>::justfoldTree(node * n)//just delete tree
{
	std::cout<<"folding Tree...\n";
	n=woLeft(n);
	while(n)
	{
		n=justDeleteWoLeft(n);
	}
	std::cout <<"\tCoMpLeTe!!!\n\n";
}

template<class T1,class T2>
void tree<T1,T2>::Show(node * n)// shows Tree. recursive!!! 
{
	std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<"\n";
	// std::cout<<"H  "<<n->h<<":\n\n";		
	// std::cout<<"size  "<<n->size<<":\n\n";
	if(n->parent)
	{
		if((n->parent->left)&&(n==n->parent->left))
		{
			std::cout<<"\t\t__("<<n->parent->val<<", "<<n->parent->item<<")\n";	
		}
		if((n->parent->right)&&(n==n->parent->right))
		{
			std::cout<<"("<<n->parent->val<<", "<<n->parent->item<<")__"<<"\n";	
		}
	}
	std::cout<<"\t("<<n->val<<", "<<n->item<<")\n";
	if(n->left)
	{
		std::cout<<"("<<n->left->val<<", "<<n->left->item<<")";
	}
	if(n->right)
	{
		std::cout<<"\t\t("<<n->right->val<<", "<<n->right->item<<")";
	}
	std::cout<<"\n";
	std::cout<<"\n++++++++++++++++++++++++++++++++\n\n"<<"\n";
		
	if(n->left){
		Show(n->left);
	}
	if(n->right)
	{
		Show(n->right);
	}
}


template<class T1,class T2>
typename tree<T1,T2>::node * tree<T1,T2>::search4Key(node * n, const T1& key) //try to find the first (after initial) node with val==key
{
	// std::cout<< "search4Key: "<< key<<"\n";
	node * tmp =NULL;
	do
	{
		if(key<n->val)
		{
			tmp=n->left;
			// std::cout<<"\tsearch4Key: go to the Left from "<<n->val<<"\n";
		}
		else // key >= n->val
		{
			tmp=n->right;
			// std::cout<<"\tsearch4Key: go to the Rigth from "<<n->val<<"\n";
		}
		if(tmp)
		{
			n=tmp;
			if(n->val==key)
			{
				// std::cout<<"   search4Key: key: "<<n->val<<" found!\n";
				return n;
			}
		}

	}while(tmp);

	if(n->val!=key)
	{
		// std::cout<<"   search4Key: key value requested NOT found!\n";
		return NULL;
	}
	// else {return n;}
}


// MAIN FUNCTIONs:

//make tree for find()
template<class T1,class T2>
void tree<T1,T2>::makeTree(const pVector& invector)
{
	Root=NULL;
	resVector_ptr=new typename tree<T1,T2>::rVector(); 
	std::cout<<"creating Tree...\n";
	Root=Tree(invector);
	std::cout<<"\tdone!\n";
}

//find by key:
template<class T1,class T2>
typename tree<T1,T2>::rVector * tree<T1,T2>::find(const T1& key) // returns pointer to vector<T2*> of pointers to items, found by key
{
	node * n =Root;
	node * tmp=NULL;
	do
	{
		if(n->val!=key)
		{
			tmp=search4Key(n,key);
			if(tmp) //node found
			{
				n=tmp;
				// std::cout<<"   find: key has been Found: "<<n->val<<"\n";
			}
		}
		else
		{
			// std::cout<<"   key requested: "<<n->val<<" is in the root!\n";
			resVector_ptr->push_back(new T2(n->item));
			tmp=n->right;
			if(tmp) //node to the right does exist
			{
				n=tmp;
			}
		}
	}while(tmp);
	return resVector_ptr;
}

// clear results of searching: 
template<class T1,class T2>
void tree<T1,T2>::clearResults()
{
	for(typename rVector::iterator it=resVector_ptr->begin();it!=resVector_ptr->end();it++)
	{
		delete *it;
		*it=NULL;
	}
	resVector_ptr->clear();
}


//delete tree made by makeTree()
template<class T1,class T2>
void tree<T1,T2>::deleteTree()
{
	if(Root)
	{
		justfoldTree(Root);	
	}
	delete resVector_ptr;
	resVector_ptr=NULL;
	
}

//sorting:
template<class T1,class T2>
typename tree<T1,T2>::pVector * tree<T1,T2>::Sort(const pVector & invector)	//returns vector of sorted pairs(val, item)
{
	std::cout<<"creating Tree...\n";
	node * root=Tree(invector); //create Tree
	std::cout<<"\tdone!\n";

	// Show(root);
	//sorting:
	// node * minNode=findMin(root);
	// std::cout<<"min key: "<<minNode->val<<"\n";
	pVector * sVector = new pVector();

	foldTree(root,sVector);
	return sVector;
}


#endif
