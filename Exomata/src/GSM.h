#pragma once
#include "empch.h"

enum class GameStates {
	MainMenu, 
	Level1, 
	Restart,
	Quit
};

GameStates PrevState;
GameStates CurrState;
GameStates NextState;

void (*GS_init) ();
void (*GS_update) ();
void (*GS_unload) ();

void GSMInit(GameStates StartState);
void GSMUpdate();