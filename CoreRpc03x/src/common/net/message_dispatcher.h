#ifndef _H_NET_MESSAGE_DISPATCHER_H
#define _H_NET_MESSAGE_DISPATCHER_H
#include <boost/shared_ptr.hpp>
#include "../util/blocking_queue.h"
#include "../util/concurrent_queue.h"
#include "net_package.h"
namespace net{
	
	template<typename T>
	class MessageDispatcher{
	
	public:
		//template<typename T>
		void pushMessage(tcp_connection& conn,boost::shared_ptr<T> message){
			const boost::shared_ptr<NetworkPackage<T> > networkPackage(new NetworkPackage<T>(conn));
			networkPackage->message(message);
			messageQueue_.push(networkPackage);
		};
		//template<typename T>
		bool  getMessage(boost::shared_ptr<NetworkPackage<T> >& message){
		 messageQueue_.wait_and_pop(message);
		 return true;
		};
	private:
		util::concurrent_queue<boost::shared_ptr<NetworkPackage<T> > > messageQueue_;
	};


	
		
}
#endif