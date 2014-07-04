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
			cfg(std::string filename) : m_filepath(std::move(filename))
			{
				cfg_helper::load(*this, m_filepath);
			}

			~cfg()
			{
				try
				{
					save();
				}
				catch (std::exception& e)
				{
					slog::error() << "Exception while saving config file '" << m_filepath << "': " << e;
				}
			}

			void save()
			{
				cfg_helper::save(*this, m_filepath);
			}

		private:
			std::string m_filepath;
	};
}