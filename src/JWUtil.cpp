#include "JWUtil.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <Windows.h>
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
#endif

		return result;
	}

	std::string getWorkingDir()
	{
		std::string result;
#ifdef WIN32
		char path_buffer[_MAX_PATH + 1] = {0};
		_getcwd(path_buffer, sizeof(path_buffer) - 1);
		result =  path_buffer;
#else
		char path_buffer[MAX_PATH + 1] = {0};
		getcwd(path_buffer, sizeof(path_buffer) - 1);
		result = path_buffer;
#endif

		return result;
	}

	std::string getCurrentExeFileDir()
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
#else
#endif

		return result;
	}
}
