/* 
 * File:   TestService.h
 * Author: Administrator
 *
 * Created on 2013年11月14日, 下午4:44
 */

#ifndef TESTSERVICE_H
#define	TESTSERVICE_H
#include "../common/startup/service.h"
#include <boost/thread.hpp>
#include <stdio.h>
class TestService:public Service {
    
    public:
        TestService():
        Service("test service","version:1","test s"){}
        bool start(){
            th=new boost::thread(boost::bind(&TestService::proccess,this));
            return true;
        }
        
        void stop();
        
        void proccess(){
            int i=0;
            while(i<10){
                printf("process:%d\n",i++);
            }
        
        }
        private:
            boost::thread* th;

};



#endif	/* TESTSERVICE_H */

