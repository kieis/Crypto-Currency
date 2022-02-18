#include "stdafx.h"
#ifdef UTILS_H
Utils utils;

std::string Utils::getRequestUrl(std::string url) {
	char* buffer = new char[5000];

	HINTERNET hSession = InternetOpenA("downloader", INTERNET_OPEN_TYPE_PROXY, "http=http://127.0.0.1:6666", NULL, 0);
	if (hSession) {
		HINTERNET hOpenUrl = InternetOpenUrlA(hSession, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
		DWORD dwRead;

		while (InternetReadFile(hOpenUrl, buffer, 5000 - 1, &dwRead)) {
			if (dwRead == '\0') {
				break;
			}

			memset(&buffer[dwRead], 0, 1);
		}

		InternetCloseHandle(hOpenUrl);
		InternetCloseHandle(hSession);
	}

	return buffer;
}

std::vector<std::string> Utils::readFile(const std::string filePath) {
	std::vector<std::string> tmp;
	std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			tmp.push_back(line);
		}
		file.close();
	}

	return tmp;
}

std::string Utils::getCurrentPath() {
	CHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

void Utils::saveProfile(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR castparam) {
	CHAR lpString[1024];
	sprintf(lpString, "%s", castparam);
	WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, std::string(getCurrentPath() + std::string("\\") + "alarm.ini").c_str());
}

void Utils::loadProfile(LPCSTR lpAppName, LPCSTR lpKeyName, std::string& outparam) {
	char m_returned[256];
	if (GetPrivateProfileStringA(lpAppName, lpKeyName, "", m_returned, 256, std::string(getCurrentPath() + std::string("\\") + "alarm.ini").c_str())) { outparam = m_returned; }
	else { outparam = "0"; }
}

void Utils::strReplace(std::string& str, const std::string& oldStr, const std::string& newStr) {
	std::string::size_type pos = 0u;
	while ((pos = str.find(oldStr, pos)) != std::string::npos) {
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
}

#endif