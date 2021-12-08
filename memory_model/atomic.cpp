#include<atomic>
#include<iostream>
using namespace std;
int main(){
    std::atomic_flag f = ATOMIC_FLAG_INIT;
    std::atomic<int> a;
    cout<<a.is_lock_free();
    std::atomic<bool> b;
    cout<<b.is_lock_free();
}