#pragma once

#include "Runtime/Core/Public/Async/AsyncWork.h"

class FSVONFindPathTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FSVONFindPathTask>;

public:
	FSVONFindPathTask(ASVONVolume& aVolume, UWorld* aWorld, const SVONLink aStart, const SVONLink aTarget, FNavPathSharedPtr* oPath, TQueue<int>& aQueue, TArray<FVector>& aDebugOpenPoints) :
		myVolume(aVolume),
		myWorld(aWorld),
		myStart(aStart),
		myTarget(aTarget),
		myPath(oPath),
		myOutQueue(aQueue),
		myDebugOpenPoints(aDebugOpenPoints)
	{}

protected:
	ASVONVolume& myVolume;
	UWorld* myWorld;

	SVONLink myStart;
	SVONLink myTarget;
	FNavPathSharedPtr* myPath;

	TQueue<int>& myOutQueue;
	TArray<FVector>& myDebugOpenPoints;

	void DoWork()
	{
		SVONPathFinderSettings settings;

		SVONPathFinder pathFinder(myWorld, myVolume, settings);

		int result = pathFinder.FindPath(myStart, myTarget, myPath);

		myOutQueue.Enqueue(result);
		
	}

	// This next section of code needs to be here.  Not important as to why.

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FSVONFindPathTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};