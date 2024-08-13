#include"main_gui.h"
#include"script.h"
#include"settings.h"
#include"fiber_pool.h"
#include"gta_util.hpp"
#include"features.h"
#include"mod_vehicle.h"
#include"script_global.h"
#include"data/player.h"
#include"data/vehicles.h"
#include"data/lists.h"
#include"enums.h"
#include"ui/ui_manager.h"
#include"ui/regular_submenu.h"
#include"ui/regular_option.h"
#include"ui/sub_option.h"
#include"ui/bool_option.h"
#include"ui/number_option.h"
#include"ui/choose_option.h"
#include"ui/break_option.h"
#include"ui/vehicle_option.h"
#include"ui/player_submenu.h"

namespace hbase
{
	enum Submenu : std::uint32_t
	{
		main_menu,
		menu_seetings
	};

	void main_gui::initialize()
	{
		m_initialized = true;
		std::size_t SELF = g_ui_mgr->addSub("SELF");//this is dumb im just too lazy to change
		g_ui_mgr->add_submenu<RegularSubmenu>(SELF, "HOME", main_menu, [](RegularSubmenu* sub)
		{
			sub->add_option<SubOption>("Settings", nullptr, menu_seetings);
		});

		g_ui_mgr->add_submenu<RegularSubmenu>(SELF, "settings", menu_seetings, [](RegularSubmenu* sub)
		{
		    sub->add_option<RegularOption>("Unload", nullptr, [] {
		    g_running = false;
		    });
		    sub->add_option<RegularOption>("Quit", nullptr, [] {
		    exit(0);
		    });
		});
	}

	void main_gui::tick()
	{
		if (m_initialized)
		{
			g_ui_mgr->onTick();
		}
		else
		{
			initialize();
		}
	}
}