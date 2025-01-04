#include "pch.h"

CoreGlobal core;

int main()
{
	for (int i = 0; i < 5; i++)
	{
		GThreadManager->Launch([]()
			{
				while (true)
				{
					cout << "i am " << LThreadId << "\n";
					this_thread::sleep_for(1000ms);
				}
			});
	}

	while (true)
	{
		;
	}
	GThreadManager->Join();
}