#include <boost/thread/thread.hpp> 
#include <boost/thread/mutex.hpp> //定义锁
#include <boost/thread/shared_mutex.hpp>
#include <iostream>
#include <boost/chrono.hpp> 
#include <boost/thread/condition_variable.hpp>

#include <unistd.h>
using namespace std;

boost::mutex mlock; //使用的锁


int num = 100;
bool isTimeOut_ = false;
boost::mutex mutex_;
boost::chrono::time_point<boost::chrono::system_clock> startTime_;

boost::chrono::time_point<boost::chrono::system_clock> endTime_;

boost::condition_variable cv_;

static const unsigned int MILISEC_IN_SEC = 1000;

int countTarget = 10;

int currentCount = 0;

void updataCount(int & count) 
{
	count += 1;
}


void checkCount(int &count, const double& timeOut) 
{
	startTime_ = boost::chrono::system_clock::now();
	// endTime_ = boost::chrono::system_clock::now();
	// double elapsedMilliseconds = boost::chrono::duration_cast<boost::chrono::milliseconds>(endTime_ - startTime_).count();
	// double elapsedSeconds      = elapsedMilliseconds / 1000.0;

	while(count != countTarget && (boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - startTime_).count() < timeOut * MILISEC_IN_SEC)) {
		updataCount(count);
		std::cout <<  "current_count: " << count << std::endl;
		sleep(1);

	}

	if (boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - startTime_).count() > timeOut * MILISEC_IN_SEC) {
		isTimeOut_ =true;
	}

	std::cout << "isTimeOut_" << isTimeOut_ << std::endl;

	cv_.notify_one();

}


bool waitUntilCountReached(int &count, const double& timeOut) 
{
	isTimeOut_ = false;
	boost::unique_lock<boost::mutex> lck(mutex_);
	boost::thread t1(boost::bind(checkCount, count, boost::ref(timeOut)));

	if ((cv_.wait_for(lck, boost::chrono::milliseconds(static_cast<uint64_t> (timeOut * MILISEC_IN_SEC))) == boost::cv_status::timeout) == isTimeOut_)
    {
        if (t1.joinable()) t1.join();

		std::cout<< "*****************" << std::endl;

        return true;
    }
    else
    {
        if (t1.joinable()) t1.join();

        return false;
    }


	
	return false;
}

int main(int argc, char* argv[]) 
{ 
	bool flag = waitUntilCountReached(currentCount, 11);

	std::cout << "flag: " << flag << std::endl;

	return 0; 
}