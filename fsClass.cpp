#include "fsClass.h"
#include "driveClass.h"

using namespace std;

fsClass::fsClass(driveClass* driveObj){
	this->driveObj = driveObj;
}


void fsClass::getAttributes(){
	cout << "File system name:" << getFsName() << endl
		 << "Bytes per sector:" << bytesPerSector << endl
		 << "Sectors per cluster:" << sectorsPerCluster << endl
		 << "Bytes per cluster:" << getBytesPerCluster() << endl
		 << "Total clusters:" << getTotalClusters() << endl;
}

DWORD fsClass::getBytesPerCluster(){
	return bytesPerSector * sectorsPerCluster;
}


void fsClass::setNumOfClustersToRead(){
	tryAgainEnterNumOfClusters:
	cout << "How many clusters do you want to read?" << endl;
	cin >> numOfClustersToRead;
	if (numOfClustersToRead == 0) {
		cout << "Nothing to print." << endl;
		goto tryAgainEnterNumOfClusters;
	}
}

void fsClass::setFirstClusterToRead(){
	tryAgainEnterFirstCluster:
	cout <<	"Where to start? Available clusters: [" << getFirstClusterNum() << ", "
		 << getTotalClusters() - 1 + getFirstClusterNum() << "]" << endl;
	cin >> firstClusterToRead;
	if ((firstClusterToRead < getFirstClusterNum() || firstClusterToRead >= (getTotalClusters() + getFirstClusterNum()))) { 
		goto tryAgainEnterFirstCluster;
	}
	firstClusterToRead += getFsClustersOffset() - getFirstClusterNum();
}


void fsClass::readClusters(){
		DWORD bytesToRead = getBytesPerCluster() * numOfClustersToRead;
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = firstClusterToRead * getBytesPerCluster();
		numOfClustersToRead == 1 ?
		cout << endl << "Sector by offset:" << sectorOffset.QuadPart << endl:
		cout << endl << "Sectors by offset:" << sectorOffset.QuadPart << endl;
		BYTE *dataBuffer = driveObj->readRecords(sectorOffset, getBytesPerCluster(), numOfClustersToRead);
		driveObj->printHexBuffer(dataBuffer, bytesToRead);
        delete[] dataBuffer;
		BYTE *dataEvenBuffer = driveObj->readEvenRecords(sectorOffset, getBytesPerCluster(), numOfClustersToRead);
		driveObj->printHexBuffer(dataEvenBuffer, bytesToRead);
		delete[] dataEvenBuffer;
}

fsClass::~fsClass(){
	delete driveObj;
}
