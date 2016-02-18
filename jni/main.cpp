#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include "substrate.h"

#include "CreateWorldScreen.h"
#include "ImageButton.h"
#include "TextBox.h"
#include "Label.h"

struct FlatLevelSource
{
	static std::string DEFAULT_LAYERS;
};

static void (*_CreateWorldScreen$_buttonClicked)(CreateWorldScreen*, Button&);
static void CreateWorldScreen$_buttonClicked(CreateWorldScreen* self, Button& button)
{
	static std::string _customLayers;
	static int _lastClicked;
	int entry;
	if(self->_isOneOf(button, self->generatorButtons, entry))
	{
		switch(entry)
		{
		case 2:
			_CreateWorldScreen$_buttonClicked(self, button);
			self->seedLabel.setText("Superflat layers");
			self->gameTypeButtons[0]->isActive = true;
			self->gameTypeButtons[1]->isActive = true;
			if(_lastClicked != 2)
				self->seedBox.setText(_customLayers);
			return;

		case 0:
		case 1:
			if(self->generator == 2)
			{
				_customLayers = self->seedBox.getText();
				self->seedBox.setText("");
				self->seedLabel.setText("Seed");
			}
			break;
		}

		_lastClicked = entry;
	}

	if(&button == &self->createWorldButton)
	{
		FlatLevelSource::DEFAULT_LAYERS = "[7,3,3,2]";
		if(self->isFlatWorld && self->seedBox.getText() != "")
		{
			FlatLevelSource::DEFAULT_LAYERS = self->seedBox.getText();
		}
	}

	_CreateWorldScreen$_buttonClicked(self, button);
}

static int (*_CreateWorldScreen$_getGameMode)(CreateWorldScreen*);
static int CreateWorldScreen$_getGameMode(CreateWorldScreen* self)
{
	// Workaround for Mojang forcing Creative Mode when creating a flat world
	return self->gameType;
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*) &CreateWorldScreen::_buttonClicked, (void*) &CreateWorldScreen$_buttonClicked, (void**) &_CreateWorldScreen$_buttonClicked);
	MSHookFunction((void*) &CreateWorldScreen::_getGameMode, (void*) &CreateWorldScreen$_getGameMode, (void**) &_CreateWorldScreen$_getGameMode);
	return JNI_VERSION_1_2;
}
