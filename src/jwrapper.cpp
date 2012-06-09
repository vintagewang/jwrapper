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
#include "JavaConfig.h"
#include "JWUtil.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	bool result = JavaConfig::getInstance()->load();
	if(result) {
		JavaConfig::getInstance()->printAll();
	}

	system("PAUSE");
	return 0;
}
