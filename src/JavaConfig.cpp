#include "JavaConfig.h"
#include "JWUtil.h"
#include <string>
#include <stdio.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/std/utility.hpp>

using namespace boost::property_tree;
using std::string;

JavaConfig::JavaConfig()
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
		// java home
		const char* jh = getenv("JAVA_HOME");
		if(!jh) jh = "";
		this->javaHome = pt.get("java.javahome", jh);

		// JVM Type
		this->jvmType = pt.get<string>("java.jvmtype");

		// Main class
		this->mainClass = pt.get<string>("java.mainclass");

		// Class path
		BOOST_AUTO(child, pt.get_child("java.classpaths"));
		for(BOOST_AUTO(pos, child.begin());
		    pos != child.end();
		    ++pos) {
			this->classPathList.push_back(pos->second.data());
		}
	} catch(const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
		return false;
	} catch(...) {
		fprintf(stderr, "Unexpected exception.%s\n");
		return false;
	}

	return true;
}

void JavaConfig::printAll()
{
	printf("javaHome = [%s]\n", this->javaHome.c_str());
	printf("jvmType = [%s]\n", this->jvmType.c_str());
	printf("mainClass = [%s]\n", this->mainClass.c_str());
	
	for(size_t i = 0; i < this->classPathList.size(); i++) {
		printf("classPathList %2d = [%s]\n", i, this->classPathList[i].c_str());
	}

	printf("EXE = [%s]\n", this->getConfigFile().c_str());
}

std::string JavaConfig::getConfigFile()
{
	return JWUtil::getCurrentExeFilePath() + ".xml";
}
