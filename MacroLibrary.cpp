#include "pch.h"
#include "MacroLibrary.h"

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

MACROLIBRARY__API void Macro::PlayGif(const string& _folderPath, const string& _filePath, const string& _fileExtension, const u_int _frameCount ,const u_int _frameRate)
{
	int _indexBuffer1 = 1;
	int _indexBuffer2;
	Stream _stream;
	Stream _streamBuffer1;
	Stream _streamBuffer2;
	HANDLE _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO _info;
	_info.dwSize = 100;
	_info.bVisible = FALSE;
	while (true)
	{
		
		Sleep(_frameRate);
		_streamBuffer1 = Stream(_folderPath, to_string(_indexBuffer1) + _filePath, _fileExtension);
		_indexBuffer2 = (((_indexBuffer1 + 1) % (_frameCount + 1))) == 0 ? 1 : _indexBuffer1 + 1;
		_streamBuffer2 = Stream(_folderPath, to_string(_indexBuffer2) + _filePath, _fileExtension);

		_stream = _streamBuffer1;
		SetConsoleCursorInfo(_consoleHandle, &_info);
		SetConsoleCursorPosition(_consoleHandle, { 0, 0 });
		_streamBuffer1.DisplayAllFile();

		_stream = _streamBuffer2;
		SetConsoleCursorInfo(_consoleHandle, &_info);
		SetConsoleCursorPosition(_consoleHandle, { 0, 0 });
		_stream.DisplayAllFile();

		_indexBuffer1 = (((_indexBuffer2 + 1) % (_frameCount + 1))) == 0 ? 1 : _indexBuffer2 + 1;
		if (_kbhit())break;
	}
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
