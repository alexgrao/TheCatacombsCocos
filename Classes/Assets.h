#ifndef __ASSETS_H__
#define __ASSETS_H__


class Assets
{
public:
	//static void InitAssets();
	// Menu
	static const char* Assets::MenuBackground;
	static const char* Assets::MenuTitle;
	static const char* Assets::PlayButton;
	static const char* Assets::PlayButtonClicked;
	//GameScene
	static const char* Assets::Wall;
	static const char* Assets::Wall3D;
	static const char* Assets::Floor;
	static const char* Assets::Ceiling;
	static const char* Assets::Upstairs;
	static const char* Assets::Downstairs;
	static const char* Assets::Cross;
	static const char* Assets::Shadow;
	static const char* Assets::ShadowOverWall;
	static const char* Assets::LanternShadow;
	//Enemies
	static const char* Assets::Rat;
	//Game menu
	static const char* Assets::EUMap;
	static const char* Assets::RedBall;

	// Positions and Sizes for walls
	static float Assets::FrontWallsParams[4][4];
	static float Assets::LeftWallParams[4][4];
	static float Assets::Left3DWallParams[4][4];
	static float Assets::RightWallParams[4][4];
	static float Assets::Right3DWallParams[4][4];
	static float Assets::ShadowsParams[4][3];
};

#endif