#include "sconf/group.h"

#include <json/json.h>

using namespace sconf;

group::group(std::string name) : property_base(nullptr, std::move(name))
{
}

group::group(group* parent, std::string name) : property_base(parent, std::move(name))
{
}

group::~group()
{
}

//virtual 
void group::serialize(Json::Value& root) const
{
	for (auto& each : _properties)
	{
		std::string propname = each->name();
		auto& proproot = root[propname];
		each->serialize(proproot);
	}
}

//virtual 
void group::register_property(property_base& prop)
{
	_properties.push_back(&prop);
}

//virtual 
void group::deserialize(const Json::Value& group, bool restore_missing_defaults)
{
	for (auto& each : _properties)
	{
		std::string name = each->name();
		auto proproot = group[name];
		if (proproot.isObject() == false)
			each->deserialize(proproot, restore_missing_defaults);
		else if (restore_missing_defaults)
			each->restore_default();
	}
}

//virtual 
void group::restore_default()
{
	for (auto& each : _properties)
		each->restore_default();
}
