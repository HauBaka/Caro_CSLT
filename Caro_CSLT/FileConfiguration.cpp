#include "FileConfiguration.h"
vector<FileConfiguration> yaml_loaded = {};

vector<wstring> toKeyValue(wstring s) {
	if (!s.empty() && s.back() == '\n') {
		s.pop_back();
	}
	vector<wstring> result = { {},{} };
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ':') {
			result[0] = s.substr(0, i);
			result[1] = s.substr(i + 2);
			RGBPrint(0,i,result[0] + L": "+ result[1], black, default_white, true);
			return result;
		}
	}
	return result;
}
bool loadConfiguration(FILE* file) {
	if (file == NULL) return 0;
	//kiểm tra file đã được load chưa
	for (int i = 0; i < yaml_loaded.size(); i++) if (yaml_loaded[i].file == file) return 1;
	//nạp file
	FileConfiguration yaml = { file, {}, {} };
	wchar_t s[256];
	while (fgetws(s, 256, file) != NULL) {
		vector<wstring> result = toKeyValue(s);
		yaml.keys.push_back(result[0]);
		yaml.values.push_back(result[1]);
	}
	yaml_loaded.push_back(yaml);
	return 1;
}
FileConfiguration getYAML(FILE* file) {
	for (int i = 0; i < yaml_loaded.size(); i++) {
		if (yaml_loaded[i].file == file) {
			return yaml_loaded[i];
		}
	}
	return {};
}
wstring getString(FILE* file, wstring path) {
	FileConfiguration yaml = getYAML(file);
	if (yaml.file != NULL) {
		for (int i = 0; i < yaml.keys.size(); i++) {
			if (path == yaml.keys[i]) return yaml.values[i];
		}
	}
	return path + L" is not found!";
}
int getInt(FILE* file, wstring path) {
	return stoi(getString(file, path));
}
bool getBool(FILE* file, wstring path) {
	return (getString(file, path) == L"true") ? 1 : 0;
}


