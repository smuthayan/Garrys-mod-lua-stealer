#include "pch.h"
#include "Lua.h"
std::string Lua::IntToString(::std::uint64_t x)
{
	std::stringstream temp;
	temp << x;
	return temp.str();

}

void Lua::checkIfNameIsRepeat(std::string& string)
{

	// set it to string and increment

	for (std::size_t x = 0; x < filenameArray.size(); ++x) // find how many strings that are the same are in the array
	{

		if (filenameArray[x] == string)
		{
			++howManySameStrings;

		}



	}
	// put string in 
	filenameArray.resize(filenameArray.size() + 1);
	filenameArray[count] = string;
	if (howManySameStrings != 0)
	{
		string = string + "_" + IntToString(howManySameStrings);
	}
	++count;
	howManySameStrings = 0;
}

void Lua::removeIllegalChars(std::string& string)
{

	for (int x = 0; x < string.length(); ++x)
	{
		if (string[x] == '<' ||
			string[x] == '>' ||
			string[x] == ':' ||
			string[x] == '"' ||
			string[x] == '/' ||
			string[x] == '\\' ||
			string[x] == '|' ||
			string[x] == '?' ||
			string[x] == '*')
		{
			string[x] = '_';
		}
	}

}