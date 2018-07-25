# C++ Utility Classes and Functions
This repo presents helpful classes and functions written with C++

# Traveler
You can travel and copy specific files/folders with this class on Windows. This class uses Windows API's for travelling and copying.
```
	BOOL travel_and_copy(std::wstring from, std::wstring to);
	void addExtension(std::wstring);
	void delExtension(std::wstring);
	std::string getFileExtension(std::string);
	std::wstring getFileExtension(std::wstring);
```
With the addExtension function, you can set the file extensions to be copied.
