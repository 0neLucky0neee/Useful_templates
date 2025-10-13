#pragma once
#include <Windows.h>

// learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input
void SendCustomKbInput(WORD wScan, DWORD dwUp) {
	INPUT iInputs[0x1] = { NULL };
	iInputs[0x0].type = INPUT_KEYBOARD;
	iInputs[0x0].ki.dwFlags = (dwUp == TRUE ? KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP : KEYEVENTF_SCANCODE);
	iInputs[0x0].ki.wScan = wScan;

	SendInput(1, iInputs, sizeof(INPUT));
}
