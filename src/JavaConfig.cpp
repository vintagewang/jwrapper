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
#include <string>
#include <stdio.h>
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
				this->propertyTable[pos->first.data()] = pos->second.data();
			}
		}

		// Class Path
		{
			BOOST_AUTO(child, pt.get_child("java.classpaths"));
			for(BOOST_AUTO(pos, child.begin());
			    pos != child.end();
			    ++pos) {
				this->classPathList.push_back(pos->second.data());
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


	JWUtil::setEnv("JAVA_HOME", this->javaHome.c_str());

	return true;
}

void JavaConfig::printAll()
{
	if(this->debug) {
		printf("javaHome = [%s]\n", this->javaHome.c_str());
		printf("jvmType = [%s]\n", this->jvmType.c_str());
		printf("mainClass = [%s]\n", this->mainClass.c_str());

		for(size_t i = 0; i < this->classPathList.size(); i++) {
			printf("classPathList %2d = [%s]\n", i, this->classPathList[i].c_str());
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

			}
			// 当前工作目录
			else if(var == "cwd") {

			}
			// 环境变量
			else {

			}
		}
	}

	return result;
}
