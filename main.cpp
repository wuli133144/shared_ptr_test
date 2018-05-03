
#include <iostream>
#include <map>#include <list>
#include <string>
#include "tc_shared_ptr.h"
#include "tc_enable_shared_from_this.h"


using namespace tars;
using namespace std;

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
	 TC_SharedPtr<object>getSharedptr(){
	  return sharedFromThis();
	 }
	 string toString(){
	  return key+" : "+value;
	 }
     string key;
	 string value;
     
};


typedef  TC_SharedPtr<object>   smart_ptr_obj;


int main(){

     list <string>testlist;
	 testlist.push_back("12");
	 testlist.push_back("13");
	 testlist.push_back("14");
	 testlist.push_back("15");
	 testlist.push_back("16");
	 testlist.push_back("17");
	 //! 这段代码就会奔溃，迭代器失效的常见情况
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
	 
	 
	 
	 
	 //! 测试map的应用、
     
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
  

return 0;
}

