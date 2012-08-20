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
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifdef WIN32
#include <Windows.h>
#include <direct.h>
#else
#include <sys/types.h>
#include <unistd.h>
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
		char path[PATH_MAX + 1] = {0};
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
		char path[PATH_MAX + 1] = {0};
		getcwd(path, sizeof(path) - 1);
		result = path;
#endif

		return result;
	}

	std::string getCurrentExeFileDir()
	{
		return getDirName(getCurrentExeFilePath().c_str());
	}

	void setEnv(const char* name, const char* value)
	{
		assert(NULL != name);
		assert(NULL != value);

		std::string envFull = name;
		envFull += "=";
		envFull += value;

		char* newEnv = (char *)malloc(envFull.length() + 1);
		memset(newEnv, 0, envFull.length() + 1);
		strcat(newEnv, envFull.c_str());

#ifdef WIN32
		_putenv(newEnv);
#else
		putenv(newEnv);
		//setenv(name, value, 1);
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

	void addLibPath(const char* path)
	{
		assert(NULL != path);

#if defined(WIN32)
		const char* libPath = "PATH";
#elif defined(AIX)
		const char* libPath = "LIBPATH";
#elif defined(HPUX)
		const char* libPath = "SHLIB_PATH";
#else
		const char* libPath = "LD_LIBRARY_PATH";
#endif
		const char* envLibPath = getenv(libPath);
		std::string pathValue = path;
		pathValue += PATH_SEPARATOR;
		pathValue += (envLibPath != NULL) ? envLibPath : "";
		setEnv(libPath, pathValue.c_str());
	}

	std::string getLibPath()
	{
#if defined(WIN32)
		const char* libPath = "PATH";
#elif defined(AIX)
		const char* libPath = "LIBPATH";
#elif defined(HPUX)
		const char* libPath = "SHLIB_PATH";
#else
		const char* libPath = "LD_LIBRARY_PATH";
#endif
		const char* envLibPath = getenv(libPath);

		return (envLibPath != NULL) ? envLibPath : "";
	}

	std::string getDirName(const char* path)
	{
		assert(NULL != path);
		std::string result = path;
		std::string::size_type pos = result.find_last_of(FILE_SEPARATOR);
		if(pos != std::string::npos) {
			return result.substr(0, pos);
		}

		return result;
	}
}
