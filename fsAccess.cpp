#pragma hdrstop
#pragma argsused

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <string>

#include "driveClass.h"
#include "fsClass.h"
#include "factoryClass.h"

int main()
{
	using namespace std;
	DWORD driveType;
	WCHAR driveList[MAX_PATH];
	WCHAR * drive;
	GetLogicalDriveStringsW(MAX_PATH, (LPWSTR)driveList);
	drive = driveList;
	driveType = GetDriveTypeW(drive);

	wcout << "Disk - [";

	while (*drive) {
		driveType = GetDriveTypeW(drive);

		if(driveType == DRIVE_REMOVABLE || driveType == DRIVE_FIXED) {
			wcout << "," << drive[0];
		}
		drive += wcslen(drive) + 1;
	}

	cout << "].";

	// Узнаем у пользователя имя интересующего диска
	wstring diskLetter = L"";
	cout << endl << "Choose: ";
	diskLetter += L"\\\\.\\";
	diskLetter += cin.get();
	diskLetter += L":";

	driveClass* driveObj = new driveClass(diskLetter.c_str());
	fsClass* fsItem = factoryClass::objCreator(driveObj);

	fsItem->getAttributes();

	fsItem->setNumOfClustersToRead();        // Сколько кластеров нужно
	fsItem->setFirstClusterToRead();        // с какого кластера начинать
	fsItem->readClusters();

	system("pause");
	delete driveObj;
	return 0;
}
