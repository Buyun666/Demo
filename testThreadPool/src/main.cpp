#include <iostream>
#include <memory>
#include <string>
#include <string.h>
#include <thread>
#include <unistd.h>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>

using namespace std;



class ThreadPool {

public:

    ThreadPool(int numThreads) : isStop(false) {
        for (int i = 0; i < numThreads; i++) {
            threads.emplace_back([this]{
                while(true) {
                    unique_lock<mutex> lock(mtx);
                    condition.wait(lock, [this](){return (!tasks.empty() || isStop);});

                    if ( isStop && tasks.empty()) {
                        return;
                    }

                    auto task = tasks.front();
                    tasks.pop();
                    lock.unlock();
                    task();
                    
                }
            });

        }

    }


    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args) {
        function<void()> task = bind(forward<F>(f), forward<Args>(args)...);
        {
            unique_lock<mutex> lock(mtx);
            tasks.emplace(move(task));
        }

        condition.notify_one();
    }


    ~ThreadPool() {

        {
            unique_lock<mutex> lock(mtx);

            isStop = true;
        }

        condition.notify_all();

       for (auto& t : threads) {
            t.join();
       }

    }

private:


    vector<thread> threads;
    queue<function<void()>> tasks;

    mutex mtx;

    condition_variable condition;

    bool isStop;
};


void show(int value) {
    std::cout << "value: " << value << std::endl;
}



int main() {

    ThreadPool tp(4);
    // for (int i = 0; i < 10; i++) {
    //     tp.enqueue([i]{
    //         cout << "task: " << i << " isRunning" << endl;

    //         this_thread::sleep_for(chrono::seconds(1));


    //         cout << "task: " << i << " isDone" << endl;
    //     });
    // }


    for (int i = 0; i < 10; i++) {
        tp.enqueue(show, i);

        cout << "task: " << i << " isRunning" << endl;

        this_thread::sleep_for(chrono::seconds(1));


        cout << "task: " << i << " isDone" << endl;
    }

    return 0;


}