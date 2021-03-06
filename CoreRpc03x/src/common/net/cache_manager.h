#ifndef _H_COMMON_NET_CACHE_MANAGER_H
#define _H_COMMON_NET_CACHE_MANAGER_H
#include <map>
namespace net{

	class call_back{
	public:
		virtual void run(){};
		virtual void wait(){};
		virtual void wait(int time){};
	};

	template<typename T>
	class cache_message{

	public:
		cache_message(call_back& callback):call_back_(callback),is_done_(false){}
		~cache_message(){
			
		}
		void run(boost::shared_ptr<T> t){
			is_done_=true;
			rsp=t;
			call_back_.run();
		}

		 void wait(){
			 call_back_.wait();
		}
		 void wait(int time){
			 call_back_.wait(time);
		}
		void response(boost::shared_ptr<T> t){
			rsp=t;
		}

		boost::shared_ptr<T> response(){
			return rsp;
		}
		bool is_done(){
			return is_done_;
		}
	private:
		call_back& call_back_;
		boost::shared_ptr<T> rsp;
		bool is_done_;
	};

	template<typename K,typename Rsp>
	class cache_manager{

	public:
		//template<typename K>
		void put(K key,cache_message<Rsp>* value){
			cache_map_.insert(std::make_pair(key,value));
		}

		
		cache_message<Rsp>* find(K key){
			//std::map<K,cache_message<Rsp> *>::iterator it= cache_map_.find(key);
			//if(it!=cache_map_.end()){
			//	return it->second;
			//}
			return NULL;
		}

		void remove(){
			
		}
		
	private:
		std::map<K,cache_message<Rsp> * > cache_map_;
	};
}

#endif