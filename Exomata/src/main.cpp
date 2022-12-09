#include "main.h"
#include "GSM.h"

int main() {
	GSMInit(GameStates::MainMenu);
	while (CurrState != GameStates::Quit) {
		if (CurrState == GameStates::Restart) {
			NextState = CurrState = PrevState;
		}
		else {
			GSMUpdate();
		}
		GS_init();
		while (CurrState == NextState) {
			GS_update();
		}
		GS_unload();
		PrevState = CurrState;
		CurrState = NextState;
	}
	return 1;
}