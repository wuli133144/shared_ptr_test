#include <iostream>
#include <map>
#include <list>
#include <stack>

#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <cctype>





#include "sigslot.h"
#include "tc_shared_ptr.h"
#include "tc_enable_shared_from_this.h"


using namespace std;
using namespace tars;

bool isvalid(string &str){
 
  int length=str.length();
  for(auto i=0;i<length;i++)
  {
       if(!isdigit(str[i]))
       	{
       	 return false;
       	}
  }

  return true;

}

string int2str(const int &int_temp)  
{  
		stringstream stream;  
		stream<<int_temp;  
		string string_temp=stream.str();	//此处也可以用 stream>>string_temp  
		return string_temp;
} 

int str2int(string &str)
{
   return  atoi(str.c_str());
}





typedef  struct node{

public:
	node(){}
	node(int va):left(NULL),right(NULL),value(va){}
	~node(){
		if(left){
			 delete left;
			 left=NULL;
		}
		if(right)
		{
		 delete right;
		 right=NULL;
		}
	}

	int value;
	struct node *left;
	struct node *right;
     

}node_t,*ptr_node_type;

class b2tree{


public:

   b2tree(){ptr_root=NULL;}
   ~b2tree(){}

   /*bool static create(vector<int>&ls_arr,ptr_node_type pnode,int index){
      if(ls_arr.size()<1){
	  	 return false;
	  }
	  
	  if(pnode==NULL)
	  {
	     pnode=new node_t(ls_arr[index]);

		 create(ls_arr,pnode->left,++index);
		 create(ls_arr,pnode->right,++index);
		 
	  }
   }*/


    void create(ptr_node_type * pnode){
        string temp;
        cin>>temp;
        
		if(isvalid(temp))
		{ 
             *pnode=new node_t(str2int(temp));	 
			 create(&((*pnode)->left));
             create(&((*pnode)->right));
		}else{
			 (*pnode)=NULL;
		}
		
   }


void showLMR(ptr_node_type pnode)
    {
         if(pnode)
         {
               showLMR(pnode->left);
			   std::cout<<pnode->value<<" ";
			   showLMR(pnode->right);
			   	
         }
    }

//!用栈的方法处理
void showLMR_STACK(ptr_node_type pnode)
{             
              stack<ptr_node_type>Stack; 
			  ptr_node_type temp=pnode;
			  
              while(!Stack.empty()||temp!=NULL)
              {        
                       
					   while(temp){
					      Stack.push(temp);
					      temp=temp->left;
						  
					   }

					   if(!Stack.empty())
					   	{ 
					   	   pnode=Stack.top();
						   std::cout<<pnode->value<<" ";
						   Stack.pop();
						   temp=pnode->right;
						    
					   	}
					   
					  
					   
					   
              }
}


//中序遍历
void midemu_travel(ptr_node_type pnode){

       stack<ptr_node_type>Stack; 
	   
	   while(1)
	   {
            
			 goleftbrach(Stack,pnode);
             if(Stack.empty())break;
			 
			 cout<<Stack.top()->value<<" ";
			 
			 Stack.pop();
			 pnode=pnode->right; 
			
	   }

            


}

void pre_travel(ptr_node_type node)
{
      stack<ptr_node_type>Stack;
	  while(1){
          goleftbranch1(Stack,node);
		  if(Stack.empty())break;
		  node=Stack.top();
		  Stack.pop();
		  node=node->right;
	  }
 

}


void last_travel(ptr_node_type node)
{
     stack<ptr_node_type>Stack;
	 vector<ptr_node_type>vec;
	 while(1){
         goleftbranch2(Stack,node,vec);
		 if(Stack.empty())break;
		 node=Stack.top();
		 Stack.pop();
         node=node->left;

	 }
     
	 for(auto iter=vec.rbegin();iter!=vec.rend();iter++)
	 {
	          cout<<(*iter)->value<<endl;
	 }
}

//前序遍历
void goleftbranch1(stack<ptr_node_type>&st,ptr_node_type node){
     while(node){
	 	   cout<<node->value<<" ";
		   st.push(node->right);
		   node=node->left;
     }


}

void goleftbrach(stack<ptr_node_type> &st,ptr_node_type pnode){
                while(pnode)
                {
                        st.push(pnode);
						pnode=pnode->left;
                }

}


void goleftbranch2(stack<ptr_node_type >&st,ptr_node_type node,vector<ptr_node_type>&vc)
{

    while(node){
          vc.push_back(node);
		  st.push(node->left);//压入左侧连
		  node=node->right;

	}

}

void showMLR_STACK(ptr_node_type pnode){
    stack<ptr_node_type >Stack;

	while(!Stack.empty()||pnode!=NULL)
	{
              while(pnode)
              	{ 
              	  std::cout<<pnode->value<<" ";
			      Stack.push(pnode);
				  pnode=pnode->left;
              	}

			   if(!Stack.empty())
			   	{
                    pnode=Stack.top();
					Stack.pop();
                    pnode=pnode->right;
			   }


	}

}


//!后续遍历

void travel_last(ptr_node_type pnode){
        stack<ptr_node_type>Stack;
		ptr_node_type olded=NULL;
		if(pnode) Stack.push(pnode);
		while(!Stack.empty())
		{     pnode=Stack.top();
		
		 if((pnode->left==NULL &&pnode->right==NULL)||((pnode->left==olded||pnode->right==olded)&&olded!=NULL)/*叶子节点*/)
			  {
			      cout<<pnode->value<<" ";
				  olded=Stack.pop();
				  
			  }
		else{
		      if(pnode->right)
		      {
		          Stack.push(pnode->right);
				  
		      }
			  if(pnode->left)
			  {   
			      Stack.push(pnode->left);
			  }
		} 
		}

}

 
   ptr_node_type ptr_root;
  

};




#define   type_BinNode(T)        binnode<T>*

template <typename T> 
class binnode{
  public:
    T data;
	int color;
	int height;
	type_BinNode(T) parent,*lchild,*rchild;
     
	binnode(T e,binnode<T> *p){
	       	 this->data=e;
			 this->lchild=NULL;
			 this->rchild=NULL;
			 this->parent=p;
			
	 }
	 

	 binnode<T> * insertLChild(T e)
	{ 
	          lchild=new  binnode<T>(e,this);
			  return lchild;
	}

	 binnode<T>* insertRChild(T e)
	{
	          rchild=new binnode<T>(e,this);
			  return rchild;
	}

	size_t size(){

	    size_t sz=1;
	    if(lchild==NULL&&rchild==NULL)
	   	{
	   	  return 1;
	   	}
        if(lchild)
        {
          sz+=lchild->size();
        }
		if(rchild)
		{
		  sz+=rchild->size();
		}
		return sz;	


	}
	
    size_t getheight()
	{
	        int max1=0,max2;
			int maxr=0;
			if(lchild)
			{
			    max1=max1+lchild->getheight()+1;
				maxr=max1;
			}
			if(rchild)
			{
			    max1=max1+rchild->getheight()+1;
			}

			return  maxr>max1? maxr : max1;
				
			
			
	}
	
	void travel_left(){                    
           pri_travel_l(this);
	}

	void travel_medium()
	{
	    pri_travel_m(this);
	}

	void travel_right(){
         pri_travel_r(this);
   
	}

	void go()
	{
	   last_travel(this);
	}

void last_travel(binnode<T>* node)
{
     stack<binnode<T>*>Stack;
	 vector<binnode<T>*>vec;
	 cout<<"xxxx"<<endl;
	 while(1){
         goleftbranch2(Stack,node,vec);
		 if(Stack.empty())break;
		 node=Stack.top();
		 Stack.pop();
         node=node->lchild;

	 }
     
	 for(auto iter=vec.rbegin();iter!=vec.rend();iter++)
	 {
	          cout<<(*iter)->data<<endl;
	 }
}

//前序遍历
void goleftbranch1(stack<binnode<T>*>&st,binnode<T>* node){
     while(node){
	 	   cout<<node->data<<" ";
		   st.push(node->rchild);
		   node=node->lchild;
     }
}


void goleftbrach(stack<binnode<T>*> &st,binnode<T>* pnode){
                while(pnode)
                {
                        st.push(pnode);
						pnode=pnode->lchild;
                }

}


void goleftbranch2(stack<binnode<T>* >&st,binnode<T>* node,vector<binnode<T>*>&vc)
{

    while(node){
          vc.push_back(node);
		  st.push(node->lchild);//压入左侧连
		  node=node->rchild;
	}

}

private:

    void pri_travel_l(binnode<T>*o)
	{
	    if(o)
	    {  
	       cout<<o->data<<" ";
	       pri_travel_l(o->lchild);
		   
		   pri_travel_l(o->rchild);
	    }
	}


	 void pri_travel_m(binnode<T>*o)
	{
	    if(o)
	    {
	       pri_travel_m(o->lchild);
		   cout<<o->data<<" ";
		   pri_travel_m(o->rchild);
	    }
	}

	  void pri_travel_r(binnode<T>*o)
	{
	    if(o)
	    {
	       pri_travel_r(o->lchild);
		  
		   pri_travel_r(o->rchild);
		    cout<<o->data<<" ";
	    }
	}
};







#if 0
	  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
      };

	  
	class Solution {
	public:
		int size(ListNode *l){
             int sz=0;
			 while(l)
			 {
			      sz+=1;
				  l=l->next;
			 }

             return sz;
		}
		
		ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
               int add_res_temp;

			   int l1_len=size(l1);
			   int l2_len=size(l2);
			   int max_len=l1_len>=l2_len ?l1_len:l2_len;
			   ListNode *temp=NULL,*temp1=NULL;
			   int flag=0;
               ListNode *newlist=(struct ListNode *)malloc(sizeof(struct ListNode)*max_len);//new ListNode();ok
               
               for(int j=0;j<max_len-1;j++)
               {
                     newlist[j]->next=newlist[j+1];
               }

			     temp=l1;
				 temp1=l2;
               for(int i=0,j=0;i<max_len;i++,j++)
               {
                    if(l1_len==max_len){
                            if(j<=l2_len)
                            {
                                
								  add_res_temp=temp->val+temp1->val+flag;
								  
								  if(add_res_temp>=10)
								  {   
								       
								       newlist[j]->val=add_res_temp%10;   
									   flag=1;
								  }else{
								  	   newlist[j]->val=add_res_temp;
									   flag=0;
								  }
								  temp=temp->next;
								  temp1=temp1->next;
								  
                                  
							}else{
                                 
                                   add_res_temp=temp->val+flag;   
								    if(add_res_temp>=10)
								   {   
								       
								       newlist[j]->val=add_res_temp%10;   
									   flag=1;
								   }else{
								  	   newlist[j]->val=add_res_temp;
									   flag=0;
								   }
								    temp=temp->next;

							}


					
					}else{

                                  if(j<=l1_len)
                            {
                                
								  add_res_temp=temp->val+temp1->val+flag;
								  
								  if(add_res_temp>=10)
								  {   
								       
								       newlist[j]->val=add_res_temp%10;   
									   flag=1;
								  }else{
								  	   newlist[j]->val=add_res_temp;
									   flag=0;
								  }
								  temp=temp->next;
								  temp1=temp1->next;
								  
                                  
							}else{
                                 
                                   add_res_temp=temp->val+flag;   
								    if(add_res_temp>=10)
								   {   
								       
								       newlist[j]->val=add_res_temp%10;   
									   flag=1;
								   }else{
								  	   newlist[j]->val=add_res_temp;
									   flag=0;
								   }
								    temp=temp->next;

							}



					}
			   
               }
			   
			   
			  return newlist;   
		   
		}
	};




#endif


class Solution {
public:
   /*
    bool ishuiwen(string &str)
    {
         stack<char>Stack1,Stack2;
		 
		 const char *p=str.data();
		 int len=str.length();
		 bool ret=false;
		 for(int i=0;i<len/2;i++)
		 {
		     Stack1.push(p[i]);
		 }
         for(int i=len-1;i>len/2;i--)
         {
             Stack2.push(p[i]);
         }

		 for(int i=0;i<len/2;i++)
		 {
		     if(Stack1.top()==Stack2.top())
		     {
		       Stack1.pop();
			   Stack2.pop();
			   
		     }else{
			 	 return ret=false;
			 }
		 }
        
		return ret=true;
		 
    }*/

      
     bool ishuiwen(string &str)
    {
              int len=str.length();
			  if(len==1){return true;}
			    if(len&0x01){
			      int i=len/2;
				  for( int j=i;i>0 &&j<len-1;i--,j++)
				  {
				             if(str[i-1]!=str[j+1])
				             	{
				             	  return false;
				             	}
				  }
				  return true;
			    }else{
                         
				   int i=len/2;
				  for( int j=i;i>0 &&j<len-1;i--,j++)
				  {
				             if(str[i-1]!=str[j])
				             	{
				             	  return false;
				             	}
				  }
				  return true;   
				}
				
    }

    bool ishuiwen1(string &str,int i,int len)
    {         bool bret=false;
              if(i>=len/2-1){
			  	  if(str[i]==str[len-i])
				  	return true;
				  return false;
              }
			  if(str[i]==str[len-i-1])
			  { 
			      bret=ishuiwen1(str,i+1,len);
			  }else{
			  	  bret=false;
			  }
			  return bret;
			  
    }


    string longestPalindrome(string s) {
             stack<char>Stack;
			 string::size_type len=s.length();
			 int max_length,max=0;
			 string substr;
			 string prety_str;
			 for(string::size_type i=0;i<len;i++)
			 {   
			     for(int j=1;j<=len-i;j++){

					substr=s.substr(i,j);
					if(ishuiwen(substr))
					{
					   max_length=substr.length();
					}
						`
					
			     }

				 if(max <max_length){
				    max=	max_length;
					prety_str=substr;
				 }
				 
				    
			 }

			 cout<<prety_str<<endl;
			 
    }
};




int main()

{

#if 0
binnode<int> bin_tree(2,NULL);
binnode<int>*p=bin_tree.insertLChild(5);
p=p->insertLChild(34);
p=p->insertLChild(33);


p=p->insertLChild(37);
p=p->insertRChild(334);

p=p->insertLChild(3480);

#if 0
p=p->insertLChild(34);

p=p->insertLChild(34);

p=p->insertLChild(34);

p=p->insertLChild(34);

p=p->insertLChild(34);

p=p->insertLChild(34);
p=p->insertRChild(34);
p=p->insertRChild(34);
p=p->insertRChild(34);
p=p->insertRChild(34);

p->insertLChild(39);

#endif 

bin_tree.insertRChild(10);
bin_tree.go();

cout<<"xxxx"<<endl;




#endif

// b2tree tree;
// tree.create(&tree.ptr_root);
// tree.last_travel(tree.ptr_root);


 return 0;
 
}




  
