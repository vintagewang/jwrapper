#include "JavaConfig.h"

//void test_ptree()
//{
//	ptree pt;
//	read_xml("jwrapper.xml", pt);
//	cout << pt.get<string>("java.javahome") << endl;
//	cout << pt.get<string>("java.mainclass") << endl;
//
//	BOOST_AUTO(child, pt.get_child("java.classpaths"));
//	for(BOOST_AUTO(pos, child.begin());
//	    pos != child.end();
//	    ++pos)
//	{
//		cout << pos->second.data() << ",";
//	}
//}

int main(int argc, char** argv)
{
	bool result = JavaConfig::getInstance()->load();
	if(result) {
		JavaConfig::getInstance()->printAll();
	}
	return 0;
}

