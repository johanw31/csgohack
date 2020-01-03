#include <iostream>
#include <Windows.h>
#include <string>
#include "csgo.h"
#include "ProcMem.h"
#include <conio.h>


using namespace hazedumper::signatures;
using namespace std;
using namespace hazedumper::netvars;

ProcMem mem;

DWORD localPlayer;
DWORD gameModule;
const DWORD teamOffset = 0xF4;
const DWORD healthOffset = 0x100;
const DWORD EntLoopDist = 0x10;

BOOL temp = false;

void kevinMemes()
{
	float pJunkcode = 53226288245653;
	pJunkcode = 134113561356242;
	if (pJunkcode = 17345637132425)
		pJunkcode = 183213683111425;
	pJunkcode = 17368136833425;
	pJunkcode = 111368368911;
	if (pJunkcode = 3492511368368534);
	pJunkcode = 23048921365838943;
	pJunkcode = 4390751246453;
	if (pJunkcode = 1712578425)
		pJunkcode = 1794784425;
	pJunkcode = 17324123575;
	pJunkcode = 43574979426534;
	if (pJunkcode = 34245762548659034);
	pJunkcode = 22146784657983657;
	pJunkcode = 43926725782547;
	if (pJunkcode = 1251487936575);
		pJunkcode = 14877868345675;
	pJunkcode = 9835757893256;
	pJunkcode = 785092574769834;
	if (pJunkcode = 4798490257249257674);
	pJunkcode = 2368736735984675346;
	pJunkcode = 553868625670453;
}



int left_click()
{
	// left mouse button down
	INPUT	Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left mouse button up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
	return 0;
}


int main() 
{

	char process[9] = "csgo.exe";
	char module[20] = "client_panorama.dll";
	mem.Process(process);
	gameModule = mem.Module(module);

	do {	
		localPlayer = mem.Read<DWORD>(gameModule + dwLocalPlayer);
	} while (localPlayer == NULL);
	DWORD glowObject = mem.Read<DWORD>(gameModule + dwGlowObjectManager);

	while (true) {

	

		localPlayer = mem.Read<DWORD>(gameModule + dwLocalPlayer);
		int playerNumber = mem.Read<int>(localPlayer + m_iCrosshairId);
		DWORD pEntity = mem.Read<DWORD>(gameModule + dwEntityList + (m_iCrosshairId - 1)* EntLoopDist);
		int teamNumber = mem.Read<int>(pEntity + teamOffset);;
		//cout << teamNumber << endl;
		if ((playerNumber > 0) && (playerNumber < 11)) {
			left_click();
		}
		int myTeam = mem.Read<int>(localPlayer + teamOffset);
		for (short int i = 0; i < 64; i++) {
			DWORD entity = mem.Read<DWORD>(gameModule + dwEntityList + i * EntLoopDist);
			if (entity != NULL) {
				int glowIndex = mem.Read<int>(entity + m_iGlowIndex);
				int entityTeam = mem.Read<int>(entity + teamOffset);
				int entityHealth = mem.Read<int>(entity + healthOffset);
				if (entityTeam != myTeam) {
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0x4), 2);
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0x8), 0);
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0xc), 0);
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0x10), 0.5);
				}
				else
				{
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0x4), 0);
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0x8), 0);
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0xc), 2);
					mem.Write<float>(glowObject + ((glowIndex * 0x38) + 0x10), 0.5);
				}
				mem.Write<bool>(glowObject + ((glowIndex * 0x38) + 0x24), true);
				mem.Write<bool>(glowObject + ((glowIndex * 0x38) + 0x25), false);
			}
		}
		Sleep(5);
	}
}
