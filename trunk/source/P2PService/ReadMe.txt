IE to P2PService ��URL�涨:
	��ȡ�ļ��ӿ�:
		��ʽ: http://host:port/filename.rmvb?serveraddr=serverhost&tcpport=tcpport&updoort=3344&agent=agentname&upuserid=1&userid=111&nodename=nodename(char[32])&filehash=char[32]&filesize=DWORD[4]&filepath=D:\xxx
		ʾ��:http://127.0.0.1:81/test.rmvb?serveraddr=p2p.kan8888.com&tcpport=8902&udpport=3344&agent=shengcong&upuserid=1&userid=999&nodename=KevinTestNode&filehash=ABCD3458934759834753479857349444&filesize=333654321&filename=FileName.rmvb&filepath=C:\\ttt\test.rmvb
		��ѡ����:nodename �ڵ�HASH,��Ŀ¼,һ����������ж��Ŀ¼,Ҳ���Գ������ group
				filehash ��ӦĿ¼���ļ���MD5��׼HASH��,32�ֽ�,�ļ��Դ���Ϊ���ֱ�׼
				filesize �ļ�ʵ�ʳ���,��λ,�ֽ�
				filepath �ļ�·��,������Դ��Ч
		��ѡ����:serveraddr(default:p2p.kan8888.com), tcpport(default:8902), udpport(default:3344), agent, upuserid, userid
		��ǰ�汾 serveraddr tcpport udpport�����ڱ���״̬.P2PNetwork���ӵķ����������� P2PNetwork.ini�ṩ
		
	��ȡ������ݽӿ�:
		��ʽ:http://host:port/monitor.js?channelhash=char[32]
		ʾ��:http://host:port/monitor.js?channelhash=ABCD3458934759834753479857349444
		��ѡ����: channelhash ���ȱ���Ϊ32�ֽ��ļ���׼MD5����HASH��,Ϊ��ȡ������Ƶ�����
	
App to P2PNetwork ��URL�涨:
	��ʽ: kp2p://tcpserver:tcpport/....
	������ IE to P2PService ��URL�涨��ͬ,��tcpserver��tcpport
	ע:UDP�� UDPSERVER:UPDPORT������tcpserver:tcpport��,��¼����
