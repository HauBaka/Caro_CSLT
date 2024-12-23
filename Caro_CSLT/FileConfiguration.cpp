#include "FileConfiguration.h"
#include "Caro_CSLT.h"
vector<FileConfiguration> loaded = {};
/*Tách từ 1 chuỗi sang key & value*/
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
/*Nạp file*/
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
/*Lấy các key & value*/
FileConfiguration getFileConfiguration(FILE* file) {
	for (int i = 0; i < loaded.size(); i++) {
		if (loaded[i].file == file) {
			return loaded[i];
		}
	}
	return {};
}
/*Lấy value dưới dạng wstring*/
wstring getwstring(FILE* file, wstring path) {
	FileConfiguration yaml = getFileConfiguration(file);
	if (yaml.file != NULL) {
		for (int i = 0; i < yaml.keys.size(); i++) {
			if (path == yaml.keys[i]) return yaml.values[i];
		}
	}
	return path + L" is not found!";
}
/*Lấy value dưới dạng int*/
int getInt(FILE* file, wstring path) {
	return stoi(getwstring(file, path));
}
/*Lấy value dưới dạng bool*/
bool getBool(FILE* file, wstring path) {
	return (getwstring(file, path) == L"true") ? 1 : 0;
}
/*Đóng tất cả các file đã mở*/
void closeAllFiles() {
	FILE* f;
	fclose(language);
	fclose(config);
	for (int i = 0; i < loaded.size(); i++) {
		f = loaded[i].file;
		if (f != NULL)  fclose(f);
	}
}