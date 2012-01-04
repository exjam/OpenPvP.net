/*
Injects dll into LoL processes
*/
#include <Windows.h>
#include <iostream>

void PrintLastError(){
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);

	printf("%s\n", lpMsgBuf);
	LocalFree(lpMsgBuf);
}

bool InjectDLL(HANDLE hProcess, const char* dll){
	DWORD dwWritten;
	LPVOID pStringInRemoteProcess;

	if(!hProcess){
		PrintLastError();
		return false;
	}

	pStringInRemoteProcess = VirtualAllocEx(hProcess, 0, strlen(dll) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if(pStringInRemoteProcess == NULL){
		PrintLastError();
		return false;
	}

	WriteProcessMemory(hProcess, pStringInRemoteProcess, dll, strlen(dll) + 1, &dwWritten);
	if(dwWritten != strlen(dll)+1){
		PrintLastError();
		return false;
	}

	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll") , "LoadLibraryA"), pStringInRemoteProcess, 0, 0);
	return true;
}

int main(int argc, char** argv){
	if(argc < 3){
		printf("Usage: %s <target> <dll>\n", argv[0]);
		printf("\ttarget = game | pvpnet\n");
		printf("\tdll = path to dll\n");
		printf("Example:\n\t%s pvpnet airlog.dll\n", argv[0]);
		return 0;
	}

	const char* target = argv[1];
	const char* dll = argv[2];
	
	HWND hwnd = NULL;
	if(_stricmp(target, "game") == 0){
		while(!(hwnd = FindWindow("LeagueOfLegendsWindowClass", NULL)))
			Sleep(50);
	}else{
		while(!(hwnd = FindWindow(NULL, "PVP.net Client")))
			Sleep(50);
	}

	DWORD id;
	if(!GetWindowThreadProcessId(hwnd, &id) || !id){
		printf("Could not get process ID!\n");
		return -1;
	}

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
	if(!handle){
		printf("Could not get process handle!\n");
		return -1;
	}

	char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);
	
	char* inject = new char[MAX_PATH + strlen(dll) + 2];
	sprintf_s(inject, MAX_PATH + strlen(dll) + 2, "%s/%s", path, dll);

	if(!InjectDLL(handle, inject)){
		printf("Could not inject '%s'!\n", inject);
		return -1;
	}

	printf("Injected %s!\n", dll);

	return 0;
}
