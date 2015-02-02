#pragma once

#include "Screen.h"
#include "Button.h"
#include "TextBox.h"
#include "Label.h"
#include "FlatLevelSource.h"

#include <string>
#include <vector>
#include <memory>

class CreateWorldScreen : public Screen {
public:
	bool isAdvanced; // 200
	bool isFlat; // 201
	char levelList_seed[18]; // 202
	int gamemode; // 220
	int generator; // 224
	std::vector<Button*, std::allocator<Button*>> gameModeBtns; // 228
	std::vector<Button*, std::allocator<Button*>> worldTypeBtns; // 240
	Button* selectedGameModeBtn; // 252
	Button* selectedWorldTypeBtn; // 256
	Button* createWorldBtn; // 260
	Button* closeBtn; // 264
	Button* headerBtn; // 268
	Button* advancedBtn; // 272
	Button* limitedWorldsErrorBtn; // 276
	TextBox* worldNameBox; // 280
	TextBox* seedBox; // 284
	Label* worldNameLabel; // 288
	Label* seedLabel; // 292
};


static void (*_CreateWorldScreen$buttonClicked)(CreateWorldScreen*, Button*);
static void CreateWorldScreen$buttonClicked(CreateWorldScreen* scrn, Button* btn) {
	if(btn == scrn->worldTypeBtns[2]) { // Superflat button
		scrn->seedLabel->setText("Superflat layers"); // custom text
		scrn->generator = 2;
		scrn->selectedWorldTypeBtn = btn;
		scrn->isFlat = true;
		scrn->gameModeBtns[0]->isActive = true; // Allow the survival and creative buttons
		scrn->gameModeBtns[1]->isActive = true; // to be clicked in superflat
		return;
	}
	if(btn == scrn->worldTypeBtns[0] || btn == scrn->worldTypeBtns[1]) { // old or infinite
		scrn->seedLabel->setText("Seed"); // reset the label to normal
	}

	if(btn == scrn->createWorldBtn && scrn->seedBox->text != "") {
		if(scrn->isFlat) FlatLevelSource::DEFAULT_LAYERS = scrn->seedBox->getText();
	} else FlatLevelSource::DEFAULT_LAYERS = "[7,3,3,2]";
	_CreateWorldScreen$buttonClicked(scrn, btn);
}

static int (*_CreateWorldScreen$_getGameMode)(CreateWorldScreen*);
static int CreateWorldScreen$_getGameMode(CreateWorldScreen* scrn) {
	// Workaround for Mojang forcing Creative Mode when creating a flat world
	return scrn->gametype;
}