//
// Copyright (C) C0000374
//

#include <Windows.h>

#define NAKED	__declspec(naked)
#define STDCALL	__stdcall
#define ASM		__asm

typedef union __UINT128 UINT128, * PUINT128;
union __UINT128 {
	UINT32			Dwords[4];
	UINT8			Bytes[16];
};

const UINT8 Table[62] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

NAKED
UINT32 STDCALL Random(VOID) {

Gen:
	ASM {
		rdrand eax
		jnc    Gen
		retn
	};
}

VOID STDCALL Main(VOID) {

	UINT128	RandomNumber;
	UINT32	i;

	for (i = 0; i < 4; i++) RandomNumber.Dwords[i] = Random();

	for (i = 0; i < 16; i++) RandomNumber.Bytes[i] = Table[RandomNumber.Bytes[i] % 62];

	WriteConsoleA(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&(RandomNumber.Bytes),
		16,
		&i,
		NULL
	);
	ExitProcess(0);
}