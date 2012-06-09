#ifndef _JW_JWUTIL_H__
#define _JW_JWUTIL_H__
#include <string>

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
};

#endif // end of _JW_JWUTIL_H__
