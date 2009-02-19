/********************************************************************
	created:	2008/01/11
	created:	11:1:2008   15:49
	author:		Kevin
	
	purpose:	

	email:		kan8888.com@163.com
	msn:		fuwenke@gmail.com
	QQ:			799383417
	site:		opensource.kan8888.com
*********************************************************************/

// P2POrderServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "OrderApp.h"
#include "UdpServer.h"
#include "log/KLog.h"
#include "VideoChatServer.h"

void CommandProcess( COrderApp& app);

int _tmain(int argc, _TCHAR* argv[])
{
#ifndef _DEBUG
	CKLog::SetDebugType( LOG_TYPE_WARNING);
#endif

	initNetwork();

	COrderApp app;
	CVideoChatServer vcserver;
	CUdpServer udpServer;
	udpServer.SetApp( &app );

	if ( !app.Connect() )
		return -1;

	if ( !vcserver.Connect() )
		return -2;

	if ( !udpServer.Connect() )
	{
		app.Release();
		uninitNetwork();
		return -1;
	}

	CommandProcess( app);

	udpServer.Release();

	vcserver.Release();
	app.Release();

	uninitNetwork();

	return 0;
}

void CommandProcess( COrderApp& app)
{
	char Message[1024];

	while (TRUE)
	{
		memset((void*)Message,0,sizeof(Message));
		printf(">");
		scanf("%s",Message);
		char *pPos = Message;
		while (*pPos != '\0')
		{
			*pPos = tolower(*pPos);
			pPos++;
		}
		char * lowCase = Message;

		if(strcmp(lowCase,"exit")==0)
		{
			printf("Exit? [Y] or [N]\n");
			char bexit;
			while (TRUE)
			{
				printf(">");
				bexit = getchar();
				if(isprint(bexit))
				{
					if(bexit=='y'||bexit=='Y'||bexit=='N'||bexit=='n')
					{
						break;
					}
					else 
					{
						printf("Enter [Y] to exit or enter [N] to continue\n");
					}
				}
			}
			printf("%c\n",bexit);
			if(bexit =='y'||bexit == 'Y')
			{
				break;
			}
		}

		app.TransInputCommand( lowCase);
	}
}

