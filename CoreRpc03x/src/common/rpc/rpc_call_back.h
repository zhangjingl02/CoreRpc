#ifndef _H_COMMON_RPC_CALL_BACK_H
#define _H_COMMON_RPC_CALL_BACK_H
#include <boost/thread/condition.hpp>
#include "../net/cache_manager.h"
#include "rpc.pb.h"
namespace rpc{
	 typedef boost::unique_lock<boost::mutex> UniqueLock;
	 typedef boost::mutex::scoped_lock ScopedLock;
	class rpc_call_back :public net::call_back{
	public:
		void run(){
			ScopedLock lg(m_mutex);
			m_notRsp.notify_one();
		}

		void wait(){
			 ScopedLock lg(m_mutex);
			 m_notRsp.wait(lg);
		}


		void wait(int timeout){
			 ScopedLock lg(m_mutex);
			 m_notRsp.timed_wait(lg, boost::posix_time::milliseconds(timeout));
			//m_notRsp.wait(lg, boost::posix_time::milliseconds(timeout));
		}
	private:
		boost::mutex m_mutex;
        boost::condition_variable m_notRsp;
	};
}
#endif 