#pragma once

namespace Json { class Value; }

#include <string>
#include <cstdint>

namespace sconf
{
	template<typename T>
	extern T value_from_json(const Json::Value& in, T default);

	template<>
	extern uint32_t value_from_json(const Json::Value& in, uint32_t default);

	class property_base
	{
		public:
			property_base(property_base* parent, std::string name);

			std::string name() const { return _name; }
			property_base* parent() { return _parent; }

			virtual void deserialize(const Json::Value& in, bool restore_missing_defaults) = 0;
			virtual void serialize(Json::Value& out) const = 0;
			virtual void restore_default() = 0;
			virtual void register_property(property_base& prop) = 0;

		protected:
			std::string _name;
			property_base* _parent;
	};
};
