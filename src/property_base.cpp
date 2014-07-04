#include "sconf/property_base.h"
#include <json/json.h>

using namespace sconf;

//template<> 
//uint32_t value_from_json(const Json::Value& in, uint32_t default)
//{
//	return default;
//}

property_base::property_base(property_base* parent, std::string name) : _name(std::move(name)), _parent(parent)
{
	if (_parent)
		_parent->register_property(*this);
}

namespace sconf
{
	//template uint32_t value_from_json<uint32_t>(const Json::Value& in, uint32_t default);

	template<>
	int32_t value_from_json(const Json::Value& in, int32_t defaultValue)
	{
		return in.isInt() ? in.asInt() : defaultValue;
	}

	template<> 
	uint32_t value_from_json(const Json::Value& in, uint32_t defaultValue)
	{
		return in.isUInt() ? in.asUInt() : defaultValue;
	}

	template<>
	uint64_t value_from_json(const Json::Value& in, uint64_t defaultValue)
	{
		return in.isUInt64() ? in.asUInt64() : defaultValue;
	}

	template<>
	int64_t value_from_json(const Json::Value& in, int64_t defaultValue)
	{
		return in.isInt64() ? in.asInt64() : defaultValue;
	}

	template<>
	bool value_from_json(const Json::Value& in, bool defaultValue)
	{
		return in.isBool() ? in.asBool() : defaultValue;
	}

	template<>
	float value_from_json(const Json::Value& in, float defaultValue)
	{
		return in.isDouble() ? in.asFloat() : defaultValue;
	}

	template<>
	double value_from_json(const Json::Value& in, double defaultValue)
	{
		return in.isDouble() ? in.asDouble() : defaultValue;
	}

	template<>
	std::string value_from_json(const Json::Value& in, std::string defaultValue)
	{
		return in.isString() ? in.asString() : defaultValue;
	}
};
