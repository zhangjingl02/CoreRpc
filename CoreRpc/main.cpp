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
	//test
	net::NetBuffer buffer;
	 auto func = [] () { cout << "Hello world"; };  
    func(); // now call the functionaa
	 cin.get();
    return 0;
}

