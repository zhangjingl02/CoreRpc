#include "stdafx.h"
#include "nt_service.h"
#include <fstream>
#include <set>
#include <string>
#include <string.h>
#include <stdio.h>
#include "service.h"
#include "commander.h"
#include "../util/file_system.h"
#include "XnuxDaemon.h"

#ifndef WIN32
#ifdef __linux__
#	include <sys/prctl.h>
#endif
#	include <sys/time.h>
#	include <sys/resource.h>
uid_t	uid	= 0;
#else
#pragma comment(lib, "user32.lib")
#include <process.h>
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")
#include <WinBase.h>
#endif
using namespace std;



void createChild(int argc, char* argv[])
{
#ifdef WIN32
	// check weather the process already running...
	ifstream ifp;
	ifp.open(PIDFILENAME);
	if(ifp.is_open())
	{
		std::string procname = argv[0];
		std::string::size_type pos = procname.find_last_of('\\');
		if(pos != std::string::npos)
			procname = procname.substr(pos+1);

		bool running = false;
		DWORD procid;
		ifp >> procid;

		HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procid);
		if(hproc != NULL)
		{
			HMODULE hmod;
			DWORD needed;
			if(EnumProcessModules(hproc, &hmod, sizeof(hmod), &needed))   
			{
				TCHAR modname[_MAX_PATH] = "";
				GetModuleBaseName(hproc, hmod, modname, sizeof(modname));
				if(!_stricmp(modname, procname.c_str()))   
				{
					running = true;
				}   
			}
			CloseHandle(hproc);			
		}
		if(running)
		{
			cout << procname << " already running, process ID is " << procid << endl;
			exit(12);
		}	
	}
	//
	std::string childprocess;
	for(int i=0; i<argc; i++)
	{
		childprocess += argv[i];
		childprocess += " ";
	}

	// append a "child option to the command line
	childprocess += "child";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

	if( !CreateProcessA( NULL,
		(LPSTR)childprocess.c_str(),
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW,                // creation flags. 
		NULL,
		NULL,
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		cout << "Can't create a daemon" << endl;
		exit(-1);
	}
	cout << "Using daemon mode" << endl;
	// save the processId	
	ofstream ofp;
	ofp.open(PIDFILENAME);
	if(ofp.is_open())
	{
		//ofp << pi.dwProcessId << endl << pi.dwThreadId << endl;
		char	acProId[64] = {0};
		char	acThrId[64] = {0};
		sprintf(acProId, "%d", pi.dwProcessId);
		sprintf(acThrId, "%d", pi.dwThreadId);
		ofp << acProId << endl << acThrId << endl;
		ofp.close();
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	exit(0);

#else

	gid_t   gid;
	gid = getgid();
	setgroups(1, &gid);

	cout << "Using daemon mode" << endl;

	pid_t runningPID = getRunningPID();
	if(runningPID > 0)
	{
		cout << argv[0] << " already running, PID is " << runningPID << endl;
		exit(12);
	}
	sigBlock();
	makeDaemon();

	// daemon process will go on
	#ifdef __linux__
	prctl(PR_SET_DUMPABLE,1,42,42,42);
	#endif

	rlimit          rl;
	getrlimit( RLIMIT_CORE, &rl );
	if ( rl.rlim_max != -1 ) {
		rl.rlim_max     = -1;
	};
	rl.rlim_cur     = rl.rlim_max;
	if ( setrlimit( RLIMIT_CORE, &rl ) != 0 ){
		printf("ERRO: fail to setrlimit, %s\n", 
                        "" );
			//strerror(errno) );
	};
#endif
}

#ifdef WIN32
class ShineService : public NTService
{
public:
	ShineService(Commander& commander)

		: NTService("","",""),commander_(commander)
	{

	}
	virtual bool OnInit()
	{
		return true;
	}
	virtual void Run()
	{
		NTService::Run();
	}
	virtual void OnStop()
	{
		commander_.stopService();
	}
private:
	Commander& commander_;
};

int doService(int argc, char* argv[])
{
	std::string modpath = util::FileSystem::getModulePath();
	SetCurrentDirectory(modpath.c_str());
	Commander cmd;
	ShineService ntservice(cmd);
	if (!ntservice.ParseStandardArgs(argc, argv)) {
		ntservice.StartService();
	}
	return ntservice.m_status.dwWin32ExitCode;
}
#else
int doService(int argc, char* argv[]){
	createChild(argc,argv);
        Commander cmd;
        cmd.startService(2007);
        sigWait();
}
#endif



boost::shared_ptr<Service> createService(){
	 boost::shared_ptr<Service> te;
	 return te;
};




int main(int argc, char** argv) {

#if defined(WIN32) && defined(_DEBUG)
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	std::locale::global(std::locale(""));
	doService(argc,argv);
	return 0;
}