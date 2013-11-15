#include "service_skeleton.h"

namespace net{
	/*
	template<typename T>
	bool ServiceSkeleton<T>::start(){

		for(int i=0;i<threadCount_;i++){
			threadGroup_.create_thread(boost::bind(&ServiceSkeleton<T>::proccess,this));

		}
		return false;
	}
	template<typename T>
	void ServiceSkeleton<T>::proccess(){
	
		while(runFlag_){
			boost::shared_ptr<NetworkPackage<T>> message;
			dispatcher_->getMessage(message);
			onMessage(message->connection,message->message);
		}
	
	}
	*/

}