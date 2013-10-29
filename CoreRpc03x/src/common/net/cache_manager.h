#ifndef _H_COMMON_NET_CACHE_MANAGER_H
#define _H_COMMON_NET_CACHE_MANAGER_H
#include <map>
namespace net{
	template<typename T>
	class call_back{
	public:
		virtual run(T& t)=0;
	};

	template<typename T>
	class cache_message{
	public:
		void run(T& t){
			call_back_.run(t);
		}
	private:
		call_back<T> call_back_;
	};

	template<typename K,typename Rsp>
	class cache_manager{

	public:
		//template<typename K>
		void put(K key,cache_message<Rsp> value){
			cache_map_.insert(std::make_pair(key,value));
		}

		
		cache_message<Rsp>* find(K key){
			std::map<K,cache_message>::iterator it=std::map<K,cache_message<Rsp>> cache_map_.find(key);
			return it->second;
		}
		
		
	private:
		std::map<K,cache_message<Rsp>> cache_map_;
	};
}

#endif