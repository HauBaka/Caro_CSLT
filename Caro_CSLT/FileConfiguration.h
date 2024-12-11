#ifndef _FILECONFIGURATION_H_
#define _FILECONFIGURATION_H_

#include "ModelUtils.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct FileConfiguration {
	FILE* file;
	vector<wstring> keys;
	vector<wstring> values;
};

extern vector<FileConfiguration> loaded;

vector<wstring> toKeyValue(wstring);
bool loadConfiguration(FILE*);
FileConfiguration getYAML(FILE*);
wstring getwstring(FILE*, wstring);
int getInt(FILE*, wstring);
bool getBool(FILE*, wstring);

#endif