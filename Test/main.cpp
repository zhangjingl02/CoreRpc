/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2013年9月23日, 上午11:32
 */
#ifdef WIN32
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <cstdlib>
#include <iostream>
#include "rpc.pb.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	
	TransferMessage tm;
	tm.set_command(TransferMessage::Command::TransferMessage_Command_Login);
	tm.set_message("hahahah");

	cout<<tm.message()<<endl;
	cin.get();
    return 0;
}

