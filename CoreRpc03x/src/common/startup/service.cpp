#include "service.h"
#include <boost/format.hpp>
static const int NAME_LENGTH = 16;
static const int VERSION_LENGTH = 16; 
Service::Service(std::string name,std::string version,std::string dispname):
		name_(name),version_(version),displayName_(dispname){

			name_ = name;
	versionInfo_ = version;
	displayName_ = dispname;

	versionInfo_ = "VER:";
	versionInfo_ += name.substr(0, NAME_LENGTH);
	for (int i=0; i< (int)(NAME_LENGTH- name.size()); i++)
		versionInfo_ += " ";

	versionInfo_ += version.substr(0, VERSION_LENGTH);
	for (int i=0; i< (int)(VERSION_LENGTH+1-version.size()); i++)
		versionInfo_ += " ";

	versionInfo_ += " build:";
	versionInfo_ +=" build:";
	char month[10];
	int day;
	int year;
	sscanf(__DATE__,"%s %d %d", &month, &day, &year);

	int imonth = 0;
	if (strcmp(month, "Jan") == 0 )
		imonth = 1;
	else if (strcmp(month, "Feb") == 0 )
		imonth = 2;
	else if (strcmp(month, "Mar") == 0 )
		imonth = 3;
	else if (strcmp(month, "Apr") == 0 )
		imonth = 4;
	else if (strcmp(month, "May") == 0 )
		imonth = 5;
	else if (strcmp(month, "Jun") == 0 )
		imonth = 6;
	else if (strcmp(month, "Jul") == 0 )
		imonth = 7;
	else if (strcmp(month, "Aug") == 0 )
		imonth = 8;
	else if (strcmp(month, "Sep") == 0 )
		imonth = 9;
	else if (strcmp(month, "Oct") == 0 )
		imonth = 10;
	else if (strcmp(month, "Nov") == 0 )
		imonth = 11;
	else if (strcmp(month, "Dec") == 0 )
		imonth = 12;
	
	versionInfo_ += str(boost::format("%4d-%02d-%02d ")%year%imonth%day);
		//StringUtil::format("%4d-%02d-%02d ", year, imonth, day);
	version_+= str(boost::format("%4d-%02d-%02d ")%year%imonth%day);
	//version_ += StringUtil::format("%4d-%02d-%02d ", year, imonth, day);
	versionInfo_ += __TIME__;

}