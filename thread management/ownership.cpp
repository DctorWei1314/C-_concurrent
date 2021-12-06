#include <thread>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
void some_function(){

};
void some_other_function(){

};
void test(){
    std::thread t1(some_function);            // 1
std::thread t2=std::move(t1);            // 2
t1=std::thread(some_other_function);    // 3
std::thread t3;                            // 4
t3=std::move(t2);                        // 5
cout<<"endl";
t1=std::move(t3);                        // 6 赋值操作将使程序崩溃
cout<<"endl";
}

struct func
{
  int& i;
  func(int& i_) : i(i_) {}
  void operator() ()
  {
    for (unsigned j=0 ; j<1000000 ; ++j)
    {
      // _sleep(1);
    //   do_something(i);           // 1. 潜在访问隐患：悬空引用
    i++;
    // cout<<i;
    }
  }
};
class scoped_thread
{
  std::thread t;
public:
  explicit scoped_thread(std::thread t_):                 // 1
    t(std::move(t_))                                      
  {
    if(!t.joinable())                                     // 2
      throw std::logic_error("NO_THREAD");
  }
  ~scoped_thread()
  {
    t.join();                                            // 3
  }
  scoped_thread(scoped_thread const&)=delete;
  scoped_thread& operator=(scoped_thread const&)=delete;
};


void test1()
{
  int some_local_state = 0;
//   scoped_thread t(std::thread(func(some_local_state)));    // 4
//   do_something_in_current_thread();
   func my_func(some_local_state);
   std::thread t(std::thread(func(some_local_state)));
   cout<<some_local_state; 
}                                                        // 5

void do_work(unsigned id){

};

void f()
{
  std::vector<std::thread> threads;
  for(unsigned i=0; i < 20; ++i)
  {
    threads.push_back(std::thread(do_work,i)); // 产生线程,移动敏感
  } 
  std::for_each(threads.begin(),threads.end(),
                  std::mem_fn(&std::thread::join)); // 对每个线程调用join()
}
int main(){
    // test();
    test1();
}