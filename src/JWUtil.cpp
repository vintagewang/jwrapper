#include "JWUtil.h"
#include <Windows.h>

namespace JWUtil
{
	std::string getCurrentExeFilePath()
	{
		std::string result;
#ifdef WIN32
		char bufFileName[512 + 1] = {0};
		GetModuleFileNameA(NULL, bufFileName, sizeof(bufFileName) - 1);
		result = bufFileName;

		//
		// remove file extention
		//
		std::string::size_type pos = result.find_last_of('.');
		if(pos != std::string::npos) {
			result = result.substr(0, pos);
		}
#else
#endif

		return result;
	}
}
