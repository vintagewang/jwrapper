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
#include "DLL.h"
#include <assert.h>

DLL::DLL(const char* file) : dll(NULL)
{
	assert(NULL != file);

#ifdef WIN32
	this->dll = ::LoadLibraryA(file);
#else
	this->dll = dlopen(file, RTLD_NOW + RTLD_GLOBAL);
	if(NULL == this->dll) {
		fprintf(stderr, "dllopen error %s\n", dlerror());
	}
#endif
}

DLL::~DLL()
{
	if(NULL != this->dll) {
#ifdef WIN32
		::FreeLibrary(this->dll);
#else
		::dlclose(this->dll);
#endif
	}
}

void* DLL::getFunction(const char* functionName)
{
	assert(NULL != functionName);

	if(NULL != this->dll) {
#ifdef WIN32
		return (void*)::GetProcAddress(this->dll, functionName);
#else
		return (void*)::dlsym(this->dll, functionName);
#endif
	}

	return NULL;
}
