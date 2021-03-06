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
#ifndef _JW_JWUTIL_H__
#define _JW_JWUTIL_H__
#include <string>

#ifdef WIN32
#define FILE_SEPARATOR "\\"
#define PATH_SEPARATOR ";"
#else
#define FILE_SEPARATOR "/"
#define PATH_SEPARATOR ":"
#endif

namespace JWUtil
{
	/**
	 * 获取工作目录
	 */
	std::string getWorkingDir();

	/**
	 * 获取当前程序可执行程序所在目录
	 */
	std::string getCurrentExeFileDir();

	/**
	 * 获取当前程序可执行程序的全路径，含文件名
	 */
	std::string getCurrentExeFilePath();

	/**
	 * 设置环境变量
	 */
	void setEnv(const char* name, const char* value);

	/**
	 * 字符串替换
	 */
	void replaceAll(std::string& source, const char* oldString, const char* newString);

	void addLibPath(const char* path);

	std::string getLibPath();

	/**
	 * 获取DIRNAME
	 * path 包含文件名的全路径
	 */
	std::string getDirName(const char* path);
};

#endif // end of _JW_JWUTIL_H__
