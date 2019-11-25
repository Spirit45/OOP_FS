#include "decoratorClass.h"

using namespace std;

clusterDecorator::clusterDecorator(HANDLE fileHandle, LARGE_INTEGER sectorOffset, DWORD bytesPerCluster, DWORD numOfClustersToRead) : clusterIterator(fileHandle, sectorOffset, bytesPerCluster, numOfClustersToRead)
{
	clustersReaded = 0;
}

void clusterDecorator::Next()
{
	sectorOffset.QuadPart -= (bytesPerCluster + bytesPerCluster);
	sectorOffset.QuadPart < 0 ? sectorOffset.QuadPart = 0 : sectorOffset.QuadPart;
	clustersReaded += 1;
}
