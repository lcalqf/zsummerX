/*
* ZSUMMER_11X License
* -----------
* 
* ZSUMMER_11X is licensed under the terms of the MIT license reproduced below.
* This means that ZSUMMER_11X is free software and can be used for both academic
* and commercial purposes at absolutely no cost.
* 
* 
* ===============================================================================
* 
* Copyright (C) 2013 YaweiZhang <yawei_zhang@foxmail.com>.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
* 
* ===============================================================================
* 
* (end of COPYRIGHT)
*/
#ifndef _ZSUMMER_11X_TCPSOCKET_IMPL_H_
#define _ZSUMMER_11X_TCPSOCKET_IMPL_H_

#include "public.h"
#include "../zsummer.h"
namespace zsummer
{
	namespace network
	{
		class CTcpSocketImpl
		{
		public:
			typedef std::function<void(zsummer::network::ErrorCode, std::string, unsigned short)> _OnConnectHandler;
			typedef std::function<void(zsummer::network::ErrorCode, char *, unsigned int, unsigned int)> _OnSendHandler;
			typedef _OnSendHandler _OnRecvHandler;
			CTcpSocketImpl(SOCKET s, std::string remoteIP, unsigned short remotePort);
			~CTcpSocketImpl();
			bool Initialize(CZSummer & summer);
			inline bool GetPeerInfo(std::string& remoteIP, unsigned short &remotePort)
			{
				remoteIP = m_remoteIP;
				remotePort = m_remotePort;
			}
			bool DoConnect(const _OnConnectHandler & handler);
			bool DoSend(char * buf, unsigned int len, const _OnSendHandler &handler);
			bool DoRecv(char * buf, unsigned int len, const _OnRecvHandler & handler);
			bool DoClose();
		public:
			bool OnIOCPMessage(BOOL bSuccess, DWORD dwTranceCount, unsigned char cType);
		public:
			//private
			CZSummer *  m_summer;
			SOCKET		m_socket;
			std::string m_remoteIP;
			unsigned short m_remotePort;

			//recv
			tagReqHandle m_recvHandle;
			WSABUF		 m_recvWSABuf;
			_OnRecvHandler m_onRecvHandler;


			//send
			tagReqHandle m_sendHandle;
			WSABUF		 m_sendWsaBuf;
			_OnSendHandler m_onSendHandler;


			//connect
			tagReqHandle m_connectHandle;
			_OnConnectHandler m_onConnectHandler;
			//status
			bool m_isRecving;
			bool m_isSending;
			bool m_isConnecting;
			int m_nLinkStatus;
		};
	}
}
























#endif











