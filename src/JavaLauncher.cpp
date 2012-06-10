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
#include "JavaLauncher.h"
#include "JavaConfig.h"
#include "DLL.h"

#define NULL_CHECK0(e) if ((e) == 0) return 0
#define NULL_CHECK(e) if ((e) == 0) return

JavaLauncher::JavaLauncher()
{
}

JavaLauncher::~JavaLauncher()
{
}

JavaLauncher* JavaLauncher::getInstance()
{
	static JavaLauncher *singleton = new JavaLauncher();
	return singleton;
}

int JavaLauncher::launchJavaApp(int argc, char** argv)
{
	// 1, 获取JVM动态库全路径
	std::string jvmPath = JavaConfig::getInstance()->getJVMDllPath();

	// 2, 定义DLL对象，并加载JVM动态库
	DLL jvmDll(jvmPath.c_str());

	// 3, 获取创建JVM的函数指针
	typedef jint(JNICALL *CreateJVMFun)(JavaVM**, void**, void*);
	CreateJVMFun createJVMFun = (CreateJVMFun)jvmDll.getFunction("JNI_CreateJavaJVM");
	if(NULL == createJVMFun){
		fprintf(stderr, "Load JVM error %s\n", jvmPath.c_str());
		return -1;
	}
	JavaConfig::getInstance()->printLog("Get JVM function OK.");

	// 4, 创建JVM
	JavaVMInitArgs jvmArgs;

	return 0;
}

void JavaLauncher::exitHandler(int code)
{

}

void JavaLauncher::abortHandler(int code)
{

}

jobject JavaLauncher::newPlatformString(JNIEnv *env, char *s)
{
	int len = (int)strlen(s);
	jclass cls;
	jmethodID mid;
	jbyteArray ary;
	jobject enc;

	if(s == NULL)
		return 0;
	enc = getPlatformEncoding(env);

	ary = env->NewByteArray(len);
	if(ary != 0) {
		jobject str = 0;
		env->SetByteArrayRegion(ary, 0, len, (jbyte *)s);
		if(!env->ExceptionOccurred()) {
			if(isEncodingSupported(env, enc) == JNI_TRUE) {
				NULL_CHECK0(cls = env->FindClass("java/lang/String"));
				NULL_CHECK0(mid = env->GetMethodID(cls, "<init>",
				                                   "([BLjava/lang/String;)V"));
				str = env->NewObject(cls, mid, ary, enc);
			} else {
				/*If the encoding specified in sun.jnu.encoding is not
				endorsed by "Charset.isSupported" we have to fall back
				to use String(byte[]) explicitly here without specifying
				the encoding name, in which the StringCoding class will
				pickup the iso-8859-1 as the fallback converter for us.
				*/
				NULL_CHECK0(cls = env->FindClass("java/lang/String"));
				NULL_CHECK0(mid = env->GetMethodID(cls, "<init>",
				                                   "([B)V"));
				str = env->NewObject(cls, mid, ary);
			}
			env->DeleteLocalRef(ary);
			return str;
		}
	}
	return 0;
}

jobject JavaLauncher::getPlatformEncoding(JNIEnv *env)
{
	jobject platformEncoding = NULL;

	if(platformEncoding == NULL) {
		jstring propname = env->NewStringUTF("sun.jnu.encoding");
		if(propname) {
			jclass cls;
			jmethodID mid;
			NULL_CHECK0(cls = env->FindClass("java/lang/System"));
			NULL_CHECK0(mid = env->GetStaticMethodID(cls,
			                  "getProperty",
			                  "(Ljava/lang/String;)Ljava/lang/String;"));
			platformEncoding = env->CallStaticObjectMethod(
			                       cls, mid, propname);
		}
	}
	return platformEncoding;
}

jboolean JavaLauncher::isEncodingSupported(JNIEnv *env, jobject enc)
{
	jclass cls;
	jmethodID mid;
	NULL_CHECK0(cls = env->FindClass("java/nio/charset/Charset"));
	NULL_CHECK0(mid = env->GetStaticMethodID(
	                      cls,
	                      "isSupported",
	                      "(Ljava/lang/String;)Z"));
	return env->CallStaticBooleanMethod(cls, mid, enc);
}

void JavaLauncher::reportErrorMessage(JNIEnv* env, const char* errorMsg /*= NULL*/)
{
	if(env->ExceptionOccurred()) {
		env->ExceptionDescribe();
	} else if(errorMsg != NULL) {
		fprintf(stderr, "%s\n", errorMsg);
	}
}
