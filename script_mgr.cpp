#include "pch.h"
#include "script_mgr.h"
#include "gta_util.hpp"
#include "gta/joaat.h"
#include"invoker.h"
namespace hbase
{
	void script_mgr::add_script(std::unique_ptr<script> script)
	{
		std::lock_guard lock(m_mutex);
		m_scripts.push_back(std::move(script));
	}

	void script_mgr::remove_all_scripts()
	{
		std::lock_guard lock(m_mutex);
		m_scripts.clear();
	}

	void script_mgr::tick()
	{
		gta_util::execute_as_script(RAGE_JOAAT("main_persistent"), std::mem_fn(&script_mgr::tick_internal), this);
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);
		static bool ensure_native_handlers = (g_nativeInvoker.cacheHandlers(), true);

		std::lock_guard lock(m_mutex);
		for (auto const& script : m_scripts)
		{
			script->tick();
		}
	}
}