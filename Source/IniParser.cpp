#include "PreCompileHeaders.h"
#include "Iniparser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, std::string> LoadConfig(const std::string& filename) 
{
    std::unordered_map<std::string, std::string> config;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) 
    {
        if (line.empty() || line[0] == '[' || line[0] == '#') continue; // Skip sections and comments

        std::istringstream is_line(line);
        std::string key, value;

        if (std::getline(is_line, key, '=') && std::getline(is_line, value)) 
        {
            config[key] = value;
        }
    }

    return config;
}

bool GetBoolFromConfig(const std::unordered_map<std::string, std::string>& config, const std::string& key)
{
    auto it = config.find(key);
    if (it != config.end())
    {
        return it->second == "true"; // Returns true if value is "true", otherwise false
    }
    return false; // Default to false if the key isn't found
}

int GetIntFromConfig(const std::unordered_map<std::string, std::string>& config, const std::string& key, int defaultValue)
{
    auto it = config.find(key);
    if (it != config.end())
    {
        try
        {
            return std::stoi(it->second); // Convert string to int
        }
        catch (const std::exception& e) // Catch conversion errors
        {
            LOG("Error converting \"%s\" to int: %s", key, e.what());
        }
    }
    return defaultValue; // Return default value if key is not found or conversion fails
}

void SaveConfig(const std::string& filename, const std::unordered_map<std::string, std::string>& config) 
{
    std::ofstream file(filename);
    file << "[Graphics]\n";
    for (const auto& pair : config)
    {
        file << pair.first << "=" << pair.second << "\n";  // Use pair.first and pair.second
    }
}