#pragma once

#include "property_base.h"
#include <vector>

namespace sconf
{
	class group : public property_base
	{
		public:
			friend struct cfg_helper;

			group(std::string name);
			group(group* parent, std::string name);
			~group();

			virtual void serialize(Json::Value& root) const override;

			group* parent() const { return reinterpret_cast<group*>(_parent); }

		protected:
			virtual void register_property(property_base& prop) override;

			virtual void deserialize(const Json::Value& group, bool restore_missing_defaults) override;

			virtual void restore_default() override;

		private:
			std::vector<property_base*> _properties;
	};
}