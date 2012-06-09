#ifndef _JW_JAVA_CONFIG_H__
#define _JW_JAVA_CONFIG_H__
#include <string>
#include <map>
#include <vector>

typedef std::vector<std::string> ClassPathList;

class JavaConfig
{
public:

	JavaConfig();
	~JavaConfig();
	static JavaConfig* getInstance();

	bool load();

	void printAll();

private:
	static std::string getConfigFile();

private:
	std::string javaHome;
	std::string mainClass;
	ClassPathList classPathList;
};

#endif // end of _JW_JAVA_CONFIG_H__
