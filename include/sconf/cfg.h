#pragma once

#include <slog/slog.h>
#include <string>

#include "cfg_helper.h"

namespace sconf
{
	template<typename T>
	class cfg : public T
	{
		public:
			cfg(std::string filename) : _filepath(std::move(filename))
			{
				cfg_helper::load(*this, _filepath);
			}

			~cfg()
			{
				try
				{
					save();
				}
				catch (std::exception& e)
				{
					slog::error() << "Exception while saving config file '" << _filepath << "': " << e;
				}
			}

			void save()
			{
				cfg_helper::save(*this, _filepath);
			}

		private:
			std::string _filepath;
	};
}