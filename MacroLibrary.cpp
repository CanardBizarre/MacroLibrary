#include "pch.h"
#include "MacroLibrary.h"
#include "Color.h"

void Macro::Config()
{
	locale::global(locale("fr_FR"));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

int Macro::GetRandomNumberInRange(const int _max, const int _min)
{
	random_device _rSeed; // Obtient un graine aléatoire
	mt19937 _gen(_rSeed()); // Initialise le générateur avec la graine
	uniform_int_distribution<> _distr(_min, _max); // Définit la distribution (les limites)
	return _distr(_gen); // Génération du nombre
}

int Macro::GetInt()
{
	int _value;
	bool _isValid;
	do
	{
		cin >> _value;
		_isValid = cin.good();
		CLEAR;


	} while (!_isValid);

	return _value;
}

string Macro::GetLine()
{
	string _line = string();
	bool _wantToQuit;
	do
	{
		const int _charASCII = getchar();
		_wantToQuit = _charASCII == EOF || _charASCII == '\n';

		if (!_wantToQuit)
		{
			_line += char(_charASCII);
		}

	} while (!_wantToQuit);

	return _line;
}

MACROLIBRARY__API void Macro::PlayGif(const string& _folderPath, const string& _filePath, const string& _fileExtension, const u_int _frameCount ,const u_int _frameRate, const bool _invertColor)
{
	string** _allFrame = GetAllFrame(_folderPath, _filePath, _fileExtension, _frameCount, _invertColor);
	int _index = 0;
	HANDLE _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO _info;
	_info.dwSize = 100;
	_info.bVisible = FALSE;
	string _frame1 = *_allFrame[_index];
	string _frame2;
	while (true)
	{
		SetConsoleCursorInfo(_consoleHandle, &_info);

		Sleep(_frameRate);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0});
		printf("%s", _frame1.c_str());


		_index = (((_index + 1) % (_frameCount - 1))) == 0 ? 1 : _index + 1;
		_frame2 = *_allFrame[_index];

		_index = (((_index + 1) % (_frameCount- 1))) == 0 ? 1 : _index + 1;
		_frame1 = *_allFrame[_index];

		Sleep(_frameRate);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0});
		printf("%s", _frame2.c_str());

		if (_kbhit())break;
	}
	for (u_int _index = 0; _index < _frameCount; _index++)
	{
		delete _allFrame[_index];
	}
	delete[] _allFrame;
}

MACROLIBRARY__API void Macro::PlayYoshiGif()
{
	return PlayGif("D:\\HUYNH_Vuong-Tu\\Libraries\\MacroLibrary\\YoshiGif\\", "_YoshiAscii", "txt", 20, 90);
}

MACROLIBRARY__API void Macro::PlayToothlessGif()
{
	return PlayGif("D:\\HUYNH_Vuong-Tu\\Libraries\\MacroLibrary\\ToothlessGif\\", "_ToothlessAscii", "txt", 223, 45, true);;
}

MACROLIBRARY__API string** Macro::GetAllFrame(const string& _folderPath, const string& _filePath, const string& _fileExtension, const u_int _frameCount, const bool _invertColor)
{
	u_int _stringArrayCount = 0;
	string** _stringArray = new string*[_frameCount];
	Stream _stream;
	for (u_int _index = 0; _index < _frameCount; _index++)
	{
		_stream = Stream(_folderPath, to_string(_index + 1) + _filePath, _fileExtension);
		string* _frame = new string(_stream.GetFrame(_invertColor));
		_stringArray[_index] = _frame;
	}
	return _stringArray;
}

MACROLIBRARY__API void Macro::PushFrame(string**& _stringArray, u_int& _stringArrayCount,  string* _frame)
{
	string** _dupeArray = new string*[_stringArrayCount + 1];
	for (u_int _index = 0; _index < _stringArrayCount; _index++)
	{
		_dupeArray[_index] = _stringArray[_index];
	}
	_dupeArray[_stringArrayCount] = _frame;
	_stringArrayCount++;
	delete[] _stringArray;
	_stringArray = _dupeArray;
}


MACROLIBRARY__API string Macro::Stream::GetFrame(const bool _invertColor)
{
	if (!DoesPathExist(filePath))
	{
		return "";
	}
	string _color;
	if (_invertColor) _color = BLACK_INTENSE_TEXT + string(WHITE_INTENSE_BG);
	ifstream _stream = ifstream(filePath);
	string _file = _color;
	string _line;
	while (getline(_stream, _line))
	{
		_file += _line + "\n";
	}
	return _file + RESET;
}

Macro::Stream::Stream()
{
	folderPath = "";
	filePath = "";
	fileExtension = "";
	filePath = "";
}

Macro::Stream::Stream(const string& _folderPath, const string& _filePath, const string& _fileExtension)
{
	folderPath = _folderPath;
	fileName = _filePath;
	fileExtension = _fileExtension;
	filePath = folderPath + fileName + "." + fileExtension;
}

Macro::Stream::~Stream()
{
}

bool Macro::Stream::DoesPathExist(const string& _filePath)
{
	ifstream _stream = ifstream(_filePath);
	if (!_stream)
	{
		cerr << "ERROR => the file : " << _filePath << " doesn't exist !" << endl;
		return false;
	}
	return true;
}

void Macro::Stream::DisplayAllFile()
{
	if (!DoesPathExist(filePath)) return;

	ifstream _stream = ifstream(filePath);
	string _file;
	string _line;
	while (getline(_stream, _line))
	{
		_file += _line + "\n";
	}
	DISPLAY(_file, false);
}

MACROLIBRARY__API void Macro::Stream::CreateFilesForGif(const u_int _frameCount)
{
 	for (u_int _index = 0; _index < _frameCount; _index++)
	{
		string _filePath = folderPath + to_string(_index+1) + filePath + "." + fileExtension;
		ofstream _stream = ofstream(_filePath);
		_stream << "";
	}
	
}
