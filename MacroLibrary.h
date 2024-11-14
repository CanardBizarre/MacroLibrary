#pragma once

#ifdef MACROLIBRARY_EXPORTS
#define MACROLIBRARY__API __declspec(dllexport)
#else
#define MACROLIBRARY__API __declspec(dllimport)
#endif

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <random>
#include <thread>
#include <limits>
#include <cmath>

using namespace std;
using namespace std::chrono_literals;
using namespace chrono;
using namespace this_thread;


#define PI 3.14
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define DISPLAY(_value, _isEndl)    cout << _value;\
                                    if (_isEndl) cout << endl;
#define CLEAR  cin.clear();\
               cin.ignore((numeric_limits<streamsize>::max)(), '\n');

typedef unsigned int u_int;

class  Stream;

namespace Macro
{
	/// <summary>
	/// Config the project
	/// </summary>
	MACROLIBRARY__API void Config();
	MACROLIBRARY__API int GetRandomNumberInRange(const int _max, const int _min = 0);
	MACROLIBRARY__API int GetInt();
	MACROLIBRARY__API string GetLine();
	MACROLIBRARY__API void PlayGif(const string& _folderPath, const string& _filePath, const string& _fileExtension, const u_int _frameCount, const u_int _frameRate, const bool _invertColor = false);
	MACROLIBRARY__API void PlayYoshiGif();
	MACROLIBRARY__API void PlayToothlessGif();
	MACROLIBRARY__API string** GetAllFrame(const string& _folderPath, const string& _filePath, const string& _fileExtension, const u_int _frameCount, const bool _invertColor);
	MACROLIBRARY__API void PushFrame(string**& _stringArray, u_int& _stringArrayCount, string* _frame);

	class Stream
	{
		string folderPath;
		string fileName;
		string fileExtension;
		string filePath;
	public:
		MACROLIBRARY__API string GetFrame(const bool _invertColor);
	public:
		MACROLIBRARY__API Stream();
		MACROLIBRARY__API Stream(const string& _folderPath, const string& _filePath, const string& _fileExtension);
		MACROLIBRARY__API ~Stream();

	private:
		bool DoesPathExist(const string& _filePath);

	public:
		MACROLIBRARY__API void DisplayAllFile();
		MACROLIBRARY__API void CreateFilesForGif(const u_int _frameCount);

	};
};
