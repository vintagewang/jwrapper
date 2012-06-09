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
	this->javaHome = pt.get<string>("java.javahome");
	this->mainClass = pt.get<string>("java.mainclass");

	BOOST_AUTO(child, pt.get_child("java.classpaths"));
	for(BOOST_AUTO(pos, child.begin());
	    pos != child.end();
	    ++pos) {
		this->classPathList.push_back(pos->second.data());
	}
	return true;
}

void JavaConfig::printAll()
{
	printf("JAVA_HOME = [%s]\n", this->javaHome.c_str());
	printf("MAIN CLASS = [%s]\n", this->mainClass.c_str());
	for(size_t i = 0; i < this->classPathList.size(); i++) {
		printf("CLASS PATH %2d = [%s]\n", i, this->classPathList[i].c_str());
	}

	printf("EXE = [%s]\n", this->getConfigFile().c_str());
}

std::string JavaConfig::getConfigFile()
{
	return JWUtil::getCurrentExeFilePath() + ".xml";
}
