#include "traveler.h"


Traveler::Traveler() {}

BOOL Traveler::travel_and_copy(std::wstring from, std::wstring to)
{
	if (from[from.length() - 1] != L'*' && from[from.length() - 2] != L'\\') {
		from.append(L"\\*");
	}
	// Kopyalanacak olan klasör yoksa oluþturuldu
	if (CreateDirectoryW(to.c_str(), NULL) == 0) {
		//wcout << "I couldnt create boss " << endl;
	}

	WIN32_FIND_DATAW file_info;
	HANDLE findHandle = FindFirstFileW(from.c_str(), &file_info);
	if (findHandle == INVALID_HANDLE_VALUE) {
		std::wcout << "Wrong handle value" << std::endl;
		return FALSE;
	}

	while (FindNextFileW(findHandle, &file_info)) {
		std::wstring filename = file_info.cFileName;
		DWORD fileSize = 0;
		GetFileSize(findHandle, &fileSize);
		std::cout << "Filesize => " << fileSize << std::endl;
		if (filename == L".." || filename == L".") {
			continue;
		}
		// Handle okunurken bulunan kýsmýn dizin olup olmadýðýna bakýlýyor
		if (file_info.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			std::wstring to_folder_name = ((to + L"\\") + file_info.cFileName);
			if (CreateDirectoryW(to_folder_name.c_str(), NULL) != 0) {
				travel_and_copy(from.substr(0, from.find_last_of(L"*")).append(filename + L"\\*"), to_folder_name);
			}
		}
		else {
			if (this->extensions.empty() != true) {
				for (unsigned i = 0; i < this->extensions.size(); i++) {
					if (this->getFileExtension(filename) == this->extensions.at(i)) {
						this->copy(from, to, filename);
					}
				}
			}
			else {
				this->copy(from, to, filename);
			}
		}
	}
	return TRUE;
}

BOOL Traveler::copy(std::wstring from, std::wstring to, std::wstring filename) {
	std::wstring from_file_name = (from.substr(0, from.find(L"*"))) + filename;
	std::wstring to_file_name = ((to + L"\\") + filename);
	
	if (!CopyFileW(from_file_name.c_str(), to_file_name.c_str(), true)) {
		std::cout << "Error when copying file .. " << std::endl;
		std::wcout << from_file_name << L" -- "<<to_file_name<<L"\n";
		return FALSE;
	}
	return TRUE;
}

void Traveler::addExtension(std::wstring ext) {
	bool isAdded = false;
	for (unsigned i = 0; i < this->extensions.size(); i++) {
		if (this->extensions.at(i) == ext) {
			isAdded = true;
		}
	}
	if (isAdded == false) {
		this->extensions.push_back(ext);
	}
}

void Traveler::delExtension(std::wstring ext) {
	for (unsigned i = 0; i < this->extensions.size(); i++) {
		if (this->extensions.at(i) == ext)
			this->extensions.erase(this->extensions.begin() + i);
	}
}

std::string Traveler::getFileExtension(std::string filename) {
	int firstDot = filename.rfind(".") + 1;
	return filename.substr(firstDot, (filename.size() - firstDot));
}

std::wstring Traveler::getFileExtension(std::wstring filename) {
	int firstDot = filename.rfind(L".") + 1;
	return filename.substr(firstDot, (filename.size() - firstDot));
}
