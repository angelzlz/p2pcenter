#pragma once

#include "P2PPacket.h"

// ��������0��ʼ
class CP2PPacketMgr :
	public CKPtrMap<DWORD, CP2PPacket>
{
public:
	CP2PPacketMgr(void);
	virtual ~CP2PPacketMgr(void);
	
	// ��ȡ�ļ�Ƭ��
	bool ReadSegment( DWORD dwStartPos, char* pBuffer, DWORD& dwLength );
	// ɾ�������� [dwStartBlock, dwEndBlock] ����Ŀ�
	void RemoveBlock( DWORD dwStartBlock, DWORD dwEndBlock );
	// �յ��°�
	bool PacketArrived( DWORD dwBlockIndex, char* pBuffer );
	// ����һЩ��
	void InsertShouldBlock( DWORD dwStartBlock, DWORD dwBlockNum );
	// ɾ������δ��������Ŀ��
	void ClearShouldBlock();
	// ���³�ʱ��״̬,�Ա��ٴ�����
	// ��ʱ����,ʱ�䲻Ҫ����1��,���鶨��100us
	void UpdateTimeOutStatus( DWORD dwTimeUsec = UDP_REQUEST_TIMEOUT );
	// ���ô˺�ʽ��������������.�ڴ˺����������ʱ���,��Ϊ false,��û�п�������Ŀ�
	bool GetShouldBlock( DWORD& dwStart, DWORD& dwEnd );
	// ����MAP���״̬
	void UpdatePacketStatus( const map<DWORD, DWORD>& mapRequests, PACKET_STATUS status);

	// ȡ���Ѵ��ڵĿ�,�����Ŀ�
	bool GetExistBlockAreas( map<DWORD, DWORD>& mapAreas );
	bool GetExistBlockList( list<DWORD>& listBlock, DWORD dwStartBlock, DWORD dwEndBlock );
};
