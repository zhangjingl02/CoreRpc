/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2013年9月17日, 下午1:09
 */

#include <cstdlib>
#include <iostream>
#include "src\common\net\net_buffer.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	
	net::NetBuffer buffer;

	buffer.appendInt32((int32_t)65);
	buffer.appendInt32((int32_t)-98);

	int32_t a=buffer.readInt32();
	int32_t b=buffer.readInt32();
	int32_t c=buffer.readInt32();
	cout << "Hello world"<<a<<"|"<<b<<endl;
	 auto func = [] () { cout << "Hello world"<<endl; };  
    func(); // now call the functionaa
	 cin.get();
    return 0;
}

