#pragma once

struct Button;
struct ImageButton;
struct TextBox;
struct Label;

#include <string>
#include <vector>
#include <memory>

struct Screen
{
	char data[136]; // 0
};

struct CreateWorldScreen : public Screen
{
	bool isAdvanced; // 136
	bool isFlatWorld; // 137
	char filler[16]; // 140
	int gameType; // 156
	int generator; // 160
	std::vector<std::shared_ptr<ImageButton>> gameTypeButtons; // 164
	std::vector<std::shared_ptr<ImageButton>> generatorButtons; // 176
	Button& selectedGameTypeButton; // 188
	int idk; // 192
	Button& selectedGeneratorButton; // 196
	int idk2; // 200
	Button& createWorldButton; // 204
	int idk3; // 208
	Button& closeBtn; // 212
	char filler2[52]; // 216
	TextBox& worldNameBox; // 268
	int idk4; // 272
	TextBox& seedBox; // 276
	int idk5; // 280
	Label& worldNameLabel; // 284
	Label& seedLabel; // 288

	bool _isOneOf(Button&, std::vector<std::shared_ptr<ImageButton>>&, int&) const;
	void _buttonClicked(Button&);
	int _getGameMode();
};
