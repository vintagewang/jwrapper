/**
 * Copyright 2012 Wangxr, vintage.wang@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "JavaConfig.h"
#include "JWUtil.h"
#include "JavaLauncher.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/std/utility.hpp>

using namespace boost::property_tree;
using std::string;

#include <iostream>
using std::cout;
using std::endl;

JavaConfig::JavaConfig() : debug(false)
{
}

JavaConfig::~JavaConfig()
{
}

JavaConfig* JavaConfig::getInstance()
{
	static JavaConfig *singleton = new JavaConfig();
	return singleton;
}

bool JavaConfig::load()
{
	ptree pt;
	read_xml(getConfigFile().c_str(), pt);
	try {
		// Debug ?
		this->debug = pt.get<string>("java.debug") == "true";

		// Java Home
		const char* jh = getenv("JAVA_HOME");
		if(!jh) jh = "";
		this->javaHome = pt.get("java.javahome", jh);
		if(this->javaHome.empty()) {
			fprintf(stderr, "You must set JAVA_HOME environment variable or set it in config file.\n");
			return false;
		}

		if(!this->expandMacro(this->javaHome)) {
			return false;
		}

		JWUtil::setEnv("JAVA_HOME", this->javaHome.c_str());

		// JVM Type
		this->jvmType = pt.get<string>("java.jvmtype");

		// Main Class
		this->mainClass = pt.get<string>("java.mainclass");

		// Java System Property
		{
			BOOST_AUTO(child, pt.get_child("java.properties"));
			for(BOOST_AUTO(pos, child.begin());
			    pos != child.end();
			    ++pos) {
				std::string value = pos->second.data();
				if(this->expandMacro(value)) {
					this->propertyTable[pos->first.data()] = value;
				} else {
					return false;
				}
			}
		}

		// Class Path
		{
			BOOST_AUTO(child, pt.get_child("java.classpaths"));
			for(BOOST_AUTO(pos, child.begin());
			    pos != child.end();
			    ++pos) {
				std::string value = pos->second.data();
				if(this->expandMacro(value)) {
					this->classPathList.push_back(value);
				} else {
					return false;
				}
			}
		}

		// Java Options
		{
			BOOST_AUTO(child, pt.get_child("java.options"));
			for(BOOST_AUTO(pos, child.begin());
			    pos != child.end();
			    ++pos) {
				this->optionTable[pos->first.data()] = pos->second.data();
			}
		}

	} catch(const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
		return false;
	} catch(...) {
		fprintf(stderr, "Unexpected exception.\n");
		return false;
	}

	// 加载LIBPATH
	JWUtil::addLibPath(".");
	JWUtil::addLibPath(JWUtil::getCurrentExeFileDir().c_str());
	JWUtil::addLibPath((this->javaHome + "/jre/bin").c_str());



	return true;
}

void JavaConfig::printAll()
{
	if(this->debug) {
		printf("javahome = [%s]\n", this->javaHome.c_str());
		printf("jvmtype = [%s]\n", this->jvmType.c_str());
		printf("mainclass = [%s]\n", this->mainClass.c_str());
		{
			printf("properties:\n");
			PropertyTable::iterator it = this->propertyTable.begin();
			for(; it != this->propertyTable.end(); it++) {
				printf("\t %s = [%s]\n", it->first.c_str(), it->second.c_str());
			}
		}
		{
			printf("classpaths:\n");
			for(size_t i = 0; i < this->classPathList.size(); i++) {
				printf("\t %2d = [%s]\n", i, this->classPathList[i].c_str());
			}
		}
		{
			printf("options:\n");
			OptionTable::iterator it = this->optionTable.begin();
			for(; it != this->optionTable.end(); it++) {
				printf("\t %s = [%s]\n", it->first.c_str(), it->second.c_str());
			}
		}
	}
}

std::string JavaConfig::getConfigFile()
{
	return JWUtil::getCurrentExeFilePath() + ".xml";
}

bool JavaConfig::expandMacro(std::string& value)
{
	bool result = true;
	for(std::size_t start = 0; result
	    && std::string::npos != (start = value.find("${", start));) {
		start += 2;
		std::size_t end = value.find("}", start);
		result = end != std::string::npos;
		if(result) {
			std::string var = value.substr(start, end - start);

			// 可执行程序所在目录
			if(var == "cpd") {
				value.replace(start - 2, end - start + 3, JWUtil::getCurrentExeFileDir());
			}
			// 当前工作目录
			else if(var == "cwd") {
				value.replace(start - 2, end - start + 3, JWUtil::getWorkingDir());
			}
			// 环境变量
			else {
				const char* env = getenv(var.c_str());
				if(env != NULL) {
					value.replace(start - 2, end - start + 3, env);
				} else {
					fprintf(stderr, "The environment variable <%s> is not exist\n", var.c_str());
					result = false;
				}
			}
		}
	}

	return result;
}

void JavaConfig::printLog(const char* fmt, ...)
{
	if(this->debug) {
		const static int BUFFER_SIZE = 1024 * 2;
		char *buf = new char[BUFFER_SIZE + 1];
		va_list args;

		va_start(args, fmt);
		vsnprintf(buf, BUFFER_SIZE, fmt, args);
		va_end(args);

		printf("%s\n", buf);

		delete[] buf;
	}
}

std::string JavaConfig::getJVMDllPath()
{
	std::string result;
#if defined(WIN32)
	result += this->javaHome;
	result += "/jre/bin/";
	result += this->jvmType;
	result += "/jvm.dll";
#elif defined(SOLARIS_X86)
#if defined(ARCH64)
	result += this->javaHome;
	result += "/jre/lib/amd64";
	result += this->jvmType;
	result += "/libjvm.so";
#else
	result += this->javaHome;
	result += "/jre/lib/i386";
	result += this->jvmType;
	result += "/libjvm.so";
#endif
#elif defined(SOLARIS_X86)
#if defined(ARCH64)
	result += this->javaHome;
	result += "/jre/lib/sparcv9";
	result += this->jvmType;
	result += "/libjvm.so";
#else
	result += this->javaHome;
	result += "/jre/lib/sparc";
	result += this->jvmType;
	result += "/libjvm.so";
#endif
#elif defined(HPUX)
#if defined(ARCH64)
	result += this->javaHome;
	result += "/jre/lib/IA64W";
	result += this->jvmType;
	result += "/libjvm.so";
#else
	result += this->javaHome;
	result += "/jre/lib/IA64N";
	result += this->jvmType;
	result += "/libjvm.so";
#endif
#elif defined(LINUX)
#if defined(ARCH64)
	result += this->javaHome;
	result += "/jre/lib/amd64";
	result += this->jvmType;
	result += "/libjvm.so";
#else
	result += this->javaHome;
	result += "/jre/lib/i386";
	result += this->jvmType;
	result += "/libjvm.so";
#endif
#elif defined(AIX)
	result += this->javaHome;
	result += "/jre/bin/classic";
	result += this->jvmType;
	result += "/libjvm.a";
#endif

	return result;
}

std::string JavaConfig::getMainClass()
{
	std::string retString = this->mainClass;
	std::replace(retString.begin(), retString.end(), '.', '/');
	return retString;
}

void JavaConfig::buildJavaVMInitArgs(JavaVMInitArgs& args)
{
	int index = 0;

	OptionTable table;
	this->buildNewOptionTable(table);

	// 为JavaVMInitArgs分配内存
	args.nOptions = static_cast<jint>(table.size() + 2);
	args.options = new JavaVMOption[args.nOptions];

	// 设置JavaVMInitArgs
	args.version = JNI_VERSION_1_2;
	args.ignoreUnrecognized = JNI_FALSE;

	printLog("JavaVMInitArgs:");
	printLog("	version 0x%08x", args.version);
	printLog("	ignoreUnrecognized is %s", args.ignoreUnrecognized ? "JNI_TRUE" : "JNI_FALSE");
	printLog("	nOptions is %d", args.nOptions);

	OptionTable::const_iterator it = table.begin();
	for(index = 0; it != table.end(); it++, index++) {
		std::string optString = it->first + (it->second.length() > 0 ? "=" + it->second : "");

		char *key = new char[optString.length() + 1];
		memset(key, 0, optString.length() + 1);
		sprintf(key, "%s", optString.c_str());
		args.options[index].optionString = key;
		args.options[index].extraInfo = NULL;
		printLog("\toption[%2d] = '%s'", index, args.options[index].optionString);
	}

	{
		char *key = new char[32];
		memset(key, 0, 32);
		strcpy(key, "exit");
		args.options[index].optionString = key;
		args.options[index].extraInfo = (void*) JavaLauncher::exitHandler;
		printLog("\toption[%2d] = '%s'(JNI Invocation API JVM exit hook)", index, args.options[index].optionString);
	}

	{
		index++;
		char *key = new char[32];
		memset(key, 0, 32);
		strcpy(key, "abort");
		args.options[index].optionString = key;
		args.options[index].extraInfo = (void*) JavaLauncher::abortHandler;
		printLog("\toption[%2d] = '%s'(JNI Invocation API JVM abort hook)", index, args.options[index].optionString);
	}

}

void JavaConfig::buildNewOptionTable(OptionTable& table)
{
	table = this->optionTable;

	OptionTable::iterator it = this->propertyTable.begin();
	for(; it != this->propertyTable.end(); it++) {
		this->optionTable["-D" + it->first] = it->second;
	}

	// -Djava.class.path
	std::string javaClassPath = table["-Djava.class.path"];
	for(std::size_t i = 0; i < this->classPathList.size(); i++) {
		javaClassPath += this->classPathList[i];
		javaClassPath += PATH_SEPARATOR;
	}

	table["-Djava.class.path"] = javaClassPath;
}
