
#ifdef _DEBUG
	#define KWAK_FIX_ALT_KEYDOWN_MENU_BLOCK
#endif // _DEBUG

//#define NEW_PROTOCOL_SYSTEM
#define PC_POINT
#define MAIN_VERSION_SEASON 3  // Altere para 2, 3, 4 ou 6
#define BUTTONS_SEASON6

#ifndef SEASON_VERSION
#if MAIN_VERSION_SEASON == 2
#define MUDINHOX
#elif MAIN_VERSION_SEASON == 3
#define SEASON3
#elif MAIN_VERSION_SEASON == 4
#define SEASON4
#elif MAIN_VERSION_SEASON == 6
#define SEASON6
#endif

#define SEASON_VERSION MAIN_VERSION_SEASON
#endif

#define PJH_NEW_SERVER_SELECT_MAP
//#define NEW_MUHELPER_ON
#define CONSOLE
#define ASG_ADD_GENS_SYSTEM
#ifdef ASG_ADD_GENS_SYSTEM
	#define ASG_ADD_INFLUENCE_GROUND_EFFECT
	#define ASG_ADD_GENS_MARK
	#define PBG_MOD_STRIFE_GENSMARKRENDER
	#define PBG_ADD_GENSRANKING
#endif	// ASG_ADD_GENS_SYSTEM

#define KJH_PBG_ADD_INGAMESHOP_SYSTEM
#ifdef KJH_PBG_ADD_INGAMESHOP_SYSTEM
	#define PBG_ADD_INGAMESHOP_UI_MAINFRAME
	#define PBG_ADD_INGAMESHOP_UI_ITEMSHOP
	#define PBG_ADD_NAMETOPMSGBOX
	#define KJH_ADD_INGAMESHOP_UI_SYSTEM
	#define KJH_ADD_PERIOD_ITEM_SYSTEM
	#define PBG_ADD_INGAMESHOPMSGBOX
	#define PBG_ADD_ITEMRESIZE
	#define KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	//^#define PBG_ADD_CHARACTERSLOT
	#define PBG_ADD_CHARACTERCARD
	//^#define LDK_ADD_INGAMESHOP_LIMIT_MOVE_WINDOW
#endif //KJH_PBG_ADD_INGAMESHOP_SYSTEM

#define PJH_ADD_PANDA_PET
#define PJH_ADD_PANDA_CHANGERING

#define ENABLE_FULLSCREEN





