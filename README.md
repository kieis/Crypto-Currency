
# Crypto Currency

A windows desktop program that makes use of the poocoin API to obtain the price of crypto tokens using tokens as inputs search parameter.


## Setup

Cloning with git:

```bash
$ git clone https://github.com/kieis/crypto-currency
```
Project made with Visual Studio 2019

Open: \crypto-currency\project\crypto currency.sln

### Some observations
#### Inside 'main.cpp'

```bash
-> Line 75: //Delay between requests to poocoin API, 10000 means 10 seconds.
Sleep(10000);

-> Line 84: //It's possible to get some other stuffs from the API, example usage:
std::string coinSymbol = jsonDecoded.at(0)["symbol"].c_str();

//API return example for Space Genesis token:
{
    "updated_at":1650800765603,
    "data":{
        "name":"Space Genesis",
        "symbol":"SPG",
        "price":"0.05599314266803903377882047688964",
        "price_BNB":"0.0001393497540931514095283398428704"
    }
}

```
## Usage

Folder with compiled program: \crypto-currency\build

#### File 'alarm.ini'

```bash
If empty, no alarm will occur.

Structure:

[0x0ecaf010fc192e2d5cbeb4dfb1fee20fbd733aa1] //token address
bombcrypto                                   //just an identifying comment, this will not be read in the program
alarmTimer=1500                              //time the alarm will be active
alarmFrequency=350                           //sound frequency of alarm
alarmValue=3.80                              //price that will be checked
alarmType=higher                             //higher = if price is higher than, lower = if price is lower than
```

#### File 'tokens.txt'

```bash
Enter the tokens you want to check.

Example:

0x00e1656e45f18ec6747f5a8496fd39b50b38396d
0xe9e7cea3dedca5984780bafc599bd69add087d56
0x0ecaf010fc192e2d5cbeb4dfb1fee20fbd733aa1
```

#### Run 'crypto currency.exe'


## Demonstration

![App Screenshot](https://i.imgur.com/uFg4un3.png)


## Improvements

- The api that was used does not return the data ​​in real time, there is a difference between the value shown in the graph and what the api returns.
- Using beep as an alarm is not very interesting, it is possible to use other libraries to play some specific sound file.
- In the project the only way to change the time between requests to the API is through source, it would be more interesting using configuration files.
## Reference

 - [Color Console](https://github.com/imfl/color-console)
