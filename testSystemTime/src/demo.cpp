#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include "sys/time.h"

// 参考链接https://blog.csdn.net/www_dong/article/details/134520557

typedef struct 
{
    int year;                      
    int month;                   
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;               
}Date_Time;

int64_t GetSysTime() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t current_time = tv.tv_sec * 1000000 + tv.tv_usec;
    return current_time;
}

void Get_Date(long long time_i, Date_Time &date_time_o) 
{
    int seconds = time_i / 1000000 + 8 * 3600;// time zone +8
    // int seconds = time_i + 8 * 3600;// time zone +8
    int days = seconds / 86400;
    int year = 1970 + (int) (days / 1461) * 4; // recycled in 4 years = 1461 days
    int month = 0;
    int day = days % 1461;
    day = day > 730 ? day - 1 : day;
    year += (int) (day / 365);
    day = day % 365;
    int monthday[]{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    for (int i = 0; i < 13; i++) {
        if (day < monthday[i + 1]) {
            month = i + 1;
            day = day - monthday[i] + 1;
            break;
        }
    }

    int sec = seconds % 86400;
    int hour = (int) (sec / 3600);
    int minute = (int) (sec % 3600 / 60);
    int second = sec % 60;
    int millisecond = time_i % 1000000;

    date_time_o.year = year;
    date_time_o.month = month;
    date_time_o.day = day;
    date_time_o.hour = hour;
    date_time_o.minute = minute;
    date_time_o.second = second;
    date_time_o.millisecond = millisecond;
}

int main()
{
	    // 创建两个时间点
    	auto start = std::chrono::steady_clock::now();
    	std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟5s耗时操作
    	auto end = std::chrono::steady_clock::now();

    	// 计算时间间隔
    	std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    	// 输出时间间隔
    	std::cout << "Elapsed time: " << duration.count() << " seconds\n";

        // 使用系统时钟获取当前时间点
        auto currentTime = std::chrono::system_clock::now();
        auto currentTime_s = std::chrono::time_point_cast<std::chrono::seconds>(currentTime);
        auto currentTime_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);
        auto currentTime_micro = std::chrono::time_point_cast<std::chrono::microseconds>(currentTime);
        auto currentTime_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(currentTime);
        auto valueS = currentTime_s.time_since_epoch().count();
        auto valueMS = currentTime_ms.time_since_epoch().count();
        auto valueMicroS = currentTime_micro.time_since_epoch().count();
        auto valueNS = currentTime_ns.time_since_epoch().count();

        std::cout << "Seconds: " << valueS << std::endl;
        std::cout << "Milliseconds: " << valueMS << std::endl;
        std::cout << "Microseconds: " << valueMicroS << std::endl;
        std::cout << "Nanoseconds: " << valueNS << std::endl;

        // 将当前时间格式化为时间字符串
        std::time_t t = std::chrono::system_clock::to_time_t(currentTime);
        std::cout << "CurrentTime: " << std::put_time(std::localtime(&t), "%F %T") << std::endl;

        int64_t currentSystemTime = GetSysTime();
        std::cout << "currentSystemTime: " << currentSystemTime << std::endl;

        Date_Time dateTime;

        Get_Date(currentSystemTime, dateTime);

        std::cout << "year: " << dateTime.year << ";"
                    << "month: " << dateTime.month << ";"
                    << "day: " << dateTime.day << ";"
                    << "hour: " << dateTime.hour << ";"
                    << "minute: " << dateTime.minute << ";"
                    << "second: " << dateTime.second << ";"
                    << std::endl;

    
	    return 0;
}
