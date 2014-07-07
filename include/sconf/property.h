#pragma once

#include <json/json.h>
#include "property_base.h"
#include "cfg_helper.h"

namespace sconf
{
	class group;

	template<typename T>
	class property : public property_base
	{
		public:
			property(group* parent, std::string name, T defaultValue) : property_base(parent, std::move(name)), _default(defaultValue), _current(defaultValue)
			{
			}

			virtual void deserialize(const Json::Value& in, bool restore_missing_defaults) override
			{
				_current = value_from_json(in, _default);
			}

			virtual void serialize(Json::Value& in) const override
			{
				in = _current;
			}

			virtual void restore_default() override
			{
				_current = _default;
			}

			const T value() const { return _current; }
			operator T() const { return _current; }

			property<T>& operator= (T newval)
			{
				_current = std::move(newval);
				cfg_helper::mark_dirty();
				return *this;
			}

			friend std::ostream& operator<< (std::ostream& out, const property<T>& prop)
			{
				out << prop.value();
				return out;
			}

		protected:
			virtual void register_property(property_base& prop) override
			{

			}

		private:
			T _current;
			T _default;
	};
}
