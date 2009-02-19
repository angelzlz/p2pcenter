#pragma once

#include "p2sdefine.h"
#include "P2SCommand.h"

class CClient
{
public:
	CClient(void);
	virtual ~CClient(void);

	bool IsCanWork();

	PEERINFO m_peerInfo;
	// ���յ���UDP�򶴰�
	bool m_bUdpAvail;
	// �Ѿ��յ����Ӱ�,��Ӧ���� P2S_CMD_CONNECT
	bool m_bConnAvail;
	// ���SESSION,��ͬ��SOCKET Session
	int m_nSessionID;
	// socket ID
	unsigned long m_ulSocketID;
};
