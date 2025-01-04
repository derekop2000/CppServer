#pragma once

#include<functional>
#include<thread>
#include<mutex>
#include<vector>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void Launch(function<void(void)> callBack);
	void Join();

	void InitTLS();
	void DestroyTLS();

private:
	mutex _lock;
	vector<thread> _threads;
};

