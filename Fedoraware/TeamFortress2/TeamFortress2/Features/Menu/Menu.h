#pragma once
#include "ImGui/imgui_impl_dx9.h"
#include "../../SDK/SDK.h"

class CMenu {
	void DrawMenu();
	void DrawTabbar();
	void MenuAimbot();
	void MenuTrigger();
	void MenuVisuals();
	void MenuHvH();
	void MenuMisc();
	void MenuConfigs();
	void DrawCameraWindow();

	enum class MenuTab {
		Aimbot,
		Trigger,
		Visuals,
		HvH,
		Misc,
		Configs
	};

	enum class VisualsTab {
		Players,
		Buildings,
		World,
		Font,
		Misc,
		Radar
	};

	MenuTab CurrentTab = MenuTab::Aimbot;
	VisualsTab CurrentVisualsTab = VisualsTab::Players;

public:
	void Render(IDirect3DDevice9* pDevice);
	void Init(IDirect3DDevice9* pDevice);

	bool IsOpen = false;
	bool ConfigLoaded = false;
	bool Unload = false;

	float TitleHeight = 22.f;
	float TabHeight = 30.f;

	// Colors
	ImColor Accent = { 255, 101, 101 };
	ImColor AccentDark = { 217, 87, 87 };
	ImColor Background = { 23, 23, 23, 250 };	// Title bar
	ImColor BackgroundLight = { 51, 51, 56 };	// Tab bar
	ImColor BackgroundDark = { 31, 31, 31 };	// Background
	ImColor TextDark = { 13, 13, 13 };
	ImColor TextLight = { 240, 240, 240 };
};

inline CMenu g_Menu;