#include "pch.h"
#include "RWlock.h"

void RWlock::WriteLock()
{
	uint32 lockThreadId = (_flag & WRITE_FLAG) >> 16;
	if (LThreadId == lockThreadId)
	{
		_writeCnt++;
		return;
	}
	uint32 expected = EMPTY_FLAG;
	uint32 desired = (LThreadId << 16) & WRITE_FLAG;
	while (true)
	{
		for (int i = 0; i < MAX_SPIN_CNT; i++)
		{
			if (_flag.compare_exchange_strong(expected, desired) == true)
			{
				_writeCnt++;
				break;
			}
		}
		this_thread::sleep_for(0s);
	}
}

void RWlock::WriteUnLock()
{
	if (--_writeCnt == 0)
	{
		_flag.store(EMPTY_FLAG);
	}
}

void RWlock::ReadLock()
{
	uint32 lockThreadId = (_flag & WRITE_FLAG) >> 16;
	if (LThreadId == lockThreadId)
	{
		_flag.fetch_add(1);
		return;
	}
	while (true)
	{
		for (int i = 0; i < MAX_SPIN_CNT; i++)
		{
			uint32 expected = (_flag.load() & READ_FLAG);
			if(_flag.compare_exchange_strong(expected, expected + 1))
				return;
		}
		this_thread::sleep_for(0s);
	}
}

void RWlock::ReadUnLock()
{
	_flag.fetch_add(-1);
}
