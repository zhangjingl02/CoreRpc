#ifndef _H_COMMON_H_
#define _H_COMMON_H_
#include <boost/thread.hpp>
#ifdef WIN32
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <glog/logging.h>

#define _TID_ boost::this_thread::get_id() 
#define _LOG_HEAD_(logLevel) LOG(logLevel)<<"\"T\":"<<_TID_<<"\",\"M\":"<<__FUNCTION__<<"\",\"P\":{"
#define _LOG_END "}"
#define _KV_(key,value) "\""<<key<<"\":\""<<value<<"\"," 
   /**
    **  use log_info example:
    **  LOG_INFO(_KV_("test","testvalue")
    **       <<_KV_("test2","value2")
    **      <<_KV_("test3",3)
    **      <<_KV_("test3",boost:this_thread::get_id())
    **   );
    **/

#define _LOG_(level,kvs)  _LOG_HEAD_(level)<<kvs<<_LOG_END
#define LOG_ERR(kvs) _LOG_(ERROR,kvs)
#define LOG_INF(kvs) _LOG_(INFO,kvs)
#define LOG_DBG(kvs) _LOG_(DEBUG,kvs)

#endif