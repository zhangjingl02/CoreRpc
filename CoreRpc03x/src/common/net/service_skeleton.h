#ifndef _H_COMMON_NET_SERVICE_SKELETON_H
#define _H_COMMON_NET_SERVICE_SKELETON_H
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "message_dispatcher.h"
namespace net{
	template<typename T>
	class ServiceSkeleton{
	
	public:
		ServiceSkeleton(MessageDispatcher<T>* dispatcher)
			:dispatcher_(dispatcher)
		{}
	public :
		virtual void onMessage(boost::shared_ptr<T> message);
	public :
		bool start();
	private:
		boost::thread_group threadGroup_;
		MessageDispatcher<T>* dispatcher_;
	
	};

}
#endif