//Lock guard is used in case of exception or if we have 2 or more exit from critical section where we applying lock.
//Major usecase is when mutex is lock and cannot unlock due to constrains. 
//Below is the program try uncompleting the code with mutex for better understanding.

#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<chrono>

//using namespace std::literals;
using namespace std;

mutex task_mutex;

void task(const string& str){

    for(int i = 0; i < 5; ++i){
        try{
            //task_mutex.lock();
            lock_guard<mutex> lck_guard(task_mutex);
            cout<< str[0] << str[1] << str[2]<<endl;
            throw exception();
            //task_mutex.unlock();
            this_thread::sleep_for(50ms);
        }
        catch(exception& e){
            cout<< "Exception caught "<< e.what()<<'\n';
        }
    }
}

int main(){

    thread t1(task, "abc");
    thread t2(task, "def");
    thread t3(task, "xyz");

    t1.join(); 
    t2.join(); 
    t3.join();
    return 0;
}