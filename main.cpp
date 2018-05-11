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
	   Bnode(std::pair<T,U>&p):lchild(nullptr),rchild(nullptr),parent(nullptr)
	   {
	         key_value.first=p.first;
			 key_value.second=p.second;
	   }
	   std::pair<T,U>key_value;
       Bnode<T,U>*lchild,*rchild,*parent;
	   T &getKey()    {return key_value.first;}
	   U &getValue(){return key_value.second;}

	   friend class bin2tree;
	   
};




template<typename T,typename U>
class binSTtree{

public:
	Bnode<T,U> *root;
	size_t size;
	
	binSTtree():root(NULL),size(0){}
	size_t getsize(){return size;}
    bool insert(std::pair<T,U>&p){

	 Bnode<T,U>* tem=NULL;
	 Bnode<T,U> *pnode=new Bnode<T,U>(p);
     std::cout<<"next line is search()"<<std::endl;
	 if(((tem=search(p))!=NULL)){
	 	std::cout<<"search top line"<<std::endl;
	 	 if(tem->getKey()==p.first){//over doit
		 	return false;
		 }
		 //tem=parent
		 if(tem->getKey()>p.first)
		 {
		    tem->lchild=pnode;
			pnode->parent=tem;
		 }else{
		 	tem->rchild=pnode;
			pnode->parent=tem;
		 }
		 size+=1;
		 return true;
	 }
	 if(root==NULL)
	 {
	   root=pnode;
	   pnode->parent=NULL;
	   size+=1;
	   return true;
	 }
     return false;

   }
   //search 
   Bnode<T,U> * search(std::pair<T,U>&p){
         if(root==NULL){return NULL;}
         Bnode<T,U> *ptem=root,*parent=NULL;
		 while(ptem)
		 {     parent=ptem;
		      if(ptem->getKey()==p.first)//T class must be compareable or error
		      {
		          return ptem;
		      }else if(ptem->getKey()<p.first)
		      {
		         ptem=ptem->rchild;
		      }else{
			  	 ptem=ptem->lchild;
			  }
			  
		 }

		 if(ptem==NULL)
		 {
		     return parent;//parent node
		 }
		 return ptem;
		 
   }
	
  bool Delete(std::pair<T,U>&p){

     Bnode <T,U>*target=search(p);
	 if(target==NULL||target->getKey()!=p.first){
	 	  return false;
	 }
    // std::cout<<target->key_value.first<<std::endl;
	 
	 if(target->lchild==NULL &&target->rchild==NULL)
	 {   
	      std::cout<<"lchild=rchild=NULL"<<"target->getkey()="<<std::endl;
		  std::cout<<"target getkey()= "<<target->getKey()<<"target parent getkey()="<<std::endl;//<<target->parent->getKey()<<std::endl;
          if(target->parent==NULL){//root node
		  	  delete target;  
		      target=NULL;
		      size-=1;
		      return true;
		  }
		  
	      if(target->getKey()<target->parent->getKey())
	      {
	         target->parent->lchild=NULL;
			
			
	      }else{
		  	   target->parent->rchild=NULL;
		  }
		  std::cout<<"lchild=rchild=NULl delete"<<std::endl;
		  size-=1;
		  delete target;
		  target=NULL;
	 }else if(target->lchild==NULL &&target->rchild)
	 {
	       if(target->parent->getKey()>target->getKey())
	       	{
	       	   target->parent->lchild=target->rchild;
	       	}else{
                target->parent->rchild=target->rchild;  
			}
			size-=1;
			delete target;
			target=NULL;
			
	 }else if(target->lchild &&target->rchild==NULL)
	  {
	       if(target->parent->getKey()>target->getKey())
	       	{
	       	   target->parent->lchild=target->rchild;
	       	}else{
                target->parent->rchild=target->rchild;  
			}
			size-=1;
			delete target;
			target=NULL;
			
	 }else{

               Bnode<T,U>*tem=target->rchild;
			   if(tem){
			   	   
			   	   if(tem->lchild==NULL)
			   	   {
			   	     std::swap(tem->getKey(),target->key_value.first);
                     std::swap(tem->getValue(),target->key_value.second);
					 target->rchild=tem->rchild;
					 tem->parent=target;
					 size-=1;
					 delete tem;
					 tem=NULL;
					 return true;
			   	   }
				   while(tem){
				   	    tem=tem->lchild;
				   }
	               std::swap(target->key_value.first,tem->getKey());
				   std::swap(target->key_value.second,tem->getValue());
                   delete tem;
				   tem=NULL;
				   size-=1;
				   return true;
				   
	
	  }
	}
	 
	 return false;  

 }

  Bnode<T,U>* succ(std::pair<T,U>&p)
  {
          Bnode <T,U>*target=search(p);
		  if(target==NULL||target->getKey()!=p.first){
		 	  return NULL;
		  }

		  Bnode<T,U>*tem=target;
		  if(tem==root){return NULL;}//root
		  if(tem->rchild==NULL){//no rchild return parent
		   	 return tem->parent;
		  }else{
		      tem=tem->rchild;
			  if(tem->lchild==NULL){
			  	 return tem;
			  }else{
			    while(tem)
			    {
			      tem=tem->lchild;
			    }
				return tem;
			  }
			  
		  }
		  		
      
  }
  
   void show(){
         if(getsize())
            travel(this->root);
   }

   void travel(Bnode<T,U>*p){
       if(p){
           travel(p->lchild);
		   std::cout<<"key="<<p->getKey()<<"value="<<p->getValue()<<std::endl;
           travel(p->rchild);
	   }
   }

};









int main() {




   binSTtree<int,std::string>tree;
   auto tem1=std::make_pair<int,std::string>(12,"fdasfds");
   tree.insert(tem1);
   auto tem2=std::make_pair<int,std::string>(14,"fdasfds");
   tree.insert(tem2);
   auto tem3=std::make_pair<int,std::string>(34,"fdasfds");
   tree.insert(tem3);
   auto tem4=std::make_pair<int,std::string>(1,"fdasfds");
   tree.insert(tem4);
   tree.show();
   tree.Delete(tem4);
   tree.show();
   tree.Delete(tem3);
   tree.show();
   tree.Delete(tem2);
   tree.show();
   tree.Delete(tem1);
   tree.show();

    return 0;
}



//http://alrightchiu.github.io/SecondRound/binary-search-tree-sortpai-xu-deleteshan-chu-zi-liao.html



