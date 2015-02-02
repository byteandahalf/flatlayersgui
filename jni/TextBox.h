#pragma once

#include <string>

class TextBox {
public:
	char filler[128];
	std::string text;

	std::string getText() const; // crashes :(
	void setTextboxText(std::string const&);
};