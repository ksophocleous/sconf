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
	int32_t value_from_json(const Json::Value& in, int32_t default)
	{
		return in.isInt() ? in.asInt() : default;
	}

	template<> 
	uint32_t value_from_json(const Json::Value& in, uint32_t default)
	{
		return in.isUInt() ? in.asUInt() : default;
	}

	template<>
	uint64_t value_from_json(const Json::Value& in, uint64_t default)
	{
		return in.isUInt64() ? in.asUInt64() : default;
	}

	template<>
	int64_t value_from_json(const Json::Value& in, int64_t default)
	{
		return in.isInt64() ? in.asInt64() : default;
	}

	template<>
	bool value_from_json(const Json::Value& in, bool default)
	{
		return in.isBool() ? in.asBool() : default;
	}

	template<>
	float value_from_json(const Json::Value& in, float default)
	{
		return in.isDouble() ? in.asFloat() : default;
	}

	template<>
	double value_from_json(const Json::Value& in, double default)
	{
		return in.isDouble() ? in.asDouble() : default;
	}

	template<>
	std::string value_from_json(const Json::Value& in, std::string default)
	{
		return in.isString() ? in.asString() : default;
	}
};