// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>

#include <map>
#include <string>
#include <list>
using namespace std;

#include <atlbase.h>
#include <atlapp.h>
#include <atlmisc.h>

#include <assert.h>

#include "log/KLog.h"
#include "p2pdefine.h"
#include "p2sdefine.h"

#include "thread/KThread.h"
#include "misc/KPtrList.h"
#include "misc/KPtrMap.h"
#include "network/KSocket.h"

#include "ip2pnetwork.h"

#include "../../inc/TcpClient.h"
#pragma comment(lib, "../../lib/TcpClient.lib")
#pragma comment(lib, "WS2_32.lib")

#include "P2SCommand.h"
#include "P2PCommand.h"

#include "P2PNetwork.h"
extern CP2PNetwork* g_pNetwork;

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
