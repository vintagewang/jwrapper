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
#ifndef _JW_DLL_H__
#define _JW_DLL_H__
#ifdef WIN32
#include <Windows.h>
#include <WinBase.h>
typedef HINSTANCE DLL_T;
#else
#include <dlfcn.h>
typedef void* DLL_T;
#endif

class DLL
{
	DLL_T dll;

public:
	DLL(const char* file);
	~DLL();
	void* getFunction(const char* functionName);
};

#endif // end of _JW_DLL_H__
