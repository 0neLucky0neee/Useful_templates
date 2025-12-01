#pragma once
#include <Windows.h>

#define SCAN_KEY_W		0x0011
#define SCAN_KEY_A		0x001E
#define SCAN_KEY_S		0x001F
#define SCAN_KEY_D		0x0020

#define SCAN_KEY_F		0x0021

#define SCAN_KEY_SPACE	0x0039
#define SCAN_KEY_LSHIFT 0x002A

#define SCAN_KEY_LALT	0x0038
#define SCAN_KEY_TAB	0x000F

// learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input
void SendCustomKbInput(WORD wScan, DWORD dwUp) {
	INPUT iInputs[0x1] = { NULL };
	iInputs[0x0].type = INPUT_KEYBOARD;
	iInputs[0x0].ki.dwFlags = (dwUp == TRUE ? KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP : KEYEVENTF_SCANCODE);
	iInputs[0x0].ki.wScan = wScan;

	SendInput(1, iInputs, sizeof(INPUT));
}
