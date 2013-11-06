/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2013年9月23日, 上午11:32
 */
#ifdef WIN32
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;

class Test{

public:
	int a;
	std::string b;
};

typedef boost::shared_ptr<Test> test_ptr;
/*
 * 
 */
int main(int argc, char** argv) {
	std::map<int,int> map_;
	std::map<int,int>::iterator it=map_.find(1);
	

	vector<Test> v;
	Test t;
	v.push_back(t);
	t.a=4;

	

	cout<<t.a<<"|"<<v[0].a<<endl;
	
    return 0;
}

