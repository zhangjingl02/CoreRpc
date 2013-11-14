#pragma once
#ifndef _H_COMMON_STARTUP_SERVICE_H
#define _H_COMMON_STARTUP_SERVICE_H
#include <string>
#include <boost/shared_ptr.hpp>
class Service{
public:
	Service(std::string name,std::string version,std::string dispname);

	virtual bool start()=0;
	virtual void stop()=0;

	const char* versioninfo(){return versionInfo_.c_str();};
	const char* name(){return name_.c_str();};
	const char* version(){return version_.c_str();};
	const char* displayName(){return displayName_.c_str();};
private:
	std::string name_;
	std::string version_;	
	std::string displayName_;
	std::string versionInfo_;

};

boost::shared_ptr<Service> createService();

#endif