#pragma once

typedef enum CONNNECT_STATUS
{
	CONNNECT_STATUS_NONE = 0,
	CONNNECT_STATUS_HANDSHAKING,
	CONNNECT_STATUS_CONNECTED,
	CONNNECT_STATUS_DISCONNECTED
};

struct ST_TRANS_STAT {
	DWORD dwTime;
	DWORD dwBytes;
	ST_TRANS_STAT()
	{
		dwTime = GetTickCount();
		dwBytes = UDP_PACKET_LENGTH;
	}
};

// �ٶ�ͳ�Ƽ������λ����
#define SPEED_STAT_INTERVAL 10

class CP2PPeer
{
public:
	CP2PPeer(void);
	virtual ~CP2PPeer(void);

	virtual bool IsHaveBlock( int nBlockNum );

	void CalcRequestBlock( DWORD dwBlock );	// �ѷ���Է������
	void CalcRecvBlock( DWORD dwBlock );	// ����Ŀ鱻�ѷ����յ�
	double HealthRate();

	void CalcGetBlock( DWORD dwBlock );		// �Է����ѷ������
	void CalcSendBlock( DWORD dwBlock );	// �ѷ���Է����Ϳ�
	double ReturnRate();

	PEERINFO m_peerInfo;
	map<DWORD, DWORD> m_mapBlockAreas;
	CONNNECT_STATUS m_connStatus;
	map<DWORD, DWORD> m_mapNeedBlocks;  // ����Ŀ�ž���Ҫ���͸���PEER�ģ�second ����
	DWORD    m_dwUploadBytes;			// �ϴ�����,ʮ���ڵ�ƽ���ϴ��ֽ� ��λ BYTE/��
	DWORD    m_dwRecvBytes;				// ����ͳ���ϴ�����,ʮ���ڵ�ƽ�������ֽ� ��λ BYTE/��,�Դ�PEER��һ������
	DWORD    m_dwLastHeartbeatTime;		// ���һ�η�������ʱ��

	DWORD    m_dwRequestBlocks;			// ����Ŀ���
	DWORD    m_dwReceiveBlocks;			// �յ��Ŀ���
	DWORD    m_dwGetBlocks;				// ������Ŀ���
	DWORD    m_dwSendBlocks;			// ���͵Ŀ���
	list<ST_TRANS_STAT> m_listUploads;	// �ϴ����ֽ��б� first = time
	list<ST_TRANS_STAT> m_listReceives;	// ���յ����ֽ��б�
};
