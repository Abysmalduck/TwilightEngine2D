#pragma once

#include <string>
#include <filesystem>
#include <LuaCpp.hpp>
#include <set>

#include "log.h"

#define LUA_UPDATE_FILE_NAME "update.lua"
#define LUA_START_FILE_NAME "start.lua"

class LuaEngine
{
private:
    std::filesystem::path _lua_path;
    std::filesystem::path _update_root_file_path;
    std::filesystem::path _start_root_file_path;

    std::string _lua_path_str;

    LuaCpp::LuaContext this_context;

    std::set<std::string> added_scripts = std::set<std::string>();
public:

    int init(const std::string& lua_path)
    {
        logs("Lua game path: " + lua_path);
        
        _lua_path = std::filesystem::path(lua_path);

        std::filesystem::path update_file_name(LUA_UPDATE_FILE_NAME);
        std::filesystem::path start_file_name(LUA_START_FILE_NAME);

        _update_root_file_path = lua_path / update_file_name;
        _start_root_file_path = lua_path / start_file_name;

        if (!std::filesystem::exists(_update_root_file_path))
        {
            logsi("Root update.lua file not found! Unable to initialize Lua engine.", ERR);
            return -1;
        }
        logs("Root update.lua file found.");
        
        if (!std::filesystem::exists(_start_root_file_path))
        {
            logsi("Root start.lua file not found! Unable to initialize Lua engine.", ERR);
            return -1;
        }
        logs("Root start.lua file found.");

        this_context.CompileFile("root_start", _start_root_file_path.string());
        this_context.CompileFile("root_update", _update_root_file_path.string());

        _lua_path_str = _lua_path.string();

        return 0;
    }

    LuaCpp::LuaContext* getContextPtr()
    {
        return &this_context;
    }

    void addScriptToContext(const std::string& script_name, const std::string& script_path)
    {
        if (added_scripts.find(script_name) == added_scripts.end())
        {
            this_context.CompileFile(script_name, script_path);
            logs("Added " + script_name + " script to context.");
            added_scripts.insert(script_name);
            return;
        }

        logs("Script " + script_name + " already added to context.");
        return;
    }

    void addLibrary(std::shared_ptr<LuaCpp::Registry::LuaLibrary>& lib)
    {
        this_context.AddLibrary(lib);
    }

    int callRootStart()
    { 
        return luaCallScript("root_start");
    }

    int callRootUpdate()
    {
        return luaCallScript("root_update");
    }

    int luaCallScript(std::string script_name)
    {
        try 
        {
		    this_context.Run(script_name);
	    }
	    catch (std::runtime_error& e)
  	    {
		    std::cout << e.what() << '\n';

            logsi("Runtime script error in file " + script_name + " : "+ std::string(e.what()), ERR);
            return -1;
  	    }
        return 0;
    }

    const std::string& getLuaPath()
    {
        return _lua_path_str;
    }
};