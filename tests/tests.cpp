#include "sconf/sconf.h"
#include <slog/slog.h>

struct mygroup_people : sconf::group
{
	mygroup_people(group* parent) :
		group(parent, "people"),
		maincontact(this, "main_contact", "n/a"),
		email(this, "email", "")
	{}

	sconf::property<std::string> maincontact;
	sconf::property<std::string> email;
};

struct myconfig : sconf::group
{
	myconfig() :
		group("config"),
		threads(this, "threads", 1),
		multithreaded(this, "multithreaded", true),
		zoom_factor(this, "zoom_factor", 5.3f),
		people(this),
		filename_of_another_config(this, "myconfig", "myconfig.cfg")
	{}

	sconf::property<uint32_t> threads;
	sconf::property<bool> multithreaded;
	sconf::property<float> zoom_factor;
	mygroup_people people;
	sconf::property<std::string> filename_of_another_config;
};

int main(int argc, char* argv[])
{
	sconf::cfg<myconfig> cfg("test.cfg");

	slog::info() << "number of threads: " << cfg.threads;
	slog::info() << "is multithreaded: " << (cfg.multithreaded ? "true" : "false");
	slog::info() << "zoom factor: " << cfg.zoom_factor;

	cfg.threads = 50;
}
