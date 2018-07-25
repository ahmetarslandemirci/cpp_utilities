#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
class Traveler {
private:
	std::vector<std::wstring> extensions;
	BOOL copy(std::wstring from, std::wstring to, std::wstring filename);
public:
	Traveler();
	BOOL travel_and_copy(std::wstring from, std::wstring to);
	void addExtension(std::wstring);
	void delExtension(std::wstring);
	std::string getFileExtension(std::string);
	std::wstring getFileExtension(std::wstring);
};