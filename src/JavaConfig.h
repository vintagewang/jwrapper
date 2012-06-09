#ifndef _JW_JAVA_CONFIG_H__
#define _JW_JAVA_CONFIG_H__
#include <string>
#include <map>
#include <vector>

typedef std::vector<std::string> ClassPathList;
typedef std::vector<std::string> OptionList;
typedef std::map<std::string, std::string> PropertyTable;
typedef std::map<std::string, std::string> OptionTable;

class JavaConfig
{
	// Debug ?
	bool debug;
	// Java Home Dir
	std::string javaHome;
	// JVM Type
	std::string jvmType;
	// Main Class
	std::string mainClass;
	// Class Path List
	ClassPathList classPathList;
	// Java System Property
	PropertyTable propertyTable;
	// Java Options -X
	OptionTable optionTable;

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
