#include "Assets.h"

// Menu
const char* Assets::MenuBackground = "images/Menu/Background.png";
const char* Assets::MenuTitle = "images/Menu/Game_Title.png";
const char* Assets::PlayButton = "images/Menu/Play_Button.png";
const char* Assets::PlayButtonClicked = "images/MainMenuScreen/Play_Button(Click).png";

// Game Scene
const char* Assets::Wall = "images/GameScreen/wallTexture.jpg";
const char* Assets::Wall3D = "images/GameScreen/wallTexture2D.png";
const char* Assets::Ceiling = "images/GameScreen/CeilingTexture.jpg";
const char* Assets::Floor = "images/GameScreen/GroundTexture.jpg";
const char* Assets::Upstairs = "images/GameScreen/Upstairs.jpg";
const char* Assets::Downstairs = "images/GameScreen/Downstairs.jpg";
const char* Assets::Cross = "images/GameScreen/Cross.png";
const char* Assets::Shadow = "images/GameScreen/shadow.png";
const char* Assets::ShadowOverWall = "images/GameScreen/shadowOverWall.png";
const char* Assets::LanternShadow = "images/GameScreen/lanternShadow.png";

// Enemies
const char* Assets::Rat = "images/Enemies/Rat/Rat.png";

// Game menu
const char* Assets::EUMap = "images/GameMenu/europe.jpg";
const char* Assets::RedBall = "images/GameMenu/red_ball.png";

// Walls parameters

float Assets::FrontWallsParams[4][4] = 
{
	{ 0, 0, 100, 100},    // Para profundidad 1
	{ 20, 21.7, 63, 51.3},    // Para profundidad 2
	{ 30.8, 33, 43, 26.9},    // Para profundidad 3
	{ 36, 38.5, 34, 14.4}     // Para profundidad 4
};

float Assets::LeftWallParams[4][4] =
{
	{ 0,0,0,0},
	{ 5, 21.4, 19.7, 52 },
	{ 3, 33, 30.9, 26.8 },
	{ 3, 38.5, 35.3, 14.4 }
};

float Assets::Left3DWallParams[4][4] =
{
	{ 27.7, 0, -20, 98 },
	{ 36.5, 21.4, -10, 52 },
	{ 41.1, 32.9, -5, 27 },
	{ 43.2, 38.5, -2.5, 14.7 }
};

float Assets::RightWallParams[4][4] =
{
	{ 0,0,0,0 },
	{ 84.8, 21.7, 20, 51 },
	{ 74.3, 33, 31.2, 26.5 },
	{ 69.2, 38.5, 36, 14.4 }
};

float Assets::Right3DWallParams[4][4] =
{
	{ 84.8, 0, 20, 98 },
	{ 75.5, 21.7, 10, 51 },
	{ 71, 33, 5, 26.5 },
	{ 68.8, 38.5, 2.5, 14.7 }
};

float Assets::ShadowsParams[4][3] =
{
	// posY, alto y transparencia
	{ 10, 80, 90 },
	{ 20, 60, 150},
	{ 32.5, 30, 150},
	{ 38.5, 15, 255}
};