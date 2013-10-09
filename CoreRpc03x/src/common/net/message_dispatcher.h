#ifndef _H_NET_MESSAGE_DISPATCHER_H
#define _H_NET_MESSAGE_DISPATCHER_H
#include <boost/shared_ptr.hpp>
#include "../util/blocking_queue.h"
#include "net_package.h"
namespace net{
	
	template<typename T>
	class MessageDispatcher{
	
	public:
		template<typename T>
		void pushMessage(TcpConnectionPtr conn,boost::shared_ptr<T> message){
			boost::shared_ptr<NetworkPackage<T>> networkPackage(new NetworkPackage<T>());
			networkPackage->connection=conn;
			networkPackage->message=message;
			messageQueue_.put(networkPackage);
		}
		template<typename T>
		bool  getMessage(boost::shared_ptr<NetworkPackage<T>>& message){
			return messageQueue_.take(message,5*1000);
		}
	private:
		util::BlockingQueue<boost::shared_ptr<NetworkPackage<T>>> messageQueue_;
	};


	
		
}
#endif