#ifndef _H_COMMON_NET_CACHE_MANAGER_H
#define _H_COMMON_NET_CACHE_MANAGER_H
#include <map>
namespace net{

	class call_back{
	public:
		virtual void run()=0;
		virtual void wait()=0;
		virtual void wait(int time);
	};

	template<typename T>
	class cache_message{

	public:
		cache_message(call_back& callback):call_back_(callback){}
		~cache_message(){
			delete rsp;
		}
		void run(){
			call_back_.run();
		}

		 void wait(){
			 call_back_.wait();
		}
		 void wait(int time){
			 call_back_.wait(time);
		}
		void response(T& t){
			*rsp=t;
		}

		T* response(){
			return rsp;
		}
	private:
		call_back& call_back_;
		T* rsp;
	};

	template<typename K,typename Rsp>
	class cache_manager{

	public:
		//template<typename K>
		void put(K key,cache_message<Rsp>* value){
			cache_map_.insert(std::make_pair(key,value));
		}

		
		cache_message<Rsp>* find(K key){
			std::map<K,cache_message>::iterator it=std::map<K,cache_message<Rsp>> cache_map_.find(key);
			return it->second;
		}
		
		
	private:
		std::map<K,cache_message<Rsp>*> cache_map_;
	};
}

#endif