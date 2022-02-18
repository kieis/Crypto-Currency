#include "color.h"
#include "stdafx.h"

#pragma warning(disable: 4996)

#define HIGHER "higher"
#define LOWER "lower"

struct TokenAlarm {
	std::string token;
	std::string type;
	int alarmTimer;
	int alarmFrequency;
	float alarmValue;

	TokenAlarm() {
		alarmTimer = alarmFrequency = 0;
		alarmValue = 0.0f;
	}
};

int main() {
	std::vector<std::string> tokenList = utils.readFile(utils.getCurrentPath() + std::string("\\") + "tokens.txt");
	if (!tokenList.empty()) {
		//get alarm params
		std::vector<TokenAlarm> alarmList;
		for (int i = 0; i < tokenList.size(); i++) {
			std::string alarmTimer, alarmFrequency, alarmValue, alarmType;

			utils.loadProfile(tokenList.at(i).c_str(), "alarmTimer", alarmTimer);
			utils.loadProfile(tokenList.at(i).c_str(), "alarmFrequency", alarmFrequency);
			utils.loadProfile(tokenList.at(i).c_str(), "alarmValue", alarmValue);
			utils.loadProfile(tokenList.at(i).c_str(), "alarmType", alarmType);

			if (!alarmTimer.empty()) {
				TokenAlarm tmp;
				int tmpTimer = std::stoi(alarmTimer);

				if (tmpTimer < 1000) {
					tmp.alarmTimer = 1000;
				}else {
					tmp.alarmTimer = tmpTimer;
				}

				if (!alarmFrequency.empty()) {
					int tmpFrequency = std::stoi(alarmFrequency);
					if (tmpFrequency > 0) {
						tmp.alarmFrequency = tmpFrequency;
					}else {
						tmp.alarmFrequency = 500;
					}
				}else {
					tmp.alarmFrequency = 500;
				}

				if (!alarmValue.empty()) {
					tmp.alarmValue = std::stof(alarmValue);
				}

				tmp.token = tokenList.at(i);
				if (!alarmType.empty()) {
					tmp.type = alarmType;
				}else {
					tmp.type = HIGHER;
				}
				
				alarmList.push_back(tmp);
			}
		}

		std::string poopCoinAPI = "https://api.pancakeswap.info/api/v2/tokens/";

		while (1) {
			//every 10 seconds
			Sleep(10000);
			system("cls");

			std::cout << dye::light_green("[") << dye::white("Crypto Currency") << ", " << dye::light_purple("10 Seconds to update") << dye::light_green("]") << std::endl << std::endl;

			for (int i = 0; i < tokenList.size(); i++) {
				std::string request = utils.getRequestUrl(poopCoinAPI + tokenList.at(i));

				CJsonManager jsonReader(request);
				std::vector<std::map<std::string, std::string>> jsonDecoded = jsonReader.getDecoded();

				std::string coinName = jsonDecoded.at(0)["name"].c_str();
				float cointValue = std::stof(jsonDecoded.at(0)["price"]);

				std::cout << dye::light_green(">> ") << dye::yellow(coinName.c_str()) << ": " << dye::light_green(cointValue) << "$" << std::endl;

				for (int j = 0; j < alarmList.size(); j++) {
					if (strstr(tokenList.at(i).c_str(), alarmList.at(j).token.c_str())) {
						if (strstr(alarmList.at(j).type.c_str(), HIGHER)) {
							if (cointValue >= alarmList.at(j).alarmValue) {
								std::cout << dye::light_purple("WARNING") << " ~ " << dye::yellow(coinName) << " is higher than " << dye::green(alarmList.at(j).alarmValue) << "$" << std::endl;
								Beep(alarmList.at(j).alarmFrequency, alarmList.at(j).alarmTimer);
							}
						}else {
							if (cointValue <= alarmList.at(j).alarmValue) {
								std::cout << dye::light_purple("WARNING") << " ~ " << dye::yellow(coinName) << " is lower than " << dye::green(alarmList.at(j).alarmValue) << "$" << std::endl;
								Beep(alarmList.at(j).alarmFrequency, alarmList.at(j).alarmTimer);
							}
						}
					}
				}
			}
		}
	}

	std::printf(">> tokens.txt is empty, create a file with same name at same directory.\n");
	system("pause");

	return 0;
}