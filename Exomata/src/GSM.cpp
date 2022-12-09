#include "GSM.h"

void GSMInit(GameStates StartState) {

	// reset the current, previoud and next game
	PrevState = StartState;
	CurrState = StartState;
	NextState = StartState;

	// call the update to set the function pointers
	GSMUpdate();
}

void GSMUpdate() {
	if ((CurrState == GameStates::Restart) || (CurrState == GameStates::Quit)) {
		return;
	}
	switch (CurrState) {
	case GameStates::MainMenu:
		GS_init = ;
		GS_update = ;
		GS_unload = ;
		break;
	case GameStates::Level1:
		GS_init = ;
		GS_update = ;
		GS_unload = ;
		break;
	default:
		return;
	}
}