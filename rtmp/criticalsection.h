#pragma once

#include "lock.h"
#include <windows.h>

class CriticalSection : public Lock {
public:
	CriticalSection(){
		InitializeCriticalSection(&mSection);
	}

	virtual ~CriticalSection(){
		DeleteCriticalSection(&mSection);
	}
	
	virtual void lock(){
		EnterCriticalSection(&mSection);
	}

	virtual void unlock(){
		LeaveCriticalSection(&mSection);
	}

private:
	CRITICAL_SECTION mSection;
};
