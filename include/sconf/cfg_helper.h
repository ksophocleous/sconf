#pragma once

#include <string>
#include <sstream>

namespace sconf
{
	class group;

	struct cfg_helper
	{
		static void load(group& group, const std::string& filename, bool restore_missing_defaults = true);
		static void save(group& group, const std::string& filename);

		static void mark_dirty() { _cfg_dirty = true; }

		static void deserialize_all(group& group, const std::string& streamname, std::istream& stream, bool restore_missing_defaults);
		static void serialize_all(group& group, std::ostream& stream);

		static bool _cfg_dirty;
	};
}