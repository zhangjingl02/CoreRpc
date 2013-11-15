#include "commander.h"
#include <assert.h>
#include <stdio.h>
Commander::Commander()
{
	service_ = createService();
}

Commander::~Commander()
{
}

bool Commander::startService(short alarmport)
{


	if(service_)
	{
		
		assert(service_);
		
		FILE* fp = fopen("./version.txt", "wt");
		if(fp)
		{
			fprintf(fp, "%s\n", service_->versioninfo());
			fclose(fp);
		}

		if(service_->start())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void Commander::stopService()
{
	if(service_)
	{
		service_->stop();
	}
}

void Commander::handleUICommand(const char* cmd)
{
	
}

const char* Commander::serviceVersion()
{
	if(service_)
	{
		return service_->version();
	}
	return "";
}

const char* Commander::serviceName()
{
	if(service_)
	{
		return service_->name();
	}
	return "";
}

const char* Commander::displayName()
{
	if(service_)
		return service_->displayName();
	else
		return "";
}
