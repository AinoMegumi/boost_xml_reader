#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <codecvt>
#include <locale> 
template<typename T> void replace_all(std::basic_string<T>& str, const std::basic_string<T>& old_str, const std::basic_string<T>& new_str) {
	for (size_t i = str.find_first_of(old_str); std::string::npos != i; i = str.find(old_str, i + new_str.length())) {
		str.replace(i, old_str.length(), new_str);
	}
}
template<typename T> void replace_all(std::basic_string<T>& str, const T* old_str, const T* new_str) {
	replace_all(str, std::basic_string<T>(old_str), std::basic_string<T>(new_str));
}
auto read_question(const std::string& filename) {
	std::vector<std::wstring> re;
	boost::property_tree::ptree pt;
	read_xml(filename, pt);
	static_assert(sizeof(wchar_t) == 2, "In function 'read_question' : Please check usage of 'std::codecvt_utf8_utf16'");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	for (auto& i : pt.get_child(u8"questionbook")) {
		auto node_question = i.second.get_optional<std::string>(u8"question");
		if (node_question) {
			auto str = convert.from_bytes(node_question.get());
			replace_all(str, L"\\n", L"\n");
			re.push_back(std::move(str));
		}
	}
	return re;
}
int main(void) {
	try {
#ifdef _MSC_VER
		std::wcout.imbue(std::locale("japanese"));//locale設定
#else
		std::wcout.imbue(std::locale(""));//locale設定
#endif
		const auto questions = read_question(u8"question.xml");
		for (auto& s : questions) std::wcout << s << std::endl << std::endl;
	}
	catch (std::exception& er) {
		std::cerr << er.what() << std::endl;
	}
	return 0;
}