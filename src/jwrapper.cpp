#include "JavaConfig.h"

int main(int argc, char** argv)
{
	bool result = JavaConfig::getInstance()->load();
	if(result) {
		JavaConfig::getInstance()->printAll();
	}
	return 0;
}

