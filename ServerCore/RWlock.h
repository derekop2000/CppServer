#pragma once
class RWlock
{
public:
	enum : uint32
	{
		MAX_SPIN_CNT = 7'777,
		SLEEP_TIME = 7'777,
		EMPTY_FLAG = 0x00000000,
		WRITE_FLAG = 0xFFFF0000,
		READ_FLAG = 0x0000FFFF,

	};

	void WriteLock();
	void WriteUnLock();
	void ReadLock();
	void ReadUnLock();

private:
	atomic<uint32> _flag = EMPTY_FLAG;
	uint32 _writeCnt = 0;
};

