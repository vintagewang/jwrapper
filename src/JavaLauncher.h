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
#ifndef _JW_JAVA_LAUNCHER_H__
#define _JW_JAVA_LAUNCHER_H__
#include <jni.h>
#include <string>

class JavaLauncher
{
	int exitCode;
	int abortCode;

	bool exited;
	bool aborted;

public:
	JavaLauncher();
	~JavaLauncher();
	static JavaLauncher* getInstance();

	int launchJavaApp(int argc, char** argv);
	void setExitCode(int code);
	void setAbortCode(int code);
	static void exitHandler(int code);
	static void abortHandler(int code);

private:
	static jobject newPlatformString(JNIEnv *env, char *s);
	static jobject getPlatformEncoding(JNIEnv *env);
	static jboolean isEncodingSupported(JNIEnv *env, jobject enc);
	static jobjectArray newPlatformStringArray(JNIEnv *env, char **strv, int strc);
	static void reportErrorMessage(JNIEnv* env, const char* errorMsg = NULL);
};

#endif // end of _JW_JAVA_LAUNCHER_H__
