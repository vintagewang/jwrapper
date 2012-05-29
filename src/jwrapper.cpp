#include "stdafx.h"
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/std/utility.hpp>
using namespace boost::property_tree;
using std::cout;
using std::endl;
using std::string;

void test_ptree()
{
	ptree pt;
	read_xml("jwrapper.xml", pt);
	cout << pt.get<string>("java.javahome") << endl;
	cout << pt.get<string>("java.mainclass") << endl;

	BOOST_AUTO(child, pt.get_child("java.classpaths"));
	for (BOOST_AUTO(pos, child.begin());
		pos != child.end();
		++pos)
	{
		cout << pos->second.data()<< ",";
	}
}

int main(int argc, char** argv)
{
	printf("Hello World.\n");
	test_ptree();
	return 0;
}

