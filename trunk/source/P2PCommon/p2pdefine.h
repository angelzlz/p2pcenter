/********************************************************************
	created:	2008/01/11
	created:	11:1:2008   15:49
	author:		Kevin
	
	purpose:	

	email:		kan8888.com@163.com
	msn:		fuwenke@gmail.com
	QQ:		799383417
	site:		opensource.kan8888.com
*********************************************************************/

#pragma once

//�ͻ�����ͻ���֮�������
typedef enum P2P_CMD_TYPE
{
	P2P_CMD_HANDSHAKE = 0x10001000,		// ����
	P2P_CMD_HANDSHAKE_RET,		
	P2P_CMD_GETBLOCK_AREA,				// ȡ��ӵ�п�
	P2P_CMD_GETBLOCK_AREA_RET,			// ȡ��ӵ�п鷵��
	P2P_CMD_GETSEGMENT,					// ȡ���ļ�Ƭ��
	P2P_CMD_GETSEGMENT_RET,				// ȡ���ļ�Ƭ�η���
	P2P_CMD_STAT_UPLOAD,				// ��ѯ�Է��ϴ�����
	P2P_CMD_STAT_UPLOAD_RET,			// ��ѯ�Է��ϴ���������
	P2P_CMD_HEARTBEAT,					// ����,ά����·
	P2P_CMD_CANCELSEGMENT,				// ȡ������Ŀ�
	P2P_CMD_CANCELSEGMENT_RET,			// ȡ������Ŀ鷵��
	P2P_CMD_EXIT						// �����˳�
};

typedef __int64 QWORD;

#define UDP_PACKET_LENGTH 933
#define UDP_BUFFER_LENGTH 1024
// ����ʱʱ�� ��λ(����)
#define UDP_REQUEST_TIMEOUT 3000
#define P2P_QUERYBLOCK_INTERVAL 5000	  // ��ѯ���ڿ���
#define P2P_MAX_GETSEGMENT_INTERVAL 10000 // ���������������� 10M��
#define P2P_HEARTBEAT_INTERVAL      15000 // P2P�������
#define P2P_TIMEREQUEST_MAX_NUM		64	  // ������PEER������������
#define P2P_TIMESEND_MAX_NUM		64	  // ������PEER������������

