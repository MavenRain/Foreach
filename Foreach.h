#include <Windows.h>
#include <process.h>

template<typename ActionType>
void Launch(PTP_CALLBACK_INSTANCE instance, void * context, PTP_WORK work)
{
	(* (ActionType *)(context))();
}

template<typename ActionType, unsigned NumberOfActions>
void ForEach(ActionType actions[], unsigned timeout)
{
	PTP_WORK workItems[NumberOfActions];
	for (unsigned index = 0; index < NumberOfActions; ++index) workItems[index] = CreateThreadpoolWork(Launch<ActionType>, actions + index, nullptr);
	for (unsigned index = 0; index < NumberOfActions; ++index) SubmitThreadpoolWork(workItems[index]);
	for (unsigned index = 0; index < NumberOfActions; ++index) WaitForThreadpoolWorkCallbacks(workItems[index], false);
}