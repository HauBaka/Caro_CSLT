#include "FileConfiguration.h"
vector<FileConfiguration> loaded = {};

vector<wstring> toKeyValue(wstring s) {
	if (!s.empty() && s.back() == '\n') {
		s.pop_back();
	}
	vector<wstring> result = { {},{} };
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ':') {
			result[0] = s.substr(0, i);
			result[1] = s.substr(i + 2);
			return result;
		}
	}
	return result;
}
bool loadConfiguration(FILE* file) {
	if (file == NULL) return 0;
	//kiểm tra file đã được load chưa
	int index = -1;
	for (int i = 0; i < loaded.size(); i++) if (loaded[i].file == file) {
		index = i;
		break;
	}
	//nạp file
	FileConfiguration yaml = { file, {}, {} };
	wchar_t s[256];
	while (fgetws(s, 256, file) != NULL) {
		vector<wstring> result = toKeyValue(s);
		yaml.keys.push_back(result[0]);
		yaml.values.push_back(result[1]);
	}
	if (index != -1) loaded.erase(loaded.begin() + index);
	loaded.push_back(yaml);
	return 1;
}
FileConfiguration getYAML(FILE* file) {
	for (int i = 0; i < loaded.size(); i++) {
		if (loaded[i].file == file) {
			return loaded[i];
		}
	}
	return {};
}
wstring getwstring(FILE* file, wstring path) {
	FileConfiguration yaml = getYAML(file);
	if (yaml.file != NULL) {
		for (int i = 0; i < yaml.keys.size(); i++) {
			if (path == yaml.keys[i]) return yaml.values[i];
		}
	}
	return path + L" is not found!";
}
int getInt(FILE* file, wstring path) {
	return stoi(getwstring(file, path));
}
bool getBool(FILE* file, wstring path) {
	return (getwstring(file, path) == L"true") ? 1 : 0;
}


