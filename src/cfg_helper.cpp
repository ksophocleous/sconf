#include "sconf/cfg_helper.h"
#include "sconf/group.h"

#include <slog/slog.h>
#include <json/json.h>

#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace sconf;

//static 
bool cfg_helper::_cfg_dirty = false;

//static 
void cfg_helper::load(group& group, const std::string& filename, bool restore_missing_defaults)
{
	std::ifstream configfile(filename, std::ios_base::in);
	if (configfile)
	{
		cfg_helper::deserialize_all(group, strobj() << "config file '" << filename << "'", configfile, restore_missing_defaults);
		_cfg_dirty = false;
	}
	else
		_cfg_dirty = true;
}

//static 
void cfg_helper::save(group& group, const std::string& filename)
{
	// early exit if we haven't made any changes to the config file
	if (!_cfg_dirty)
		return;

	std::string newname = strobj() << filename << ".new";

	{
		std::ofstream configfile(newname, std::ios_base::out);
		if (configfile)
			cfg_helper::serialize_all(group, configfile);
	}

#ifndef _WIN32
	auto result = rename(newname.c_str(), filename.c_str());
	if (result != 0)
		slog::error() << "failed to save config file '" << filename << "'";
#else
	BOOL result = MoveFileExA(newname.c_str(), filename.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
	if (result == FALSE)
		slog::error() << "failed to save config file '" << filename << "'";
#endif
}

//static 
void cfg_helper::deserialize_all(group& group, const std::string& streamname, std::istream& stream, bool restore_missing_defaults)
{
	Json::Value root;
	Json::Reader reader;
	if (reader.parse(stream, root) == false)
		throw std::runtime_error(strobj() << streamname << " contains an invalid json document. Error is " << reader.getFormattedErrorMessages());

	if (root.isObject() == false)
		throw std::runtime_error(strobj() << streamname << " Expected root to be an object");

	Json::Value& grouproot = root[group.name()];
	group.deserialize(grouproot, restore_missing_defaults);
}

//static 
void cfg_helper::serialize_all(group& group, std::ostream& stream)
{
	Json::Value root;

	Json::Value& grouproot = root[group.name()];
	group.serialize(grouproot);

	Json::StyledWriter writer;
	stream << writer.write(root);
}
