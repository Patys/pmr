#include "Util.hpp"

std::string Util::addBreaksToText(const std::string& text, int max_characters_in_line)
{
	std::string return_text = "";
	
	for(int i = 0; i < text.length(); i++)
	{
		if((i%max_characters_in_line) == 0)
			return_text += "\n";
		return_text += text[i];
	}
	return return_text;
}
