#include "stdafx.h"
#ifdef JSON_MANAGER_H

std::vector<std::map<std::string, std::string>> CJsonManager::getDecoded() {
	utils.strReplace(m_data, "\\", "");
	std::vector<std::map<std::string, std::string>> tmp;
	std::map<std::string, std::string> tmpMap;
	size_t find;

	std::vector<size_t> parentStart;
	find = m_data.find('{');
	while (find != std::string::npos) {
		parentStart.push_back(find);
		find = m_data.find('{', find + 1);
	}

	std::vector<size_t> parentEnd;
	find = m_data.find('}');
	while (find != std::string::npos) {
		parentEnd.push_back(find);
		find = m_data.find('}', find + 1);
	}

	for (int i = 0; i < parentStart.size(); i++) {
		tmpMap.clear();
		size_t startLimit = parentStart[i];
		size_t endLimit = parentEnd[i];

		std::vector<size_t> aspasStart;
		std::vector<size_t> aspasEnd;
		find = m_data.find('"', startLimit + 1);
		while (find != std::string::npos && find <= endLimit) {
			aspasStart.push_back(find);
			find = m_data.find('"', find + 1);
			if (find != std::string::npos && find <= endLimit) {
				aspasEnd.push_back(find);
				find = m_data.find('"', find + 1);
			}
		}

		for (int j = 0; j < aspasStart.size(); j += 2) {
			std::string functionStr;
			for (int p = 0; p < strlen(m_data.c_str()); p++) {
				if (p > aspasStart[j] && p < aspasEnd[j]) {
					functionStr += m_data[p];
				}
			}
			std::string valueStr;
			if ((j + 1) < aspasStart.size()) {
				for (int p = 0; p < strlen(m_data.c_str()); p++) {
					if (p > aspasStart[j + 1] && p < aspasEnd[j + 1]) {
						valueStr += m_data[p];
					}
				}
			}

			tmpMap.insert(std::pair<std::string, std::string>(functionStr.c_str(), valueStr.c_str()));
		}
		tmp.push_back(tmpMap);
	}
	return tmp;
}

CJsonManager::CJsonManager(std::string data) {
	m_data = data;
}

#endif