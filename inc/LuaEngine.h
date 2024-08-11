#pragma once

#include <string>
#include <log.h>
#include <filesystem>

#include <LuaCpp.hpp>

#define LUA_UPDATE_FILE_NAME "update.lua"
#define LUA_START_FILE_NAME "start.lua"

class LuaEngine
{
private:
    std::filesystem::path _lua_path;
    std::filesystem::path _update_root_file_path;
    std::filesystem::path _start_root_file_path;


    LuaCpp::LuaContext this_context;
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

        return 0;
    }

    void addLibrary(std::shared_ptr<LuaCpp::Registry::LuaLibrary>& lib)
    {
        this_context.AddLibrary(lib);
    }

    int callRootStart()
    { 
        try 
        {
		    this_context.Run("root_start");
	    }
	    catch (std::runtime_error& e)
  	    {
		    std::cout << e.what() << '\n';

            logsi("Runtime script error! " + std::string(e.what()), ERR);
            return -1;
  	    }
        return 0;
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
};