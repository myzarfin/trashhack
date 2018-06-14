#include "../includes.h"
#include "../UTILS/interfaces.h"
#include "../SDK/IEngine.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/CInputSystem.h"
#include "../UTILS/render.h"
#include "../SDK/ConVar.h"
#include "Components.h"

#include "menu_framework.h"

int AutoCalc(int va)
{
	if (va == 1)
		return va * 35;
	else if (va == 2)
		return va * 34;
	else
		return va * 25 + 7.5;
}

namespace MENU
{
	void InitColors()
	{
		using namespace PPGUI_PP_GUI;


		colors[WINDOW_BODY] = SETTINGS::settings.menu_col;//CColor(40, 40, 40);
		colors[WINDOW_TITLE_BAR] = GREY; //255, 75, 0
		colors[WINDOW_TEXT] = WHITE;

		colors[GROUPBOX_BODY] = CColor(50, 50, 50);
		colors[GROUPBOX_OUTLINE] = GREY;
		colors[GROUPBOX_TEXT] = WHITE;

		colors[SCROLLBAR_BODY] = CColor(90, 90, 90, 255);

		colors[SEPARATOR_TEXT] = WHITE;
		colors[SEPARATOR_LINE] = CColor(90, 90, 90, 255);

		colors[CHECKBOX_CLICKED] = SETTINGS::settings.checkbox_col;//CColor(75, 175, 75); //HOTPINK
		colors[CHECKBOX_NOT_CLICKED] = CColor(90, 90, 90, 255);
		colors[CHECKBOX_TEXT] = WHITE;

		colors[BUTTON_BODY] = CColor(90, 90, 90, 255);
		colors[BUTTON_TEXT] = WHITE;

		colors[COMBOBOX_TEXT] = WHITE;
		colors[COMBOBOX_SELECTED] = CColor(90, 90, 90, 255);
		colors[COMBOBOX_SELECTED_TEXT] = WHITE;
		colors[COMBOBOX_ITEM] = CColor(70, 70, 70, 255);
		colors[COMBOBOX_ITEM_TEXT] = WHITE;

		colors[SLIDER_BODY] = CColor(90, 90, 90, 255);
		colors[SLIDER_VALUE] = SETTINGS::settings.slider_col;//CColor(75, 175, 75); //HOTPINK
		colors[SLIDER_TEXT] = WHITE;

		colors[TAB_BODY] = SETTINGS::settings.tab_col;//CColor(90, 90, 90, 255);
		colors[TAB_TEXT] = WHITE;
		colors[TAB_BODY_SELECTED] = CColor(32, 32, 32); //HOTPINK
		colors[TAB_TEXT_SELECTED] = WHITE;

		colors[VERTICAL_TAB_BODY] = CColor(70, 70, 70, 255);
		colors[VERTICAL_TAB_TEXT] = WHITE;
		colors[VERTICAL_TAB_OUTLINE] = CColor(0, 0, 0, 100);
		colors[VERTICAL_TAB_BODY_SELECTED] = CColor(100, 100, 100, 255);

		colors[COLOR_PICKER_BODY] = CColor(70, 70, 70, 255);
		colors[COLOR_PICKER_TEXT] = WHITE;
		colors[COLOR_PICKER_OUTLINE] = CColor(0, 0, 0, 100);
	}
	void Do()
	{
		static bool menu_open = false;

		if (UTILS::INPUT::input_handler.GetKeyState(VK_INSERT) & 1)
		{
			menu_open = !menu_open;
			INTERFACES::Engine->ClientCmd(menu_open ? "cl_mouseenable 0" :
				"cl_mouseenable 1");
			INTERFACES::InputSystem->EnableInput(!menu_open);
		}

		if (UTILS::INPUT::input_handler.GetKeyState(UTILS::INPUT::input_handler.keyBindings(SETTINGS::settings.flip_int)) & 1)
			SETTINGS::settings.flip_bool = !SETTINGS::settings.flip_bool;

		if (UTILS::INPUT::input_handler.GetKeyState(UTILS::INPUT::input_handler.keyBindings(SETTINGS::settings.quickstopkey)) & 1)
			SETTINGS::settings.stop_flip = !SETTINGS::settings.stop_flip;

		if (UTILS::INPUT::input_handler.GetKeyState(UTILS::INPUT::input_handler.keyBindings(SETTINGS::settings.overridekey)) & 1)
			SETTINGS::settings.overridething = !SETTINGS::settings.overridething;

		InitColors();
		if (menu_open)
		{
			using namespace PPGUI_PP_GUI;
			if (!menu_open) return;

			DrawMouse();

			SetFont(FONTS::menu_window_font);
			WindowBegin("trashhack private", Vector2D(200, 200), Vector2D(700, 500));

			std::vector<std::string> tabs = { "aimbot", "visuals", "misc", "antiaim", "colours", "config" };
			std::vector<std::string> aim_mode = { "rage", "legit" };
			std::vector<std::string> acc_mode = { "head", "body aim", "hitscan" };
			std::vector<std::string> chams_mode = { "none", "visible", "invisible" };
			std::vector<std::string> aa_pitch = { "none", "emotion", "fake down", "fake up", "fake zero" };
			std::vector<std::string> aa_mode = { "none", "backwards", "sideways", "backjitter", "lowerbody", "legit troll", "rotational", "freestanding" };
			std::vector<std::string> aa_fake = { "none", "backjitter", "random", "local view", "opposite", "rotational" };
			std::vector<std::string> configs = { "default", "legit", "autos", "scouts", "pistols", "awps", "nospread" };
			std::vector<std::string> box_style = { "none", "full", "debug" };
			std::vector<std::string> media_style = { "perfect", "random" };
			std::vector<std::string> delay_shot = { "off", "lag compensation" };
			std::vector<std::string> fakelag_mode = { "factor", "adaptive" };
			std::vector<std::string> key_binds = { "none", "mouse1", "mouse2", "mouse3", "mouse4", "mouse5", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12" };
			std::vector<std::string> hitmarker = { "none", "gamesense", "bameware", "custom" };
			std::vector<std::string> antiaimmode = { "standing", "moving", "jumping" };
			std::vector<std::string> glow_styles = { "regular", "pulsing", "outline"};
			std::vector<std::string> local_chams = { "none","sim fakelag: normal", "non-sim fakelag", "sim fakelag: color" };
			std::vector<std::string> chams_type = { "metallic", "basic" };
			std::vector<std::string> team_select = { "enemy", "team"};
			std::vector<std::string> crosshair_select = { "none", "static", "recoil" };
			std::vector<std::string> autostop_method = { "head", "hitscan" };
			std::vector<std::string> override_method = { "set", "key-press"};
			std::string config;

			switch (Tab("main", tabs, OBJECT_FLAGS::FLAG_NONE))
			{
				/* Aimbot */		 case 0: {
					Checkbox("enable aimbot", SETTINGS::settings.aim_bool);
					if (SETTINGS::settings.aim_bool)
					{
						GroupboxBegin("main", AutoCalc(2));
							Combobox("aimbot type", aim_mode, SETTINGS::settings.aim_type);
							Combobox("aimbot mode", acc_mode, SETTINGS::settings.acc_type);
						GroupboxEnd();

						if (SETTINGS::settings.aim_type == 0)
						{
							GroupboxBegin("damage control", AutoCalc(3));
								Slider("minimum hit-chance", 0, 100, SETTINGS::settings.chance_val);
								Slider("minimum damage", 1, 100, SETTINGS::settings.damage_val);
							GroupboxEnd();

							GroupboxBegin("multipoint", AutoCalc(3));
								Checkbox("more aimpoints", SETTINGS::settings.multi_bool);
								Slider("head scale", 0, 1, SETTINGS::settings.point_val);
								Slider("body scale", 0, 1, SETTINGS::settings.body_val);
							GroupboxEnd();

							GroupboxBegin("corrections", AutoCalc(7));
								Checkbox("auto stop", SETTINGS::settings.stop_bool);
								Combobox("auto stop key", key_binds, SETTINGS::settings.quickstopkey);
								//Combobox("auto stop method", autostop_method, SETTINGS::settings.autostopmethod);
								Checkbox("angle correction", SETTINGS::settings.resolve_bool);
								Checkbox("override enable", SETTINGS::settings.overrideenable);
								Combobox("override key", key_binds, SETTINGS::settings.overridekey);
								Combobox("override method", override_method, SETTINGS::settings.overridemethod);
								Combobox("delay shot", delay_shot, SETTINGS::settings.delay_shot);
							GroupboxEnd();
						}
						else
						{
							GroupboxBegin("trigger and others", AutoCalc(3));
								Checkbox("triggerbot", SETTINGS::settings.legittrigger_bool);
								Combobox("triggerbot key", key_binds, SETTINGS::settings.legittrigger_key);
								Checkbox("position adjustment", SETTINGS::settings.back_bool);
							GroupboxEnd();
						}
					}
				} break;
				/* Visuals */		 case 1: {
					Checkbox("enable visuals", SETTINGS::settings.esp_bool);
					if (SETTINGS::settings.esp_bool)
					{
						GroupboxBegin("players", AutoCalc(9));
							Combobox("team selection", team_select, SETTINGS::settings.espteamselection);
							if (SETTINGS::settings.espteamselection == 0)
							{
								Checkbox("draw enemy box", SETTINGS::settings.box_bool);
								Checkbox("draw enemy name", SETTINGS::settings.name_bool);
								Checkbox("draw enemy weapon", SETTINGS::settings.weap_bool);
								Checkbox("draw enemy flags", SETTINGS::settings.info_bool);
								Checkbox("draw enemy health", SETTINGS::settings.health_bool);
								Checkbox("draw enemy money", SETTINGS::settings.money_bool);
								Checkbox("draw enemy ammo", SETTINGS::settings.ammo_bool);
								Checkbox("draw enemy fov arrows", SETTINGS::settings.fov_bool);
							}
							else if (SETTINGS::settings.espteamselection == 1)
							{
								Checkbox("draw team box", SETTINGS::settings.boxteam);
								Checkbox("draw team name", SETTINGS::settings.nameteam);
								Checkbox("draw team weapon", SETTINGS::settings.weaponteam);
								Checkbox("draw team flags", SETTINGS::settings.flagsteam);
								Checkbox("draw team health", SETTINGS::settings.healthteam);
								Checkbox("draw team money", SETTINGS::settings.moneyteam);
								Checkbox("draw team ammo", SETTINGS::settings.ammoteam);
								Checkbox("draw team fov arrows", SETTINGS::settings.arrowteam);
							}
						GroupboxEnd();

						GroupboxBegin("chams", AutoCalc(3));
							Combobox("model team selection", team_select, SETTINGS::settings.chamsteamselection);
							if (SETTINGS::settings.chamsteamselection == 0)
								Combobox("enemy coloured models", chams_mode, SETTINGS::settings.chams_type);
							else if (SETTINGS::settings.chamsteamselection == 1)
								Combobox("team coloured models", chams_mode, SETTINGS::settings.chamsteam);
							Combobox("model type", chams_type, SETTINGS::settings.chamstype);
						GroupboxEnd();

						GroupboxBegin("glow", AutoCalc(5));
							Combobox("glow team selection", team_select, SETTINGS::settings.glowteamselection);
							if (SETTINGS::settings.glowteamselection == 0)
								Checkbox("enemy glow enable", SETTINGS::settings.glowenable);
							else if (SETTINGS::settings.glowteamselection == 1)
								Checkbox("team glow enable", SETTINGS::settings.glowteam);
							Combobox("glow style", glow_styles, SETTINGS::settings.glowstyle);
							Checkbox("local glow", SETTINGS::settings.glowlocal);
							Combobox("local glow style", glow_styles, SETTINGS::settings.glowstylelocal);
						GroupboxEnd();

						GroupboxBegin("world", AutoCalc(11));
							//Checkbox("night mode", SETTINGS::settings.night_bool);
							Slider("night value", 0, 100, SETTINGS::settings.daytimevalue, 0);
							Checkbox("bullet tracers", SETTINGS::settings.beam_bool);
							Checkbox("thirdperson", SETTINGS::settings.tp_bool);
							Combobox("thirdperson key", key_binds, SETTINGS::settings.thirdperson_int);
							Combobox("crosshair", crosshair_select, SETTINGS::settings.xhair_type);
							Checkbox("render spread", SETTINGS::settings.spread_bool);
							Checkbox("remove smoke", SETTINGS::settings.smoke_bool);
							Checkbox("remove scope", SETTINGS::settings.scope_bool);
							Checkbox("remove zoom", SETTINGS::settings.removescoping);
							Checkbox("fix zoom sensitivity", SETTINGS::settings.fixscopesens);
							if (!SETTINGS::settings.matpostprocessenable)
								Checkbox("enable postprocessing", SETTINGS::settings.matpostprocessenable);
							else
								Checkbox("disable postprocessing", SETTINGS::settings.matpostprocessenable);
							Combobox("flashlight key", key_binds, SETTINGS::settings.flashlightkey);
						GroupboxEnd();

						GroupboxBegin("local player", AutoCalc(5));
							Combobox("local chams", local_chams, SETTINGS::settings.localchams);
							Slider("render fov", 0, 179, SETTINGS::settings.fov_val, 0);
							Slider("viewmodel fov", 0, 179, SETTINGS::settings.viewfov_val, 0);
							Combobox("hitmarker sound", hitmarker, SETTINGS::settings.hitmarker_val);
							Checkbox("lby indicator", SETTINGS::settings.lbyenable);
						GroupboxEnd();
					}
				} break;
				/* Miscellaneous */  case 2: {
					Checkbox("enable misc", SETTINGS::settings.misc_bool);
					if (SETTINGS::settings.misc_bool)
					{
						GroupboxBegin("movement", AutoCalc(4));
							Checkbox("auto bunnyhop", SETTINGS::settings.bhop_bool);
							Checkbox("auto strafer", SETTINGS::settings.strafe_bool);
							Checkbox("duck in air", SETTINGS::settings.duck_bool);
							Combobox("circle strafe", key_binds, SETTINGS::settings.circlestrafekey);
						GroupboxEnd();

						GroupboxBegin("fakelag", AutoCalc(5));
							Checkbox("enable", SETTINGS::settings.lag_bool);
							Combobox("fakelag type", fakelag_mode, SETTINGS::settings.lag_type);
							Slider("standing lag", 1, 14, SETTINGS::settings.stand_lag);
							Slider("moving lag", 1, 14, SETTINGS::settings.move_lag);
							Slider("jumping lag", 1, 14, SETTINGS::settings.jump_lag);
						GroupboxEnd();

						GroupboxBegin("extra", AutoCalc(1));
							Checkbox("clantag changer", SETTINGS::settings.misc_clantag);
						GroupboxEnd();
					}
				} break;
				/* Antiaim */		 case 3: {
					Checkbox("enable antiaim", SETTINGS::settings.aa_bool);
					if (SETTINGS::settings.aa_bool)
					{
						if (SETTINGS::settings.aa_bool)
						{
							GroupboxBegin("antiaim", AutoCalc(4));

							Combobox("antiaim mode", antiaimmode, SETTINGS::settings.aa_mode);
							switch (SETTINGS::settings.aa_mode)
							{
								case 0:
									Combobox("antiaim pitch - standing", aa_pitch, SETTINGS::settings.aa_pitch_type);
									Combobox("antiaim real - standing", aa_mode, SETTINGS::settings.aa_real_type);
									Combobox("antiaim fake - standing", aa_fake, SETTINGS::settings.aa_fake_type);
									break;
								case 1:
									Combobox("antiaim pitch - moving", aa_pitch, SETTINGS::settings.aa_pitch1_type);
									Combobox("antiaim real - moving", aa_mode, SETTINGS::settings.aa_real1_type);
									Combobox("antiaim fake - moving", aa_fake, SETTINGS::settings.aa_fake1_type);
									break;
								case 2:
									Combobox("antiaim pitch - jumping", aa_pitch, SETTINGS::settings.aa_pitch2_type);
									Combobox("antiaim real - jumping", aa_mode, SETTINGS::settings.aa_real2_type);
									Combobox("antiaim fake - jumping", aa_fake, SETTINGS::settings.aa_fake2_type);
									break;
							}

							GroupboxEnd();

							GroupboxBegin("additional options", AutoCalc(5));

								Combobox("flip key", key_binds, SETTINGS::settings.flip_int);
								//Checkbox("fake angle chams", SETTINGS::settings.aa_fakeangchams_bool);
								Checkbox("anti-aim arrows", SETTINGS::settings.rifk_arrow);
								switch (SETTINGS::settings.aa_mode)
								{
									case 0:
										Slider("real additive", -180, 180, SETTINGS::settings.aa_realadditive_val);
										Slider("fake additive", -180, 180, SETTINGS::settings.aa_fakeadditive_val);
										Slider("lowerbodyyaw delta", -119.9, 119.9, SETTINGS::settings.delta_val);
										break; //Checkbox("lby flick up", SETTINGS::settings.lbyflickup);
									case 1:
										Slider("real additive ", -180, 180, SETTINGS::settings.aa_realadditive1_val);
										Slider("fake additive", -180, 180, SETTINGS::settings.aa_fakeadditive1_val);
										Slider("lowerbodyyaw delta", -119.9, 119.9, SETTINGS::settings.delta1_val);
										break; //Checkbox("lby flick up", SETTINGS::settings.lbyflickup1);
									case 2:
										Slider("real additive", -180, 180, SETTINGS::settings.aa_realadditive2_val);
										Slider("fake additive", -180, 180, SETTINGS::settings.aa_fakeadditive2_val);
										Slider("lowerbodyyaw delta", -119.9, 119.9, SETTINGS::settings.delta2_val);
										break; //Checkbox("lby flick up", SETTINGS::settings.lbyflickup2);
								}

							GroupboxEnd();

							GroupboxBegin("rotate", AutoCalc(4));

								Slider("rotate fake °", 0, 180, SETTINGS::settings.spinanglefake);
								Slider("rotate fake %", 0, 100, SETTINGS::settings.spinspeedfake);

								switch (SETTINGS::settings.aa_mode)
								{
									case 0:
										Slider("rotate standing °", 0, 180, SETTINGS::settings.spinangle);
										Slider("rotate standing %", 0, 100, SETTINGS::settings.spinspeed);
										break;
									case 1:
										Slider("rotate moving °", 0, 180, SETTINGS::settings.spinangle1);
										Slider("rotate moving %", 0, 100, SETTINGS::settings.spinspeed1);
										break;
									case 2:
										Slider("rotate jumping °", 0, 180, SETTINGS::settings.spinangle2);
										Slider("rotate jumping %", 0, 100, SETTINGS::settings.spinspeed2);
										break;
								}

							GroupboxEnd();
						}
					}
				} break;
				/* Colours */		 case 4: {
					GroupboxBegin("esp colours", AutoCalc(6));
						Combobox("esp colour selection", team_select, SETTINGS::settings.espteamcolourselection);
						if (SETTINGS::settings.espteamcolourselection == 0)
						{
							ColorPicker("enemy box colour", SETTINGS::settings.box_col);
							ColorPicker("enemy name colour", SETTINGS::settings.name_col);
							ColorPicker("enemy weapon colour", SETTINGS::settings.weapon_col);
							ColorPicker("enemy fov arrows colour", SETTINGS::settings.fov_col);
						}
						else if (SETTINGS::settings.espteamcolourselection == 1)
						{
							ColorPicker("team box colour", SETTINGS::settings.boxteam_col);
							ColorPicker("team name colour", SETTINGS::settings.nameteam_col);
							ColorPicker("team weapon colour", SETTINGS::settings.weaponteam_col);
							ColorPicker("team fov arrows colour", SETTINGS::settings.arrowteam_col);
						}
						ColorPicker("grenade prediction colour", SETTINGS::settings.grenadepredline_col);
					GroupboxEnd();

					GroupboxBegin("chams colours", AutoCalc(5));

					ColorPicker("enemy vis. colour", SETTINGS::settings.vmodel_col);
					ColorPicker("enemy invis. colour", SETTINGS::settings.imodel_col);

					ColorPicker("team vis. colour", SETTINGS::settings.teamvis_color);
					ColorPicker("team invis. colour", SETTINGS::settings.teaminvis_color);

					ColorPicker("local colour", SETTINGS::settings.localchams_col);

					GroupboxEnd();

					GroupboxBegin("glow colours", AutoCalc(3));

					ColorPicker("glow enemy colour", SETTINGS::settings.glow_col);
					ColorPicker("glow team colour", SETTINGS::settings.teamglow_color);
					ColorPicker("glow local colour", SETTINGS::settings.glowlocal_col);

					GroupboxEnd();

					GroupboxBegin("bullet tracer colours", AutoCalc(3));

					ColorPicker("local player", SETTINGS::settings.bulletlocal_col);
					ColorPicker("enemy player", SETTINGS::settings.bulletenemy_col);
					ColorPicker("team player", SETTINGS::settings.bulletteam_col);

					GroupboxEnd();

					GroupboxBegin("menu options", AutoCalc(4));

					ColorPicker("menu colour", SETTINGS::settings.menu_col);
					ColorPicker("checkbox colour", SETTINGS::settings.checkbox_col);
					ColorPicker("slider colour", SETTINGS::settings.slider_col);
					ColorPicker("tab colour", SETTINGS::settings.tab_col);

					GroupboxEnd();

				} break;
				/* Configurations */ case 5: {
					GroupboxBegin("configuration", 90);
					switch (Combobox("config", configs, SETTINGS::settings.config_sel))
					{
					case 0: config = "default"; break;
					case 1: config = "legit"; break;
					case 2: config = "auto_hvh"; break;
					case 3: config = "scout_hvh"; break;
					case 4: config = "pistol_hvh"; break;
					case 5: config = "awp_hvh"; break;
					case 6: config = "nospread_hvh"; break;
					}

					if (Button("Load Config"))
					{
						INTERFACES::cvar->ConsoleColorPrintf(CColor(200, 255, 0, 255), "[Config] ");
						GLOBAL::Msg("Configuration loaded.     \n");

						SETTINGS::settings.Load(config);
					}

					if (Button("Save Config"))
					{
						INTERFACES::cvar->ConsoleColorPrintf(CColor(200, 255, 0, 255), "[Config] ");
						GLOBAL::Msg("Configuration saved.     \n");

						SETTINGS::settings.Save(config);
					}
					GroupboxEnd();
				} break;
			}
			WindowEnd();
		}
	}
}