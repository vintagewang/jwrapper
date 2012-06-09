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
	static bool expandMacro(std::string& value);
};

#endif // end of _JW_JAVA_CONFIG_H__
