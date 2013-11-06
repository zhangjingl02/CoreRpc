#ifndef _H_COMMON_RPC_RPC_CHANNEL_H
#define _H_COMMON_RPC_RPC_CHANNEL_H
#include <vector>
#include <map>
#include <boost/bind.hpp>
#include <google/protobuf/service.h>
#include "../util/sequence_generator.h"
#include "../net/tcp_connection.h"
#include "../net/cache_manager.h"
#include "rpc.pb.h"
namespace rpc{
	typedef std::map<std::string,std::vector<net::tcp_connection_ptr> > connections_map;
	class RpcChannel :public google::protobuf::RpcChannel{
	
	public:
		RpcChannel(net::cache_manager<int,Response>& cache_manager):
			cache_manager_(cache_manager){}
	public:
		virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller,
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response,
                          google::protobuf::Closure* done);

		void addConnection(std::string service_name,net::tcp_connection_ptr& connection){

			LOG_INF(_KV_("message","add service channel")
				<<_KV_("name",service_name)
				<<_KV_("id",connection->id())
				);
			connections_map::iterator it=connections_map_.find(service_name);
			if(it==connections_map_.end()){
				std::vector<net::tcp_connection_ptr> connection_list;
				connections_map_.insert(std::make_pair(service_name,connection_list));
				it=connections_map_.find(service_name);
			}
			
			for(std::vector<net::tcp_connection_ptr>::iterator connection_it=it->second.begin();connection_it!=it->second.end();connection_it++){
				
				if(connection_it->get()->id()==connection->id()){
					return;
				}
			}

			it->second.push_back(connection);
			connection->add_close_callback(boost::bind(&RpcChannel::on_connection_close,this,_1,_2));
		}
	private:
		void on_connection_close(int id,const boost::system::error_code& error){
			for(connections_map::iterator it=connections_map_.begin();it!=connections_map_.end();it++){
				
				for(std::vector<net::tcp_connection_ptr>::iterator connection_it=it->second.begin();connection_it!=it->second.end();connection_it++){
				
					if(connection_it->get()->id()==id){
						it->second.erase(connection_it);
					}
				}
			}
		}
	private:
		net::tcp_connection_ptr get_connection(const std::string& service_name);
		
	private:
		util::SequenceGenerator sequence_gen_;
		std::vector<net::tcp_connection_ptr> connections_;
		connections_map connections_map_;
		net::cache_manager<int,Response>& cache_manager_;

	};
}
//
#endif 