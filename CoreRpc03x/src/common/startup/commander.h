#ifndef _H_COMMON_STARTUP_COMMANDER_H
#define _H_COMMON_STARTUP_COMMANDER_H

#include <boost/shared_ptr.hpp>

#include <vector>

#include "Service.h"

class Commander
{
public:
	Commander();
	~Commander();
	bool startService(short alarmport);
	void stopService();

	void handleUICommand(const char* cmd);
	const char*  serviceVersion();
	const char*  serviceName();
	const char*  displayName();

private:
	boost::shared_ptr<Service>	service_;	// Ä£¿é
};

#endif