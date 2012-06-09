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
#else
#endif

		return result;
	}
}
