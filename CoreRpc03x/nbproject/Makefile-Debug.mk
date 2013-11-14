#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/common/buffer/byte_buffer.o \
	${OBJECTDIR}/src/common/buffer/shared_buffer.o \
	${OBJECTDIR}/src/common/buffer/shared_buffer_list.o \
	${OBJECTDIR}/src/common/net/io_service_pool.o \
	${OBJECTDIR}/src/common/net/message_dispatcher.o \
	${OBJECTDIR}/src/common/net/service_skeleton.o \
	${OBJECTDIR}/src/common/net/tcp_client.o \
	${OBJECTDIR}/src/common/net/tcp_connection.o \
	${OBJECTDIR}/src/common/net/tcp_server.o \
	${OBJECTDIR}/src/common/rpc/protobuf_decoder.o \
	${OBJECTDIR}/src/common/rpc/rpc.pb.o \
	${OBJECTDIR}/src/common/rpc/rpc_channel.o \
	${OBJECTDIR}/src/common/rpc/rpc_factory.o \
	${OBJECTDIR}/src/common/rpc/rpc_service_skeleton.o \
	${OBJECTDIR}/src/common/startup/XnuxDaemon.o \
	${OBJECTDIR}/src/common/startup/commander.o \
	${OBJECTDIR}/src/common/startup/main.o \
	${OBJECTDIR}/src/common/startup/net_service.o \
	${OBJECTDIR}/src/common/startup/service.o \
	${OBJECTDIR}/src/common/startup/stdafx.o \
	${OBJECTDIR}/src/common/util/file_system.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lboost_system -lboost_thread -lglog -lprotobuf -lboost_locale

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk work/coreRpcwork

work/coreRpcwork: ${OBJECTFILES}
	${MKDIR} -p work
	${LINK.cc} -o work/coreRpcwork ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/common/buffer/byte_buffer.o: src/common/buffer/byte_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/buffer
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/buffer/byte_buffer.o src/common/buffer/byte_buffer.cpp

${OBJECTDIR}/src/common/buffer/shared_buffer.o: src/common/buffer/shared_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/buffer
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/buffer/shared_buffer.o src/common/buffer/shared_buffer.cpp

${OBJECTDIR}/src/common/buffer/shared_buffer_list.o: src/common/buffer/shared_buffer_list.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/buffer
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/buffer/shared_buffer_list.o src/common/buffer/shared_buffer_list.cpp

${OBJECTDIR}/src/common/net/io_service_pool.o: src/common/net/io_service_pool.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/net
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/net/io_service_pool.o src/common/net/io_service_pool.cpp

${OBJECTDIR}/src/common/net/message_dispatcher.o: src/common/net/message_dispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/net
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/net/message_dispatcher.o src/common/net/message_dispatcher.cpp

${OBJECTDIR}/src/common/net/service_skeleton.o: src/common/net/service_skeleton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/net
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/net/service_skeleton.o src/common/net/service_skeleton.cpp

${OBJECTDIR}/src/common/net/tcp_client.o: src/common/net/tcp_client.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/net
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/net/tcp_client.o src/common/net/tcp_client.cpp

${OBJECTDIR}/src/common/net/tcp_connection.o: src/common/net/tcp_connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/net
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/net/tcp_connection.o src/common/net/tcp_connection.cpp

${OBJECTDIR}/src/common/net/tcp_server.o: src/common/net/tcp_server.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/net
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/net/tcp_server.o src/common/net/tcp_server.cpp

${OBJECTDIR}/src/common/rpc/protobuf_decoder.o: src/common/rpc/protobuf_decoder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/rpc
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/rpc/protobuf_decoder.o src/common/rpc/protobuf_decoder.cpp

${OBJECTDIR}/src/common/rpc/rpc.pb.o: src/common/rpc/rpc.pb.cc 
	${MKDIR} -p ${OBJECTDIR}/src/common/rpc
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/rpc/rpc.pb.o src/common/rpc/rpc.pb.cc

${OBJECTDIR}/src/common/rpc/rpc_channel.o: src/common/rpc/rpc_channel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/rpc
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/rpc/rpc_channel.o src/common/rpc/rpc_channel.cpp

${OBJECTDIR}/src/common/rpc/rpc_factory.o: src/common/rpc/rpc_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/rpc
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/rpc/rpc_factory.o src/common/rpc/rpc_factory.cpp

${OBJECTDIR}/src/common/rpc/rpc_service_skeleton.o: src/common/rpc/rpc_service_skeleton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/rpc
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/rpc/rpc_service_skeleton.o src/common/rpc/rpc_service_skeleton.cpp

${OBJECTDIR}/src/common/startup/XnuxDaemon.o: src/common/startup/XnuxDaemon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/startup
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/startup/XnuxDaemon.o src/common/startup/XnuxDaemon.cpp

${OBJECTDIR}/src/common/startup/commander.o: src/common/startup/commander.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/startup
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/startup/commander.o src/common/startup/commander.cpp

${OBJECTDIR}/src/common/startup/main.o: src/common/startup/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/startup
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/startup/main.o src/common/startup/main.cpp

${OBJECTDIR}/src/common/startup/net_service.o: src/common/startup/net_service.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/startup
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/startup/net_service.o src/common/startup/net_service.cpp

${OBJECTDIR}/src/common/startup/service.o: src/common/startup/service.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/startup
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/startup/service.o src/common/startup/service.cpp

${OBJECTDIR}/src/common/startup/stdafx.o: src/common/startup/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/startup
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/startup/stdafx.o src/common/startup/stdafx.cpp

${OBJECTDIR}/src/common/util/file_system.o: src/common/util/file_system.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/common/util
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/common/util/file_system.o src/common/util/file_system.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} work/coreRpcwork

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
