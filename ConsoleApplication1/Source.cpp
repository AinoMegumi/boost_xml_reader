#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <codecvt>
#include <locale> 
using namespace boost::property_tree;

auto data(const char* filename, const char* node_path) {
	ptree pt;
	read_xml(filename, pt);
	auto node = pt.get_optional<std::string>(node_path);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	return convert.from_bytes(node.get());
}

int main(void) {
	std::wcout << data("D:/question.xml", "questionbook.questiondata.question") << std::endl;
	return 0;
}