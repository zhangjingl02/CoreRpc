#ifndef _H_NET_MESSAGE_DISPATCHER_H
#define _H_NET_MESSAGE_DISPATCHER_H
#include <boost/shared_ptr.hpp>
#include "../util/blocking_queue.h"
namespace net{
	
	template<typename T>
	class MessageDispatcher{
	
	public:
		template<typename T>
		void pushMessage(boost::shared_ptr<T> message){
			messageQueue_.put(message);
		}
		template<typename T>
		bool  getMessage(boost::shared_ptr<T> message){
			return messageQueue_.take(message,5*1000);
		}
	private:
		util::BlockingQueue<boost::shared_ptr<T>> messageQueue_;
	};


	
		
}
#endif