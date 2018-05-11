#include <iostream>
#include <map>
#include <list>
#include <stack>

#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <cctype>
#include <memory>
#include "sigslot.h"
#include "tc_shared_ptr.h"
#include "tc_enable_shared_from_this.h"


//using namespace std;
//using namespace tars;

#include <iostream>
#include <utility>


template<typename T,typename U>
class Bnode{
public:
	   Bnode(){}
	   Bnode(std::pair<T,U>&p):lchild(nullptr),rchild(nullptr),parent(nullptr),_balance(0),height(0)
	   {
	         key_value.first=p.first;
			 key_value.second=p.second;
	   }
	   std::pair<T,U>key_value;
       Bnode<T,U>*lchild,*rchild,*parent;
	   uint16_t height,_balance;
	   
	   uint16_t  getheight(Bnode<T,U>*p){
	   	       return std::max(getheight(p->lchild),getheight(p->rchild))+1;
	   }
       
	   uint16_t balancedg(){
           _balance=getheight(lchild)-getheight(rchild);
		   return _balance;
	   }
	   
	   bool isbalanced(){
                  if(_balance>-2 &&_balance <2){return true;}
				  return false;
	   };
	   void updatenode(Bnode<T,U>*p){
             height=getheight(p);
	   }	  
	   T &getKey()    {return key_value.first;}
	   U &getValue(){return key_value.second;}

	   friend class avl_tree;
	   
};


template<typename T,typename U>
class avl_tree{
    public:
		bnode<T,U>*root;
		
			



};





