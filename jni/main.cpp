#include "CreateWorldScreen.h"
#include <substrate.h>
#include <dlfcn.h>
#include <jni.h>



JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void* clicked = dlsym(RTLD_DEFAULT, "_ZN17CreateWorldScreen13buttonClickedEP6Button");
	MSHookFunction(clicked, (void*) &CreateWorldScreen$buttonClicked, (void**) &_CreateWorldScreen$buttonClicked);
	MSHookFunction((void*) &CreateWorldScreen::_getGameMode, (void*) &CreateWorldScreen$_getGameMode, (void**) &_CreateWorldScreen$_getGameMode);
	return JNI_VERSION_1_2;
}