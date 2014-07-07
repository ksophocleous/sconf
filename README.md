sconf
==
a simple config property serialization library. The project is build using `cmake`, use it as a static library.

The config file created by the library is be default in the current working directory and is declared like this 

```C++
sconf::cfg<mylog> cfg("test.cfg");
```

where `myconfig` is a struct filled with the properties that you want to be serializable in the config file. All properties **must** have default values which are loaded in case the json document does not contain this property or it is of the wrong type.

```C++
struct mylog : sconf::group
{
	mylog() : group("log"),
		filename(this, "filename", "${log_dir}/default_log.log")
	{}

	sconf::property<std::string> filename;
};
```

the parameters of the constructor of `sconf::property` are (this, name of property, default value). The first parameter is the owning group.

dependencies
---
* slog (http://github.com/ksophocleous/slog)
* jsonccp (http://github.com/ksophocleous/jsoncpp)

These are `cmake` compatible and are locally included in the project.

via `git` just do a `git submodule update --init` to grab the dependencies and put them in a folder called vendor on this.
