#ifndef UTILS_H
#define UTILS_H

class Utils {
public:
	std::string getRequestUrl(std::string url);
	std::vector<std::string> readFile(const std::string filePath);
	std::string getCurrentPath();
	void saveProfile(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR castparam);
	void loadProfile(LPCSTR lpAppName, LPCSTR lpKeyName, std::string& outparam);
	void strReplace(std::string& str, const std::string& oldStr, const std::string& newStr);
};

extern Utils utils;

#endif