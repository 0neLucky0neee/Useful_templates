#pragma once
#include <Windows.h>
#include <winhttp.h>

#pragma comment(lib, "Winhttp.lib")

// learn.microsoft.com/ru-ru/windows/win32/api/winhttp
BYTE* ReadRawFileFromInternet(const WCHAR* wcAgentName, const WCHAR* wcServerName, const WCHAR* wcObjectName, DWORD dwSize = 0x1000) {
	BYTE* wArrayResult = (BYTE*)VirtualAlloc(NULL, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (wArrayResult == NULL) {
		return NULL;
	}

	HINTERNET hInetOpen = WinHttpOpen(wcAgentName, WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, WINHTTP_FLAG_SECURE_DEFAULTS);
	if (hInetOpen == NULL) {
		return NULL;
	}

	HINTERNET hInetConnect = WinHttpConnect(hInetOpen, wcServerName, INTERNET_DEFAULT_HTTPS_PORT, NULL);
	if (hInetConnect == NULL) {
		return NULL;
	}

	HINTERNET hInetRequest = WinHttpOpenRequest(hInetConnect, L"GET", wcObjectName, L"HTTP/1.3", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
	if (hInetRequest == NULL) {
		return NULL;
	}

	BOOL hInetSendRequest = WinHttpSendRequest(hInetRequest, WINHTTP_NO_ADDITIONAL_HEADERS, NULL, WINHTTP_NO_REQUEST_DATA, NULL, NULL, NULL);
	if (hInetSendRequest == FALSE) {
		return NULL;
	}

	BOOL hInetDataAvailable = WinHttpReceiveResponse(hInetRequest, NULL);
	if (hInetDataAvailable == FALSE) {
		return NULL;
	}

	BOOL bReaded = WinHttpReadData(hInetRequest, wArrayResult, dwSize, NULL);
	if (bReaded == FALSE) {
		return NULL;
	}

	WinHttpCloseHandle(hInetOpen);
	WinHttpCloseHandle(hInetConnect);
	WinHttpCloseHandle(hInetRequest);

	return wArrayResult;
}