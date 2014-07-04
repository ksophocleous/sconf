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
			property(group* parent, std::string name, T defaultValue) : property_base(parent, std::move(name)), m_default(defaultValue), m_current(defaultValue)
			{
			}

			virtual void deserialize(const Json::Value& in, bool restore_missing_defaults) override
			{
				m_current = value_from_json(in, m_default);
			}

			virtual void serialize(Json::Value& in) const override
			{
				in = m_current;
			}

			virtual void restore_default() override
			{
				m_current = m_default;
			}

			const T value() const { return m_current; }
			operator T() const { return m_current; }

			property<T>& operator= (T newval)
			{
				m_current = std::move(newval);
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
			T m_current;
			T m_default;
	};
}
