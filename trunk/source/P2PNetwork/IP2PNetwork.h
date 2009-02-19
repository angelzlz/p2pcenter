#pragma once

#include <string>
#include <list>
using namespace std;

#ifdef P2PNETWORK_EXPORTS
#define P2PNETWORK_API __declspec(dllexport)
#else
#define P2PNETWORK_API __declspec(dllimport)
#endif

class IP2PNetworkNotify
{
public:
	virtual void OnConnect() = 0;
	virtual void OnDisConnect() = 0;
};

// �ο� CONNNECT_STATUS in P2PPeer.h
typedef enum CONNTYPE
{
	CONNTYPE_NONE = 0,
	CONNTYPE_HANDSHAKING,
	CONNTYPE_CONNECTED,
	CONNTYPE_DISCONNECTED
};

struct stPeerInfo {
	DWORD		dwID;
	string		sExternalIP;
	WORD		wExternalUDPPort;
	WORD		wExternalTCPPort;
	bool		bSource;					// �Ƿ�ΪԴ

	CONNTYPE	ConnType;					// ��������
	DWORD		dwUploadBytes;				// �ϴ�����,ʮ���ڵ�ƽ���ϴ��ֽ� ��λ BYTE/��
	DWORD		dwRecvBytes;				// ����ͳ���ϴ�����,ʮ���ڵ�ƽ�������ֽ� ��λ BYTE/��,�Դ�PEER��һ������

	DWORD		dwRequestBlocks;			// ����Ŀ���
	DWORD		dwReceiveBlocks;			// �յ��Ŀ���
	DWORD		dwGetBlocks;				// ������Ŀ���
	DWORD		dwSendBlocks;				// ���͵Ŀ���

	double		dbHealthRate;				// ���ͽ�����
	double		dbReturnRate;				// ���������
};

struct stMonitorInfo {
	list<stPeerInfo> Peers;
	string sChannelName;
};

class IP2PNetwork
{
public:
	virtual bool InitModule( IP2PNetworkNotify* pNotify ) = 0;
	virtual void ReleaseModule() = 0;
	virtual DWORD OpenSource( const char* szUrl, bool bSource ) = 0;
	virtual void CloseSource( DWORD dwChannelID ) = 0;
	virtual void RequestSegment( DWORD dwChannelID, DWORD dwStartPos, DWORD dwLength ) = 0;
	virtual bool ReadSegment( DWORD dwChannelID, DWORD dwStartPos, char* pBuffer, DWORD& dwLength ) = 0; // dwLength ���峤��,���ض�ȡʵ�ʳ���
	virtual LONGLONG GetChannelSize( DWORD dwChannelID ) = 0;
	virtual bool GetAllChannelID( list<DWORD>& listChannels) = 0;
	virtual bool GetChannelMonitorInfo( DWORD dwChannelID, stMonitorInfo& monInfo) = 0;
	virtual bool GetChannelMonitorInfo( const char* szChannelHash, stMonitorInfo& monInfo) = 0;
};

P2PNETWORK_API IP2PNetwork* CreateP2PNetwork();
P2PNETWORK_API bool InitP2PSocket();
P2PNETWORK_API void UninitP2PStocket();