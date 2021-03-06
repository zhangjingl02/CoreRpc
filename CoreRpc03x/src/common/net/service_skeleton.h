#ifndef _H_COMMON_NET_SERVICE_SKELETON_H
#define _H_COMMON_NET_SERVICE_SKELETON_H
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "tcp_connection.h"
#include "message_dispatcher.h"

namespace net{
#define DEFAULT_THREAD_COUNT 2
	template<typename T>
	class ServiceSkeleton{

	public:
		ServiceSkeleton(MessageDispatcher<T>* dispatcher)
			:dispatcher_(dispatcher),threadCount_(DEFAULT_THREAD_COUNT),runFlag_(true)
		{}


		
	public :
		virtual void onMessage(tcp_connection& connection,boost::shared_ptr<T> message)=0;
	public :
		bool start(){
			for(int i=0;i<threadCount_;i++){
				threadGroup_.create_thread(boost::bind(&ServiceSkeleton<T>::proccess,this));

			}
			return false;
		}
		void stop(){runFlag_=false;};
	private:
		void proccess(){
			while(runFlag_){
				boost::shared_ptr<NetworkPackage<T> > message;
				dispatcher_->getMessage(message);
				if(message.get()){
					onMessage(message->connection(),message->message());
				}
			}
		}
	private:
		boost::thread_group threadGroup_;
		MessageDispatcher<T>* dispatcher_;
		int threadCount_;
		bool runFlag_;

	};



}
#endif