// kepcoReg.cpp : Defines the entry point for the console application.
/*
1. UNICODE 기능을 삭제 함 
2. _CRT_SECURE_NO_WARNINGS define 을 추가 함
3. 구성 속성 -> 링커 -> 매니페스트 파일" 이동한뒤, UAC 실행 수준을 아래와 같이
requireAdministrator(/level='requireAdministrator')
*/
//
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "tlhelp32.h"

#include <iostream>
#include <thread> 
#include <ctime>


int getLastIndex(char *s, char c)
{
	int length;
	int i; //loop counter
	//get length
	length = strlen(s);

	//run loop from length-1 to 0
	for (i = (length - 1); i >= 0; i--)
	{
		//compare character with each charater of string
		if (s[i] == c)
			return i; //character found return index
	}
	//if character not found return -1
	return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{

	HKEY hKey = NULL;

	char src[1000];
	char path[1000];
	char dest[1000];

	/* HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Run */
	char regSubKeyPath[1000] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	char valueName[100] = "kepcoMe";

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, regSubKeyPath, 0, KEY_ALL_ACCESS, &hKey)
		== ERROR_SUCCESS){
		printf("++++++++++++++++++++++++++++++++++++++++++++11");
		// 키를 오픈하는데 성공했습니다.
		// 이제 이 키를 이용해 레지스트리를 마음대로 ...
	}
	else 	{
		// 키 오픈에 실패했네요....
		printf("++++++++++++++++++++++++++++++++++++++++++++12");
	}

	::GetModuleFileName(NULL, path, 1000);       //현재실행파일이름+경로알아내기


	char fileNm[] = "kepcoMe.exe";
	memset(path, 0, sizeof(char)* 1000);
	::GetModuleFileName(NULL, src, 1000);       //현재실행파일이름+경로알아내기
	int index = getLastIndex(src, '\\');
	// strncpy(destStr, srcStr, sizeof(destStr)-1);
	strncpy(path, src, index + 1);
	strcat(path, fileNm);
	// MessageBoxA(0, path, "ff", MB_OK);




	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, regSubKeyPath, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) == ERROR_SUCCESS)
	{
		::RegSetValueEx(hKey, valueName, 0, REG_SZ, (BYTE*)path, strlen(path));
		::RegCloseKey(hKey);
		printf("성공\n");
		return 1;
	}
	printf("실패\n");
	return 0;
}

