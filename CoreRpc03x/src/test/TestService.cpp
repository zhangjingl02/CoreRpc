#include "TestService.h"

boost::shared_ptr<Service> createService(){
    
    return boost::shared_ptr<Service>(new TestService());
    
}

void TestService::stop(){}
