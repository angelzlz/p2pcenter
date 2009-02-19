#pragma once

#include "network/KSocket.h"
#include "misc/KDataBuffer.h"

class CTransMonitor
{
public:
	CTransMonitor(void);
	virtual ~CTransMonitor(void);

	bool PushBuffer( const char* szData, int nLen);
	void SendData();
	void ClearData();

public:
	char m_cTransType;			// ���䷽��1 == �գ�2 == ��
	char m_cMonitorType;		// ������ͣ�1 == P2S TCP�� 2 == P2S UDP, 3 == P2P TCP, 4 = P2P UDP
	char m_cTransWeight;		// �������ݵ����� 1 == ����ȫ�����ݣ� 2 == ��CMD ID,  Ŀǰ���ԣ�����ȫ��������
	char m_cSendInterval;		// ��ط�����С�������ȷ���롣
	int m_nDstIP;				// Ŀ��UDP IP
	unsigned short m_usDstPort;	// Ŀ��UDP PORT

private:
	CKUdpSocket m_udpSocket;
	CKPtrList<CKDataBuffer> m_listData; 
};
