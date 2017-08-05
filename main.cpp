#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <cstring>

#include <string>
#include <vector>
#include <fstream>


#include "tree.h"


using namespace std;


typedef long int ty;
typedef double dbl;
typedef std::pair<ty,dbl> myPair;
typedef std::vector<ty> tyVector;

// typedef typename tyVector::const_iterator  cvIt;
// typedef typename tyVector::iterator  vIt;
// typedef std::vector<myPair> pairVector;
// typedef typename pairVector::iterator pvIt;
// typedef std::vector<pairVector*> vVector;
// typedef typename vVector::iterator vvIt;



int main(int argc, char* argv[])
{
/////////////////////////////////////////////////////////////////////////////////////////////////////

	    ifstream infile;
	    if (argc>1)
	    {
	      string infileName=argv[1];


	      infile.open(argv[1]);

	      if (!infile.is_open())
	      {
	          cout<< "\nfile '"<<argv[1]<<"' NOT FOUND!\nexiting\n";
	          return 1;
	      }
	    }
	    else
	    {
	      cout<<"type infileName   -file with rand numbers\n";
	      return 2;
	    } 

	//****************************************************************************************************//

	vector<myPair> numbers;

	ty n1;
	dbl n2; 
	myPair num;  //Variable to hold each pair as it is read

	while (infile >> n1>>n2) 
	{
	//Add the number to the end of the array
	// revenue.push_back(std::make_pair("string",map[i].second));
	num=make_pair(n1,n2);
	numbers.push_back(num);
	}

	//Close the file stream
	infile.close();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	/////////////////////////////////////////////
	
	//searching by key in 'numbers':

	tree<long int, double> ob;
	
	ob.makeTree(numbers);

	// 1)	
	std::vector<double*> * ptr=ob.find(40);
	for(vector<double*>::iterator it=ptr->begin(); it!=ptr->end(); it++)
	{
		cout<<"("<< 40 <<", " << **it << ")\n";	
	}

	ob.clearResults();
	//2)
	ptr=ob.find(41);
	for(vector<double*>::iterator it=ptr->begin(); it!=ptr->end(); it++)
	{
		cout<<"("<< 41 <<", " << **it << ")\n";	
	}
	ob.clearResults();

	//3)
	ptr=ob.find(40);
	for(vector<double*>::iterator it=ptr->begin(); it!=ptr->end(); it++)
	{
		cout<<"("<< 40 <<", " << **it << ")\n";	
	}

	ob.clearResults();

	ty t= 100;
	do
	{

		ptr=ob.find(50);
		for(vector<double*>::iterator it=ptr->begin(); it!=ptr->end(); it++)
		{
			cout<<"("<< 50 <<", " << **it << ")\n";	
		}

		ob.clearResults();
		ptr=NULL;	
		cout<<"------------------\n";
		ptr=ob.find(t);
		for(vector<double*>::iterator it=ptr->begin(); it!=ptr->end(); it++)
		{
			cout<<"("<< t <<", " << **it << ")\n";	
		}

		ob.clearResults();
		ptr=NULL;	
		cout<<"+++++++++++++++++++\n";
		t--;
	}while (t>45);
	ob.deleteTree();

		
	//sorting the 'numbers'
	std::vector< std::pair<ty,double> >* sortedVector_ptr=ob.Sort(numbers);


	if(sortedVector_ptr)
	{
		ofstream outfile("sortedPairs.dat"); 
		for(std::vector< std::pair<ty,double> >::iterator it=sortedVector_ptr->begin(); it!=sortedVector_ptr->end(); it++)
		{
			outfile <<it->first<<"  "<<it->second<<"\n";   
		}

		outfile.close(); 

		sortedVector_ptr->clear();
		delete sortedVector_ptr;
		sortedVector_ptr=NULL;
	}

	return 0;

}