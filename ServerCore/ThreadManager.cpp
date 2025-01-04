#include "pch.h"
#include "ThreadManager.h"

ThreadManager::ThreadManager()
{
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(function<void(void)> callBack)
{
	lock_guard<mutex> guard(_lock);

	_threads.push_back(thread([=]()
		{
			this->InitTLS();
			callBack();
			this->DestroyTLS();
		}));
}

void ThreadManager::Join()
{
	for (thread& t : _threads)
	{
		if (t.joinable())
			t.join();
	}
	_threads.clear();
}

void ThreadManager::InitTLS()
{
	static atomic<uint32> ThreadId = 1;
	LThreadId = ThreadId++;
}

void ThreadManager::DestroyTLS()
{
}
