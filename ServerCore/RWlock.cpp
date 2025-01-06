#include "pch.h"
#include "RWlock.h"

void RWlock::WriteLock()
{
	uint32 lockThreadId = (_flag & WRITE_FLAG) << 16;
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
	}
}

void RWlock::WriteUnLock()
{
}

void RWlock::ReadLock()
{
}

void RWlock::ReadUnLock()
{
}
