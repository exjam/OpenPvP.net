/* Logs RTMP packets sent from adobe air before SSL encryption */

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

FILE* gLogFile = NULL;

void __stdcall onReceivePacket(unsigned char* buffer, int size){
	if(size < 0) return;
	
	printf("Recv> %d bytes\n", size);
	fprintf(gLogFile, "Recv> %d bytes", size);

	for(int i = 0; i < size; ++i){
		if(i % 16 == 0)
			fprintf(gLogFile, "\n");

		fprintf(gLogFile, "%02x ", buffer[i]);
	}

	fprintf(gLogFile, "\n");
}

void __stdcall onSendPacket(unsigned char* buffer, int size){
	if(size < 0) return;

	printf("Send> %d bytes\n", size);
	fprintf(gLogFile, "Send> %d bytes", size);

	for(int i = 0; i < size; ++i){
		if(i % 16 == 0)
			fprintf(gLogFile, "\n");

		fprintf(gLogFile, "%02x ", buffer[i]);
	}

	fprintf(gLogFile, "\n");
}

unsigned int gEncodeFunction = 0;
void __declspec(naked) hookEncode(){
	_asm {
		MOV EAX, DWORD PTR SS:[ESP + 0x4]//buf
		MOV EDX, DWORD PTR SS:[ESP + 0x8]//size
		
		PUSH ECX

		PUSH EDX
		PUSH EAX
		CALL onSendPacket

		POP ECX

		JMP gEncodeFunction
	};
}

unsigned int gDecodeReturn = 0;
void __declspec(naked) hookDecode(){
	_asm {
		MOV DWORD PTR DS:[ESI + 0x1C70], EAX//size

		PUSH EAX

		LEA EDX, DWORD PTR DS:[ESI + 0xC6C]//buf

		PUSH EAX
		PUSH EDX
		CALL onReceivePacket

		POP EAX

		CMP EAX, -1
		JMP gDecodeReturn
	};
}

unsigned int findCode(unsigned char* code, unsigned int size, unsigned int start, unsigned int end){
	unsigned int cur = start;
	while(cur < end){
		cur = (unsigned int)memchr((void*)cur, code[0], end - cur);
		
		if(memcmp((void*)cur, code, size) == 0)
			return cur;

		cur++;
	}

	return 0;
}
 
unsigned char rawEncode[27] = {
	0xE8, 0xA6, 0xFF, 0xFF, 0xFF, 0x83, 0xF8, 0xFF, 0x74, 0x16, 0x03, 0xF8, 0x3B, 0xBE, 0x74, 0x3C, 
	0x00, 0x00, 0x7C, 0xD9, 0x83, 0xA6, 0x74, 0x3C, 0x00, 0x00, 0x00, 
};

unsigned char rawDecode[25] = {
	0x83, 0xF8, 0xFF, 0x89, 0x86, 0x70, 0x1C, 0x00, 0x00, 0x7F, 0x85, 0xEB, 0x11, 0xE8, 0x35, 0xC8, 
	0xE7, 0xFF, 0x8B, 0x4D, 0xEC, 0x83, 0x4D, 0xFC, 0xFF, 
};

void printError(char* msg){
	DWORD eNum;
	char sysMsg[256];
	char* p;

	eNum = GetLastError( );
	FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		sysMsg, 256, NULL );

	p = sysMsg;
	while( ( *p > 31 ) || ( *p == 9 ) )
		++p;

	do {
		*p-- = 0;
	} while( ( p >= sysMsg ) && ( ( *p == '.' ) || ( *p < 33 ) ) );

	printf("WARNING: %s failed with error %d (%s)\n", msg, eNum, sysMsg );
}

BOOL FindModule( DWORD dwPID, const char* module, DWORD& location, DWORD& size ){ 
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE; 
	MODULEENTRY32 me32; 
 
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID); 
	if(hModuleSnap == INVALID_HANDLE_VALUE){ 
		printError("CreateToolhelp32Snapshot"); 
		return FALSE; 
	} 
  
	me32.dwSize = sizeof( MODULEENTRY32 ); 
 
	if(!Module32First(hModuleSnap, &me32)){ 
		printError("Module32First");
		CloseHandle(hModuleSnap);
		return FALSE; 
	} 
 
	do {
		if(_strcmpi(module, me32.szModule) == 0){
			printf("Found Module   = %s\n", me32.szModule);
			printf("Base Address   = 0x%08X\n", (DWORD) me32.modBaseAddr);
			printf("Base Size      = %d\n", me32.modBaseSize);
			
			size = (DWORD)me32.modBaseSize;
			location = (DWORD)me32.modBaseAddr;
		}
	} while(Module32Next(hModuleSnap, &me32)); 

    printf("\n");
 
	CloseHandle(hModuleSnap); 
	return TRUE; 
}

namespace code {
	void write(unsigned int location, unsigned char* data, unsigned int length){
		DWORD oldProtect;
		unsigned char* code = (unsigned char*)location;
		VirtualProtect(code, length, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(code, data, length);
		VirtualProtect(code, length, oldProtect, &oldProtect);
	}

	template<class T> void write(unsigned int location, T data){
		write(location, (unsigned char*)&data, sizeof(T));
	}

	void read(unsigned int location, unsigned char* buffer, unsigned int length){
		DWORD oldProtect;
		unsigned char* code = (unsigned char*)location;
		VirtualProtect(code, length, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(buffer, code, length);
		VirtualProtect(code, length, oldProtect, &oldProtect);
	}

	template<class T> T read(unsigned int location){
		T tmp;
		read(location, (unsigned char*)&tmp, sizeof(T));
		return tmp;
	}

	template <class T> void jmpHook(unsigned int location, T cfunc, unsigned int nops = 0){
		DWORD oldProtect;
		unsigned char* code = (unsigned char*)location;
		VirtualProtect(code, 5 + nops, PAGE_EXECUTE_READWRITE, &oldProtect);
		code[0] = 0xE9;
		*reinterpret_cast<int*>(code+1) = (int)cfunc - ((int)code + 5);
		if(nops > 0) memset(code + 5, 0x90, nops);
		VirtualProtect(code, 5 + nops, oldProtect, &oldProtect);
	}

	template <class T> unsigned int callRedirect(unsigned int location, T cfunc){
		int calldiff = read<int>(location + 1);
		unsigned int prevfunc = calldiff + location + 5;
		unsigned int newfunc = (unsigned int)cfunc;
		calldiff = newfunc - (location + 5);
		write<int>(location + 1, calldiff);
		return prevfunc;
	}
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved){
	if(dwReason == DLL_PROCESS_ATTACH){
		FILE* console;
		AllocConsole();
		SetConsoleTitle("LoL Console");
		freopen_s(&console, "CONOUT$", "wb", stdout);
		freopen_s(&console, "CONOUT$", "wb", stderr);
		
		DWORD airModuleLoc;
		DWORD airModuleSize;
		FindModule(GetCurrentProcessId(), "Adobe AIR.dll", airModuleLoc, airModuleSize);
		
		fopen_s(&gLogFile, "airlog.txt", "w");

		unsigned int locEncode = findCode(rawEncode, 27, airModuleLoc, airModuleLoc + airModuleSize);
		if(locEncode){
			gEncodeFunction = code::callRedirect(locEncode, &hookEncode);
			printf("Hooked encode at 0x%X\n", locEncode);
		}else
			printf("Could not find location for encode hook\n");

		unsigned int locDecode = findCode(rawDecode, 25, airModuleLoc, airModuleLoc + airModuleSize);
		gDecodeReturn = locDecode + 9;
		if(locDecode){
			code::jmpHook(locDecode, &hookDecode, 4);
			printf("Hooked decode at 0x%X\n", locDecode);
		}else
			printf("Could not find location for decode hook\n");
	}

	return true;
}
