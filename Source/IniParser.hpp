std::unordered_map<std::string, std::string> LoadConfig(const std::string& filename);
bool GetBoolFromConfig(const std::unordered_map<std::string, std::string>& config, const std::string& key);
int GetIntFromConfig(const std::unordered_map<std::string, std::string>& config, const std::string& key, int defaultValue = 0);
void SaveConfig(const std::string& filename, const std::unordered_map<std::string, std::string>& config);