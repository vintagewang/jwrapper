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
