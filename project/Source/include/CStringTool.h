#ifndef CSTRINGTOOL_H
#define CSTRINGTOOL_H

#include <vector>
#include <string>

class CStringTool
{
	public:

		int SplitString(std::string InputString, std::vector<std::string>* ResultVector, char SplitChar);

		template <typename T>
		T StringTo(const std::string& str);
};

#include <CStringTool.hpp>

#endif
