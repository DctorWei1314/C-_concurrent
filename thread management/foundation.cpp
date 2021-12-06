#include <thread>
#include <iostream>
#include <assert.h>
void do_something(int& i){
  i++;
    // std::cout<<i;
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
      do_something(i);           // 1. 潜在访问隐患：悬空引用
    }
  }
};

void oops()
{
  int some_local_state=5;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();          // 2. 不等待线程结束
  // printf("eee");
  // _sleep(500);
  std::cout<<some_local_state;
}
                              // 3. 新线程可能还在运行
void f()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try
  {
    throw 1;
  }
  catch(int error)
  {
    std::cout<<"catch error: "<<error;
    t.join();  // 1
    std::cout<<"local var: "<<some_local_state;
    throw;
  }
  t.join();  // 2
}

class thread_guard
{
  std::thread& t;
public:
  explicit thread_guard(std::thread& t_):
    t(t_)
  {}
  ~thread_guard()
  {
    if(t.joinable()) // 1
    {
      t.join();      // 2
    }
  }
  thread_guard(thread_guard const&)=delete;   // 3
  thread_guard& operator=(thread_guard const&)=delete;
};

void oops_detach()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();          // 2. 不等待线程结束
  // std::cout<<"my_thread.joinable(): "<<my_thread.joinable()<<std::endl;
  assert(!my_thread.joinable());  
}                              // 3. 新线程可能还在运行

int main(){
  // oops();
  // f();
  oops_detach();
}
  //the source code from <thread>
  //~thread()
  //   {
  //     if (joinable())
	// std::terminate();
  //   }

//   void edit_document(std::string const& filename)
// {
//   open_document_and_display_gui(filename);
//   while(!done_editing())
//   {
//     user_command cmd=get_user_input();
//     if(cmd.type==open_new_document)
//     {
//       std::string const new_name=get_filename_from_user();
//       std::thread t(edit_document,new_name);  // 1
//       t.detach();  // 2
//     }
//     else
//     {
//        process_user_input(cmd);
//     }
//   }
// }