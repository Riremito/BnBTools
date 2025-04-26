#include"BnBPacket.h"
#include<intrin.h>
#pragma intrinsic(_ReturnAddress)

// send - header
void(__thiscall *_CSendPacket__CSendPacket)(BnB_ClientPacket *, BYTE) = NULL;
void _fastcall CSendPacket__CSendPacket_Hook(BnB_ClientPacket *ecx, void *edx, BYTE val) {
	DEBUG(L" --- SendPacket Start ---");
	return _CSendPacket__CSendPacket(ecx, val);
}

// send - 1
void(__thiscall *_CSendPacketBase__Encode1)(BnB_ClientPacket *, BYTE) = NULL;
void _fastcall CSendPacketBase__Encode1_Hook(BnB_ClientPacket *ecx, void *edx, BYTE val) {
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | Encode1 : " + BYTEtoString(val) + L", offset = " + std::to_wstring(ecx->m_uOffset));
	return _CSendPacketBase__Encode1(ecx, val);
}

void(__thiscall *_CSendPacketBase__Encode1At)(BnB_ClientPacket *, DWORD, BYTE) = NULL;
void _fastcall CSendPacketBase__Encode1At_Hook(BnB_ClientPacket *ecx, void *edx, DWORD offset, BYTE val) {
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | Encode1At : " + BYTEtoString(val) + L", offset = " + std::to_wstring(offset));
	return _CSendPacketBase__Encode1At(ecx, offset, val);
}

// send - 2
void(__thiscall *_CSendPacketBase__Encode2)(BnB_ClientPacket *, WORD) = NULL;
void _fastcall CSendPacketBase__Encode2_Hook(BnB_ClientPacket *ecx, void *edx, WORD val) {
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | Encode2 : " + WORDtoString(val) + L", offset = " + std::to_wstring(ecx->m_uOffset));
	return _CSendPacketBase__Encode2(ecx, val);
}

void(__thiscall *_CSendPacketBase__Encode2At)(BnB_ClientPacket *, DWORD, WORD) = NULL;
void _fastcall CSendPacketBase__Encode2At_Hook(BnB_ClientPacket *ecx, void *edx, DWORD offset, WORD val) {
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | Encode2At : " + WORDtoString(val) + L", offset = " + std::to_wstring(offset));
	return _CSendPacketBase__Encode2At(ecx, offset, val);
}

// send - 4
void(__thiscall *_CSendPacketBase__Encode4)(BnB_ClientPacket *, DWORD) = NULL;
void _fastcall CSendPacketBase__Encode4_Hook(BnB_ClientPacket *ecx, void *edx, DWORD val) {
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | Encode4 : " + DWORDtoString(val) + L", offset = " + std::to_wstring(ecx->m_uOffset));
	return _CSendPacketBase__Encode4(ecx, val);
}

void(__thiscall *_CSendPacketBase__Encode4At)(BnB_ClientPacket *, DWORD, DWORD) = NULL;
void _fastcall CSendPacketBase__Encode4At_Hook(BnB_ClientPacket *ecx, void *edx, DWORD offset, DWORD val) {
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | Encode4At : " + DWORDtoString(val) + L", offset = " + std::to_wstring(offset));
	return _CSendPacketBase__Encode4At(ecx, offset, val);
}

// send - buffer
void(__thiscall *_CSendPacketBase__EncodeBuffer)(BnB_ClientPacket *, BYTE*, DWORD) = NULL;
void _fastcall CSendPacketBase__EncodeBuffer_Hook(BnB_ClientPacket *ecx, void *edx, BYTE *val, DWORD size) {
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | EncodeBuffer : " + DatatoString(val, size) + L"size = " + std::to_wstring(size) + L", offset = " + std::to_wstring(ecx->m_uOffset));
	return _CSendPacketBase__EncodeBuffer(ecx, val, size);
}

// send - string
void(__thiscall *_CSendPacketBase__EncodeEncryptedStr)(BnB_ClientPacket *, char**, DWORD) = NULL;
void _fastcall CSendPacketBase__EncodeEncryptedStr_Hook(BnB_ClientPacket *ecx, void *edx, char **str, DWORD key) {
	std::string sstr = *str;
	std::wstring wstr = std::wstring(sstr.begin(), sstr.end());
	DEBUG(DWORDtoString((ULONG_PTR)_ReturnAddress()) + L" | EncodeEncryptedStr : \"" + wstr + L"\", key = " + DWORDtoString(key)+ L", offset = " + std::to_wstring(ecx->m_uOffset));
	return _CSendPacketBase__EncodeEncryptedStr(ecx, str, key);
}


// send - packet
#define RETADDR_SENDPACKET 0x0046446F
void(__thiscall *_SendPacket)(BnB_ClientPacket *) = NULL;
void _fastcall SendPacket_Hook(BnB_ClientPacket *ecx, void *edx) {
	DEBUG(L" --- SendPacket End --- (" + std::to_wstring(ecx->m_uOffset) + L", " + DWORDtoString((ULONG_PTR)_ReturnAddress()) +  L")");
	return _SendPacket(ecx);
}
void(__thiscall *_SendPacket2)(void *ecx, BnB_ClientPacket *) = NULL;
void _fastcall SendPacket2_Hook(void *ecx, void *edx, BnB_ClientPacket *packet) {
	if ((ULONG_PTR)_ReturnAddress() != RETADDR_SENDPACKET) {
		DEBUG(L" --- SendPacket End --- (" + std::to_wstring(packet->m_uOffset) + L", " + DWORDtoString((ULONG_PTR)_ReturnAddress()) + L")");
	}
	return _SendPacket2(ecx, packet);
}

void RemoveAntiCheat(Rosemary &r) {
	r.Patch(0x004ABEF3, L"31 C0 C3"); // CRC - first
	r.Patch(0x004ABC9B, L"31 C0 C3"); // CRC
	r.Patch(0x0043F76E, L"31 C0 C3"); // CRC result check
	r.Patch(0x004AE471, L"31 C0 C3"); // same
}

void BandiAid(Rosemary &r) {
	// 004AB1B4 - E8 7EFFFFFF - call 004AB137
	r.Patch(0x004B8601, L"68 B9 B1 4A 00"); // push 004AB1B9
	r.JMP(0x004B8601 + 0x05, 0x004AB137);
	r.JMP(0x004AB1B4, 0x004B8601);
}

bool BnBPacketHook() {
	Rosemary r;
	// BnB JP37
	RemoveAntiCheat(r);
	// Bandaid fix for SendPacket2
	BandiAid(r);

	// CSendPacket::CSendPacket
	SHookFunction(CSendPacket__CSendPacket, 0x004643DA);
	// CSendPacketBase::Encode1
	SHookFunction(CSendPacketBase__Encode1, 0x004C74E0);
	// CSendPacketBase::Encode2
	SHookFunction(CSendPacketBase__Encode2, 0x004C7500);
	// CSendPacketBase::Encode4
	SHookFunction(CSendPacketBase__Encode4, 0x004C7520);
	// CSendPacketBase::EncodeBuffer
	SHookFunction(CSendPacketBase__EncodeBuffer, 0x004C7580);
	// CSendPacketBase::EncodeEncryptedStr
	SHookFunction(CSendPacketBase__EncodeEncryptedStr, 0x004C7560);

	// SendPacket
	SHookFunction(SendPacket, 0x00464463);
	SHookFunction(SendPacket2, 0x004AB1B4); // êÊì™callîÒëŒâû (tools lib)
	// EncodeAt
	SHookFunction(CSendPacketBase__Encode1At, 0x004C79A0);
	SHookFunction(CSendPacketBase__Encode2At, 0x004C7A40);
	SHookFunction(CSendPacketBase__Encode4At, 0x004C7AE0);
	return true;
}