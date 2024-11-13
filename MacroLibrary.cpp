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


Macro::Stream::Stream()
{
	filePath = "";
}

Macro::Stream::Stream(const string& _folderPath, const string& _filePath, const string& _fileExtension)
{
	filePath = _folderPath + _filePath + "." + _fileExtension;
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

void Macro::Stream::DisplayText()
{
	if (!DoesPathExist(filePath)) return;

	ifstream _stream = ifstream(filePath);
	string _line;
	while (getline(_stream, _line))
	{
		cout << _line << endl;
	}
}
