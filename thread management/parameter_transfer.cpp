#include <thread>
#include <iostream>
#include <assert.h>
using namespace  std;

void d(string const& s){
    cout<<s<<"s ：";

    // s = "rrr";
    cout<<s<<"s ：";
 return;
}
void oops(int some_param)
{
  char buffer[1024]; // 1
  sprintf(buffer, "%i",some_param); 
//   std::thread t(f,3,s); // 2
    // string s = "eee";
    std::thread t(d,buffer);
    buffer[0] = 78;
//   _sleep(100);
  cout<<"jion: "<<t.joinable()<<endl;
//   assert(t.joinable()==true);
  t.join();
  cout<<t.joinable();
//   assert(t.joinable()==false);
//   _sleep(10);

}
void m(string* s){
    // s = "rrr ";
    s->append("ggg");
    cout<<*s<< "in m";
}
void test(){
    string s("eee");
    std::thread t (m,&s);
    t.join();
    cout<<s;
}

void g(string& s){
    // s = "rrr ";
    s.append("ggg");
    cout<<s<< "in m";
}
void test_0(){
    string s("eee");
    std::thread t (g,std::ref(s));
    t.join();
    cout<<s;
}
int main(){
    // int local = 5;
    // oops(5);
    // oops_1();
    // test();
    test_0();
}
