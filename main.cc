
#include <iostream>
#include <map>
#include <list>
#include <stack>

#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <ctype.h>

#include <string>
#include <sstream>



#include "sigslot.h"
#include "tc_shared_ptr.h"
#include "tc_enable_shared_from_this.h"


using namespace tars;
using namespace std;
using namespace sigslot;

#define CONSTRUCTOR_DESTROY_AUTO(classname)  \
 classname(){}                               \
 ~classname(){}                     


class key_map_t {
   public:
     key_map_t(string key1,string value1):key(key1),value(value1){}
	 string key;
	 string value;
	  
   public:
   CONSTRUCTOR_DESTROY_AUTO(key_map_t)


};


class object:public TC_EnableSharedFromThis<object>{

  public:
     
     CONSTRUCTOR_DESTROY_AUTO(object)
	 object(string key1,string value1):key(key1),value(value1){}
	 TC_SharedPtr<object> getSharedptr(){
	  return sharedFromThis();
	 }
	 string toString(){
	  return key+" : "+value;
	 }
     string key;
	 string value;
     
};



class Light:public TC_EnableSharedFromThis<Light>,public has_slots<>{

public:

      virtual void turnon(bool bs){
	          if(bs){
			    std::cout<<"open light signal"<<std::endl;
			  }
	  
	  }
	  virtual void turnoff(bool bs){
	          if(bs){
			    std::cout<<"close light signal"<<std::endl;
			  }
	  
	  }
	  
	  void print(){
	     
		 std::cout<<"toString "<<std::endl;
	  
	  }
	  
};

typedef  TC_SharedPtr<object>   smart_ptr_obj;

class Light;

class button {

public:

 signal0<>print;
 signal1<bool> turnon;
 signal1<bool> turnoff;
 
 void setstatus(bool bs){
   bstatus=bs;
 }
 bool getstatus(){
  return bstatus;
 }
 
 void bind(){
 
 this->print.connect(&m_light,&Light::print);
 this->turnon.connect(&m_light,&Light::turnon);
 this->turnoff.connect(&m_light,&Light::turnoff); 
 
 }
 
 button(){}
 
 ~button(){ this->print.disconnect(&m_light);
            this->turnon.disconnect(&m_light);
			this->turnoff.disconnect(&m_light);
 }
 bool bstatus;
 Light m_light;
 

};





void getfirst3th(string &str,int ch){
       const char *pch=str.c_str();
	   size_t count=1;
	   size_t length=strlen(pch);
	   char c=0;
	   if(pch[0]=='\0')
	   {  
	   	   ch=0;
	   	   return;
	   }
	   for(auto i=0;i<length;i++)
	   { 
	        c=pch[i];
			for(auto j=i+1;j<length;j++)
			{
			   if(strcmp(&c,pch+j)==0)
			   {
			      count++;
				  if(count==3 &&isalpha(c)){
				  	  ch=c;
					  std::cout<<(char)ch;
				      
					  return;
				  }
				  
			   }
			}
			count=1;
	           
	   }
	    
//Have you ever gone shopping and

}



void getFirst3TH(string &str){
  // const char *pch=str.c_str();
   int length=str.size();
   map<char,int>m_hash;

   for(auto i=0;i<length;i++)
   {     
         if(isalpha(str.at(i))){
         auto iter=m_hash.find(str.at(i));
		 if(iter==m_hash.end())
		 {
		    m_hash.insert(pair<char,int>(str.at(i),1));//!m_hash.insert(map<char,int>::value_type())
		 }else{

               int second=iter->second;
			   if(second==3)
			   {
			       std::cout<<iter->first;
				   return;
			   }
			   iter->second+=1;
			   	
		 }
    }
   }
 

}




int fun(int a)
{  
    std::cout<<"a:"<<a<<std::endl;
    if(a==0 ||a==1){
		std::cout<<"stack layer down"<<std::endl;
		return 1;
    }
    
	return a*fun(a-1);

}


string int2str(const int &int_temp)  
{  
		stringstream stream;  
		stream<<int_temp;  
		string string_temp=stream.str();	//æ­¤å¤„ä¹Ÿå¯ä»¥ç”¨ stream>>string_temp  
		return string_temp;
} 

int str2int(string &str)
{
   return  atoi(str.c_str());
}



////////////////äºŒå‰æ ‘å®žçŽ°


struct node{
  public:
  	node(){}
	~node(){}
	node(int va):value(va),pleft(NULL),pright(NULL){
          		  
    }
  int value;
  struct node * pleft;
  struct node * pright;
  
 
};

typedef   struct node * node_type;
typedef    struct node   node_t;

class x2forktree{


public:
	
	x2forktree(){proot=NULL;size=0;}
	~x2forktree(){

	   if(proot) {
		   	delete proot;
			proot=NULL;
	        size=0;
	   	}
	   
	
	}
	x2forktree(int va){
	  if(proot==NULL){
	  	proot=new node_t(va);
	    size=1;
	  }
	}
    void addHead(int value){
          if(proot)
          {
             proot->value=value;
          }else{
             proot=new node_t(value);
		  }
	}
	node_type getroot(){return proot;}
	int getnode_value(node_type p){if(p) return p->value;}
	size_t getsize()const {return size;}
	//insert new node
	bool addNewNode(int value,node_type node){
          if(!proot){
		  	node=new node_t(value);
			size+=1;
		    proot=node;
			return true;
          	}
          std::cout<<"add newnode"<<std::endl;
		  addpri(value,node);
         
		  return true;
	}
   
	void showM1(){
           
             showM(proot); 

	}
	
	
   
private:

    void addpri(int value,node_type p){
		node_type pre=p;
		while(p){
			    pre=p;
		        if(value <=p->value)
		        {
		              p=p->pleft;
					  std::cout<<"p->pleft"<<std::endl;
		        }else{
		              p=p->pright;
					  std::cout<<"p->pright"<<std::endl;
				}
			}
		p=new node_t(value);
	    if(pre->pleft){
            pre->pright=p;
		}else{
            pre->pleft=p;
		}

		size+=1;
			
	}

	void showM(node_type p){
       if(p){
        
		 showM(p->pleft);
		 std::cout<<p->value<<std::endl;
         showM(p->pright);
	   }

	}
    node_type proot;  
	size_t size;
    



};


typedef  TC_SharedPtr< struct node> ptr_shared_node;

class y2tree{
public:
	y2tree(){}
	~y2tree(){}

	void create(){
           //23ï¼Œ@,34
		   if(!isvalid()){
		   	  return;
		   }
		   char **p=toarray();
		   

	}
	



private:
     
     bool isvalid(){
	 if(m_str_order.empty()){
	      return false;
	 	}
	 return true;
	 }


	 char ** toarray()
     {

	    int length=getchcount(',');//real length
        int max=getmaxlength(',');
		int size=m_str_order.length();
		char **parr=new[length][max];
		for(auto i=0;i<size;i++)
		{     
		      int j=m_str_order.find(',',i);
			  if(j==std::string::npos)
			  {
			     return NULL;
			  }
		      for(auto m=0,n=0;m<j;m++){
		            parr[n][m]=m_str_order.at(m);
		      }
              
			  
			  n++;
			  i=j;
		}
		
        return parr;
	 }

	 int getchcount(char c){
	      int length=m_str_order.length();
		  int count=0;
          for(auto i=0;i<length;i++)
          {
              if(m_str_order.at(i)==c){
                     count++;
			  }
          }
		  return count;

	 }

	 int getmaxlength(char spt){
          int max_length=0;
		  int max=max_length;
		  int length=m_str_order.length();
		  for(auto i=0;i<length;i++)
		  {
                if(m_str_order.at(i)!=',')
                {
                    max++;
					continue;
                }else if(m_str_order.at(i)==',')
                {
                   max_length=max;
				   max=0;
                }
                
		  }
         
          return max_length;
	 }
	 
	 
     ptr_shared_node proot;   
     string m_str_order;


};




int main(){
    
	//std::cin
    string str;
    x2forktree tree;
	int temp[]={23,12,34,5,20,34,3,23243243,234};
	for(auto i=0;i<sizeof(temp)/sizeof(int);i++)
	{
	    tree.addNewNode(temp[i],tree.getroot());
	}
	 /*

           23
         12  34
               5656 
                

	*/
  

	tree.showM1();

	//getfirst3th(str,ch);
	//fun(str2int(str));
	
	#if 0
	  button btn;
	  btn.bind();
	  btn.turnon(true);
	  
     list <string>testlist;
	 testlist.push_back("12");
	 testlist.push_back("13");
	 testlist.push_back("14");
	 testlist.push_back("15");
	 testlist.push_back("16");
	 testlist.push_back("17");
	 //! Õâ¶Î´úÂë¾Í»á±¼À££¬µü´úÆ÷Ê§Ð§µÄ³£¼ûÇé¿ö
	 #if 0
	 for(auto it=testlist.begin();it!=testlist.end();it++)
	 {
	        if((*it)=="12")
			{
			  testlist.erase(it);
			}
			 
			
	 }
	 #else 
	 
	 for(auto it=testlist.begin();it!=testlist.end();)
	 {
	        if((*it)=="12")
			{
			   testlist.erase(it++);
			}else{
			  it++;
			}
						
	 }
	  
	 #endif 
	 
	 //! ²âÊÔmapµÄÓ¦ÓÃ¡¢
	 map<string,string>info;
	 info.insert(make_pair("12","xxxxxx"));
	 info.insert(make_pair("11","xxxxxx"));
	 info.insert(make_pair("15","xxxxxx"));
	 info.insert(make_pair("13","xxxxxx"));
    
	 for(auto i=info.begin();i!=info.end();i++)				 
	 {
	       std::cout<<i->first<<std::endl;
	 }
	 
	 //11 12 13 15
	 // right way
	  for(auto i=info.begin();i!=info.end();)
	 {
	         //auto iter= info.find("15");
			 if(i->first=="15")
			 {  
			    std::cout<<"mark position"<<std::endl;
				
			    info.erase(i++); 
			 }else{
			  
			   std::cout<<i->first<<std::endl;
			    i++;
			 }
			 
			
	 }
	 
	 
	  // right way
	  for(auto i=info.begin();i!=info.end();)
	 {
	         //auto iter= info.find("15");
			 if(i->first=="15")
			 {  
			    std::cout<<"mark position"<<std::endl;
			    i=info.erase(i); 
			 }else{
			  
			   std::cout<<i->first<<std::endl;
			    i++;
			 }
			 
			
	 }
	 
	 std::cout<<"ok everything"<<std::endl;
	 
	 //test smart_ptr
	 
	 
	 TC_SharedPtr<object>ptr(new object);
	 ptr->key="df";
	 ptr->value="12";
	 std::cout<<ptr.unique()<<" "<<ptr.usecount()<<std::endl;
	 
	  TC_SharedPtr<object>ptr1=ptr->getSharedptr();
	  std::cout<<ptr1.unique()<<" "<<ptr1.usecount()<<std::endl;
	 
	 string tem=ptr->toString();
	 std::cout<<tem<<std::endl;
    
 
    //std::cout<<"hello world"<<std::endl;
#endif   

return 0;
}

