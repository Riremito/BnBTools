#ifndef __BNB_PACKET_H__
#define __BNB_PACKET_H__

#include"../Share/Simple/Simple.h"
#include"../Share/Hook/SimpleHook.h"

#pragma pack(push, 1)
typedef struct {
	void *__vftable;
	unsigned int m_uSize;
	unsigned __int8 *m_pBlock;
	int m_nPacketType;
	unsigned int m_uOffset;
	int m_nCipherDegree;
} BnB_ClientPacket;
#pragma pack(pop)

bool BnBPacketHook();

#endif