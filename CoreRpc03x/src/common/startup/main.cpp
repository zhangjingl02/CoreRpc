#include "nt_service.h"
#include <WinBase.h>
#include <boost/filesystem.hpp>
#include "../util/file_system.h"
#ifdef WIN32
class ShineService : public NTService
{
public:
	ShineService()
		: NTService("","","")
	{
	}
	virtual bool OnInit()
	{
		//loadLoggerConfig();
		//cacti::AbstractPath::initRols("./apc.conf");
		//bootupSocket();
		return true;
	}
	virtual void Run()
	{
		//Logger& syslog = Logger::getInstance(LOGGER_STARTUP_SYS);
		
		//if(m_commander.startService(0))
		//{
		//	syslog.info("Running\n");
		//}
		NTService::Run();
	}
	virtual void OnStop()
	{
		//m_commander.stopService();
		//shutdownSocket();
	}
private:
	//Commander& m_commander;
};

int doNTService(int argc, char* argv[])
{
	std::string modpath = util::FileSystem::getModulePath();
	SetCurrentDirectory(modpath.c_str());


	ShineService ntservice;
	if (!ntservice.ParseStandardArgs(argc, argv)) {
		ntservice.StartService();
	}
	
	// 到这里，服务已经停止
	return ntservice.m_status.dwWin32ExitCode;
}

#endif

int main(int argc, char** argv) {
	return 0;
}