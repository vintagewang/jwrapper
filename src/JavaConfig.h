#ifndef _JW_JAVA_CONFIG_H__
#define _JW_JAVA_CONFIG_H__
#include <string>
#include <map>
#include <vector>

typedef std::vector<std::string> ClassPathList;

class JavaConfig
{
	// Java Home Dir
	std::string javaHome;
	// JVM Type
	std::string jvmType;
	// Main Class
	std::string mainClass;
	// Class Path List
	ClassPathList classPathList;

public:
	JavaConfig();
	~JavaConfig();
	static JavaConfig* getInstance();

	bool load();

	void printAll();

private:
	static std::string getConfigFile();
};

#endif // end of _JW_JAVA_CONFIG_H__
