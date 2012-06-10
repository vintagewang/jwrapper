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
#include "JWUtil.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef WIN32
#define FILE_SEPARATOR "\\"
#else
#define FILE_SEPARATOR "/"
#endif

namespace JWUtil
{
	std::string getCurrentExeFilePath()
	{
		std::string result;
#ifdef WIN32
		char path_buffer[_MAX_PATH + 1] = {0};
		char drive[_MAX_DRIVE + 1] = {0};
		char dir[_MAX_DIR + 1] = {0};
		char fname[_MAX_FNAME + 1] = {0};
		char ext[_MAX_EXT + 1] = {0};

		GetModuleFileNameA(NULL, path_buffer, sizeof(path_buffer) - 1);
		_splitpath(path_buffer, drive, dir, fname, ext);

		result += drive;
		result += dir;
		result += fname;
#else
		char proc[64] = {0};
		sprintf(proc, "/proc/%d/exe", getpid());
		char path[MAX_PATH + 1] = {0};
		readlink(proc, path, sizeof(path) - 1);
		result = path;
#endif

		return result;
	}

	std::string getWorkingDir()
	{
		std::string result;
#ifdef WIN32
		char path[_MAX_PATH + 1] = {0};
		_getcwd(path, sizeof(path) - 1);
		result =  path;
#else
		char path[MAX_PATH + 1] = {0};
		getcwd(path, sizeof(path) - 1);
		result = path;
#endif

		return result;
	}

	std::string getCurrentExeFileDir()
	{
		std::string result = getCurrentExeFilePath();
		std::string::size_type pos = result.find_last_of(FILE_SEPARATOR);
		if(pos != std::string::npos) {
			return result.substr(0, pos);
		}

		return result;
	}

	void setEnv(const char* name, const char* value)
	{
		assert(NULL != name);
		assert(NULL != value);

#ifdef WIN32
		std::string envFull = name;
		envFull += "=";
		envFull += value;
		_putenv(envFull.c_str());
#else
		setenv(name, value, 1);
#endif
	}

	void replaceAll(std::string& source, const char* oldString, const char* newString)
	{
		assert(NULL != oldString);
		assert(NULL != newString);

		while(true) {
			std::string::size_type pos = 0;
			if((pos = source.find(oldString)) != std::string::npos) {
				source.replace(pos, strlen(oldString), newString);
			} else {
				break;
			}
		}
	}
}
