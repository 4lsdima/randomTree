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
//			sortedVector->clear();
//			sortedVector_ptr=NULL;
//		}
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//