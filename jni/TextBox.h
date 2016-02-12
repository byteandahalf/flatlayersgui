#pragma once

#include <string>

struct TextBox
{
	char filler[48];
	std::string text;

	const std::string& getText() const;
	void setTextboxText(const std::string&);
};
