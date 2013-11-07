/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2013年11月7日, 下午3:07
 */
#include "stdafx.h"
#include <windows.h>



#include <cstdlib>
#include <boost/thread.hpp>
#include "src/common/daemon/nt_service.h"


using namespace std;

void test(){
	int i=0;
	while(true){
		i++;
		if(i>10000){
			i=0;
		}
	}
}

class ShineService : public NTService
{
public:
	ShineService()
		: NTService("","","")
	{
	}
	virtual bool OnInit()
	{
	
		return true;
	}
	virtual void Run()
	{
		
		boost::thread t(&test);
		printf("Runing...\n");
		NTService::Run();
	}
	virtual void OnStop()
	{
			printf("stopping...\n");
	
	}
private:
	
};

int doNTService(int argc, char* argv[])
{
	
	ShineService ntservice();
	if (!ntservice.ParseStandardArgs(argc, argv)) {
		ntservice.StartService();
	}
	
	// 到这里，服务已经停止
	return ntservice.m_status.dwWin32ExitCode;
}

/*
 * 
 */
int main(int argc, char** argv) {

	doNTService(argc,argv);

    return 0;
}

