#include <Windows.h>
#include <process.h>

template<typename ActionType>
unsigned Launch(void * context)
{
	(* (ActionType *)context)();
	return 0;
}

template<typename ActionType, unsigned NumberOfActions>
void ForEach(ActionType actions[], unsigned timeout)
{
	void * references[NumberOfActions];
	for (unsigned index = 0; index < NumberOfActions; ++index) references[index] = ((void *)_beginthreadex(nullptr, 0, Launch<ActionType>, actions + index, 0, nullptr));
	for (unsigned index = 0; index < NumberOfActions; ++index) WaitForSingleObjectEx(references[index], timeout, 0);
}