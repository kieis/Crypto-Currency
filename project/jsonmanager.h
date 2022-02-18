#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

class CJsonManager {
private:
	std::string m_data;
public:
	std::vector<std::map<std::string, std::string>> getDecoded();
	CJsonManager(std::string data);
};

#endif