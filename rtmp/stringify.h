#pragma once

#include <string>
#include <sstream>

template<typename T>
static std::string stringify(const T& value){
	std::stringstream stream;
	stream << std::fixed << value;
	return stream.str();
}
