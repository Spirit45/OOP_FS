#pragma once

#include "iteratorClass.h"

#include <windows.h>
#include <iostream>

 class clusterDecorator : public clusterIterator
{
public:
	clusterDecorator(HANDLE fileHandle, LARGE_INTEGER sectorOffset, DWORD BytesPerCluster, DWORD numOfClustersToRead);
	virtual void Next() override;
	~clusterDecorator();
};
