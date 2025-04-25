#include"BnBPacket.h"

// send - header
void(__thiscall *_CSendPacket__CSendPacket)(BnB_ClientPacket *, BYTE) = NULL;
void _fastcall CSendPacket__CSendPacket_Hook(BnB_ClientPacket *ecx, void *edx, BYTE val) {
	DEBUG(L" --- SendPacket Start ---");
	return _CSendPacket__CSendPacket(ecx, val);
}

// send - 1
void(__thiscall *_CSendPacketBase__Encode1)(BnB_ClientPacket *, BYTE) = NULL;
void _fastcall CSendPacketBase__Encode1_Hook(BnB_ClientPacket *ecx, void *edx, BYTE val) {
	DEBUG(L"BYTE : " + BYTEtoString(val));
	return _CSendPacketBase__Encode1(ecx, val);
}

// send - 2
void(__thiscall *_CSendPacketBase__Encode2)(BnB_ClientPacket *, WORD) = NULL;
void _fastcall CSendPacketBase__Encode2_Hook(BnB_ClientPacket *ecx, void *edx, WORD val) {
	DEBUG(L"WORD : " + WORDtoString(val));
	return _CSendPacketBase__Encode2(ecx, val);
}

// send - 4
void(__thiscall *_CSendPacketBase__Encode4)(BnB_ClientPacket *, DWORD) = NULL;
void _fastcall CSendPacketBase__Encode4_Hook(BnB_ClientPacket *ecx, void *edx, DWORD val) {
	DEBUG(L"DWORD : " + DWORDtoString(val));
	return _CSendPacketBase__Encode4(ecx, val);
}

// send - packet
void(__thiscall *_SendPacket)(BnB_ClientPacket *) = NULL;
void _fastcall SendPacket_Hook(BnB_ClientPacket *ecx, void *edx) {
	DEBUG(L" --- SendPacket End ---");
	return _SendPacket(ecx);
}

void RemoveAntiCheat() {
	Rosemary r;
	r.Patch(0x004ABEF3, L"31 C0 C3"); // CRC - first
	r.Patch(0x004ABC9B, L"31 C0 C3"); // CRC
	r.Patch(0x0043F76E, L"31 C0 C3"); // CRC result check
	r.Patch(0x004AE471, L"31 C0 C3"); // same
}

bool BnBPacketHook() {
	// BnB JP37
	RemoveAntiCheat();
	// CSendPacket::CSendPacket
	SHookFunction(CSendPacket__CSendPacket, 0x004643DA);
	// CSendPacketBase::Encode1
	SHookFunction(CSendPacketBase__Encode1, 0x004C74E0);
	// CSendPacketBase::Encode2
	SHookFunction(CSendPacketBase__Encode2, 0x004C7500);
	// CSendPacketBase::Encode4
	SHookFunction(CSendPacketBase__Encode4, 0x004C7520);
	// SendPacket
	SHookFunction(SendPacket, 0x00464463);
	return true;
}