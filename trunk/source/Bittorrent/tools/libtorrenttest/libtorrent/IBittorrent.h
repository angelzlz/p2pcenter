#pragma once

#include <string>
#include <list>
#include <windows.h>
using namespace std;

#ifdef LIBTORRENT_EXPORTS
#define BITTORRENT_API __declspec(dllexport)
#else
#define BITTORRENT_API __declspec(dllimport)
#endif

class IBittorrentNotify
{
public:
	virtual OnConnect() = 0;
	virtual OnDisConnect() = 0;
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

class IBittorrent
{
public:
	virtual bool InitModule( IBittorrentNotify* pNotify ) = 0;
	virtual void ReleaseModule() = 0;
	virtual DWORD OpenSource( const char* szUrl, bool bSource ) = 0;
	virtual void CloseSource( DWORD dwChannelID ) = 0;
	virtual void RequestSegment( DWORD dwChannelID, DWORD dwStartPos, DWORD dwLength ) = 0;
	virtual bool ReadSegment( DWORD dwChannelID, DWORD dwStartPos, char* pBuffer, DWORD& dwLength ) = 0; // dwLength ���峤��,���ض�ȡʵ�ʳ���
	virtual LONGLONG GetChannelSize( DWORD dwChannelID ) = 0;
	virtual bool GetAllChannelID( list<DWORD>& listChannels) = 0;
	virtual bool GetChannelMonitorInfo( DWORD dwChannelID, stMonitorInfo& monInfo) = 0;
	virtual bool GetChannelMonitorInfo( const char* szChannelHash, stMonitorInfo& monInfo) = 0;
	virtual void tick_it(){};
};

BITTORRENT_API IBittorrent* CreateIBittorrent();
