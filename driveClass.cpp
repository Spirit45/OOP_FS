#include "driveClass.h"

using namespace std;

driveClass::driveClass(const WCHAR *fileName) {

	if ((fileHandle = CreateFileW(fileName,
		GENERIC_READ,       					// Режим доступа
		FILE_SHARE_READ | FILE_SHARE_WRITE,     // Режим совместной работы
		NULL,       							// Атрибуты безопасности
		OPEN_EXISTING,      					// Способ открытия
		0,      								// Флаги и атрибуты
		NULL)) == INVALID_HANDLE_VALUE)	{

		exit(GetLastError());

		system("pause");
		exit(-1);
	}
    cout << "Connection passed successfully" << endl;
}

HANDLE driveClass::getFileHandle(){
	return fileHandle;
}

BYTE *driveClass::readRecords(LARGE_INTEGER sectorOffset, DWORD bytesPerCluster, DWORD numOfClustersToRead){

	BYTE* buffer = new BYTE;
	clusterIterator * iterator = new clusterIterator(fileHandle, sectorOffset, bytesPerCluster, numOfClustersToRead);
	for(iterator->First(); !iterator->IsDone(); iterator->Next())
	{
		buffer = iterator->GetCurrent();
	}
	return buffer;
	delete[] buffer;
	delete iterator;
}

BYTE *driveClass::readEvenRecords(LARGE_INTEGER sectorOffset, DWORD bytesPerCluster, DWORD numOfClustersToRead){

	cout << "This is decorator" << endl;
	BYTE* buffer = new BYTE;
	clusterDecorator * Decorator = new clusterDecorator(fileHandle, sectorOffset, bytesPerCluster, numOfClustersToRead);
	for(Decorator->First(); !Decorator->IsDone(); Decorator->Next())
	{
		buffer = Decorator->GetCurrent();
	}

	return buffer;
	delete[] buffer;
    delete Decorator;
}

void driveClass::printHexBuffer(BYTE * buffer, DWORD bufferSize){
	cout << "[----------------------   ----------------------]" << endl;
	for (int i = 1; i < bufferSize + 1; i++) {
		cout << hex << setw(2) << setfill('0') << DWORD(buffer[i - 1]) << " ";

		if (i % 16 == 0) {
			cout << endl;
		}
		else if (i % 8 == 0)
		{
			cout << "  ";
		}
	}
	cout << "[----------------------   ----------------------]" << endl;
    delete[] buffer;
}

driveClass::~driveClass() {
	CloseHandle(fileHandle);
}
