#ifndef _H_NET_NET_DEF_H
#define _H_NET_NET_DEF_H
namespace net{
	enum RecvState{
		NEED_DATA,RECV_SUCCESS,RECV_ERROR
	};
	enum ConnectionState{
		INIT,CONNECTED,CLOSED,CONNECT_ERROR
	};
}
#endif