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
#include <cwchar>
#include <assert.h>

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
};

namespace Gif
{
	MACROLIBRARY__API void PlayGif(const string& _folderPath, const string& _filePath, const string& _fileExtension, const u_int _frameCount, const u_int _frameRate, const bool _invertColor = false);
	MACROLIBRARY__API void PlayToothlessGif();
	MACROLIBRARY__API void PlayYoshiGif();
	MACROLIBRARY__API void PlayRickRoll();
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

namespace LinkedChain
{
	template<class T>
	struct  Node
	{
		T value;
		Node<T>* next;
		Node<T>* previous;

		inline void SetNext(Node<T>*& _next)
		{
			next = _next;
		}

		inline void SetPrevious(Node<T>*& _previous)
		{
			previous = _previous;
		}

	public:
		Node(const T& _value, Node<T>* _next = nullptr, Node<T>* _previous = nullptr)
		{
			value = _value;
			next = _next;
			previous = _previous;
		}
		~Node()
		{
			delete next;
		}

	};

	template<class Type, typename SizeType = u_int>
	class LinkedList
	{
		Node<Type>* first;
		Node<Type>* last;
		SizeType count;

	private:
		inline bool IsEmpty() const
		{
			return count == 0;
		}
		inline bool IsIndexValid(const u_int _index)const 
		{
			return 0 <= _index && count >= _index;
		}

	public:
		inline SizeType GetSize() const
		{
			return count;
		}
		inline Node<Type>* GetFirst() const
		{
			return first;
		}
		inline Node<Type>* GetLast() const
		{

			return last;
		}


	public:
		LinkedList()
		{
			last = first = nullptr;
			count = 0;
		}
		LinkedList(const LinkedList<Type, SizeType>& _other)
		{
			Node<Type>* _current = first;
			while (_current)
			{
				AddFront(_current->value);
				_current = _current->next;
			}
		}

		~LinkedList()
		{
			Clear();
		}

	private:
		void CreatNewLinkedList(const Type& _value)
		{

			Node <Type>* _newNode = new Node<Type>(_value);
			last = first = _newNode;
			count++;
		}
		void DeleteNode(Node <Type>* _node)
		{
			_node->next = nullptr;
			delete _node;
		}
		Node <Type>* GetElementAtIndex(const SizeType& _indexElement)
		{
			Node <Type>* _current = first;
			for (u_int _index = 0; _index < _indexElement && _current->next; _index++)
			{
				_current = _current->next;
			}
			return _current;
		}

	public:
		//==== Add ====
		void AddFront(const Type& _value)
		{
			if (IsEmpty())
			{
				CreatNewLinkedList(_value);
				return;
			}
			Node<Type>* _newNode = new Node<Type>(_value, first);
			first->previous = _newNode;
			first = _newNode;
			count++;
		}
		void AddBack(const Type& _value)
		{
			if (IsEmpty())
			{
				CreatNewLinkedList(_value);
				return;
			}
			Node <Type>* _newNode = new Node<Type>(_value, nullptr, last);
			last->SetNext(_newNode);
			last = _newNode;
			count++;
		}
		void InsertAt(const SizeType& _indexToInsert, const Type& _value)
		{
			if (_indexToInsert < 0)
			{
				cerr << "ERROR => Invalid Index";
				return;
			}

			if (IsEmpty() || _indexToInsert == 0)
			{
				AddFront(_value);
				return;
			}
			else if (_indexToInsert >= count)
			{
				AddBack(_value);
				return;
			}

			Node <Type>* _newNode = new Node<Type>(_value);
			Node <Type>* _current = GetElementAtIndex(_indexToInsert);
			Node <Type>* _previousCurrentNode = _current->previous;
			_previousCurrentNode->SetNext(_newNode);
			_newNode->SetPrevious(_current->previous);
			_newNode->SetNext(_current);
			_current->SetPrevious(_newNode);
		}

		//==== Remove ====
		void PopFront()
		{
			if (IsEmpty())
			{
				cerr << "ERROR => empty list";
				return;
			}
			count--;
			if (count == 1)
			{
				delete last;
				return;
			}
			first = first->next;
			Node <Type>* _previousNode = first->previous;
			DeleteNode(_previousNode);
			first->previous = nullptr;
		}
		void PopBack()
		{
			if (IsEmpty()) return;
			count--;
			if (count == 1)
			{
				delete last;
				return;
			}
			last = last->previous;
			Node <Type>* _previousNode = last->next;
			DeleteNode(_previousNode);
			last->next = nullptr;
		}
		void RemoveAt(const SizeType& _indexToRemove)
		{
			if (IsEmpty()) return;
			if (_indexToRemove <= 0)
			{
				PopFront();
				return;
			}
			if (_indexToRemove >= count)
			{
				PopBack();
				return;
			}

			Node <Type>* _current = GetElementAtIndex(_indexToRemove);
			Node<Type>* _previousPreviousNode = _current->previous;
			Node<Type>* _previousNextNode = _current->next;
			_previousPreviousNode->next = _previousNextNode;
			_previousNextNode->previous = _previousPreviousNode;
			DeleteNode(_current);
		}
		void Clear()
		{
			if (IsEmpty())
			{
				DISPLAY("La liste est vide",true);
				return;
			}

			delete first;

			/*Node<Type>* _current = first;
			while (true)
			{
				_current = _current->next == nullptr ? last : _current->next;
				Node<Type>* _nodeToDelete = _current->previous;
				_current->previous = nullptr;
				delete _nodeToDelete;

				if (_current == last)
				{
					delete last;
					last = first = nullptr;
					return;
				}

			}*/
		}

		//==== Display ====
		void Display()
		{
			if (IsEmpty())return;
			Node<Type>* _current = first;
			while (_current)
			{
				DISPLAY(_current->value, true);
				_current = _current->next;
			}
		}
		void DisplayAt(const SizeType& _indexToDisplay)
		{
			if (IsEmpty())
			{
				DISPLAY("La liste est vide", true);
				return;
			}

			if (!IsIndexValid(_indexToDisplay))
			{
				cerr << "ERROR => Invalid Index";
				return;
			}
			Node<Type>* _current = GetElementAtIndex(_indexToDisplay);
			DISPLAY(_current->value, true);
		}
		string ToString()
		{
			string _text = "Le premier noeud: " + to_string(GetFirst()->value)
				+ " Le dernier noeud: " + to_string(GetLast()->value)
				+ " La liste fait: " + to_string(GetSize());
			return _text;
		}

		//==== Operator ====
		Node<Type>* operator [] (const SizeType& _index)
		{
			assert(IsValidIndex(_index) && string("L'index " + to_string(_index) + " n'est pas valide!").c_str);
			return GetElementAtIndex(_index);
		}
	};

	template<class Type, typename SizeType = u_int>
	class PriorityQueue
	{
		LinkedList<Type, SizeType>* linkedList;

	public:
		PriorityQueue()
		{
			linkedList = new LinkedList<Type, SizeType>;
		}

		~PriorityQueue()
		{
			delete linkedList;
		}
	private:
		void CheckInsertValue(Type _newValue)
		{
			SizeType _count = linkedList->GetSize();
			for (SizeType _index = 0; _index < _count; _index++)
			{
				if (linkedList[_index]<= _newValue)  return linkedList->InsertAt(_index, _newValue);
			}
		}

	public:
		void InsertValue(Type _newValue)
		{
			SizeType _count = linkedList->GetSize();
			if (_count == 0)
			{
				linkedList->AddFront(_newValue);
			}
			if (linkedList->GetFirst()->value < _newValue)
			{
				return linkedList->AddFront(_newValue);
				
			}
			else if (linkedList->GetLast()->value > _newValue)
			{
				return linkedList->AddBack(_newValue);
			}
		}
		void Display()
		{
			linkedList->Display();
		}
	
	};
};

namespace DynamicArray
{
	template<class T, typename SizeType = u_int>
	class Array
	{
		T** arrayT;
		SizeType arraySize;

	private:
		inline bool Isempty() const
		{
			return arraySize == 0;
		}

		inline bool IndexValid(const SizeType& _index)const
		{
			return 0 <= _index && arraySize >= _index;
		}

	public:
		inline T* GetT(const int _index)
		{
			return arrayT[_index];
		}
	public:
		Array()
		{
			arraySize = 0;
			arrayT = new T * [arraySize];
		}

		Array(const initializer_list<T>& _list)
		{
			arraySize = 0;
			arrayT = new T * [arraySize];
		}

		~Array()
		{
			for (u_int _index = 0; _index < arraySize; _index++)
			{
				delete arrayT[_index];
			}
			delete arrayT;
		}

	private:

	public:
		void PushBack(T* _newValue)
		{
			T** _dupeArray = new T * [arraySize + 1];
			for (u_int _index = 0; _index < arraySize; _index++)
			{
				_dupeArray[_index] = arrayT[_index];
			}
			_dupeArray[arraySize] = _newValue;
			arraySize++;
			delete[] arrayT;
			arrayT = _dupeArray;
		}

		void PushFront(T* _newValue, const SizeType& _indexToInsert)
		{
			T** _dupeArray = new T * [arraySize + 1];
			bool _hasSkip = false;
			for (u_int _index = 0; _index < arraySize + 1; _index++)
			{
				_dupeArray[_index] = arrayT[_index];
				if (_indexToInsert == _index)
				{
					_dupeArray[_index] = _newValue;
				}
			}
			arraySize++;
			delete[] arrayT;
			arrayT = _dupeArray;
		}

		void AddAt(T* _newValue, const u_int)
		{
			T** _dupeArray = new T * [arraySize + 1];
			_dupeArray[0] = _newValue;
			for (u_int _index = 0; _index < arraySize + 1; _index++)
			{
				_dupeArray[_index] = arrayT[_index];
			}
			arraySize++;
			delete[] arrayT;
			arrayT = _dupeArray;
		}

	};

	/*template<class T, typename SizeType = u_int>
	class ArrayDouble
	{
		T*** arrayT;
		SizeType row;
		SizeType column;

	private:
		inline bool Isempty() const
		{
			return row == 0 && column == 0;
		}

		inline bool IndexRow(const SizeType& _index)const
		{
			return 0 <= _index && row >= _index;
		}

		inline bool IndexColumn(const SizeType& _index)const
		{
			return 0 <= _index && column >= _index;
		}

	public:
		inline T* GetT(const int _index)
		{
			return arrayT[_index];
		}
	public:
		ArrayDouble()
		{
			arraySize = 0;
			arrayT = new T * [arraySize];
		}

		ArrayDouble(const initializer_list<T>& _list)
		{
			arraySize = 0;
			arrayT = new T * [arraySize];
		}

		~ArrayDouble()
		{
			for (u_int _index = 0; _index < arraySize; _index++)
			{
				delete arrayT[_index];
			}
			delete arrayT;
		}

	private:

	public:
		void PushBack(T* _newValue)
		{
			T** _dupeArray = new T * [arraySize + 1];
			for (u_int _index = 0; _index < arraySize; _index++)
			{
				_dupeArray[_index] = arrayT[_index];
			}
			_dupeArray[arraySize] = _newValue;
			arraySize++;
			delete[] arrayT;
			arrayT = _dupeArray;
		}

		void PushFront(T* _newValue, const SizeType& _indexToInsert)
		{
			T** _dupeArray = new T * [arraySize + 1];
			bool _hasSkip = false;
			for (u_int _index = 0; _index < arraySize + 1; _index++)
			{
				_dupeArray[_index] = arrayT[_index];
				if (_indexToInsert == _index)
				{
					_dupeArray[_index] = _newValue;
				}
			}
			arraySize++;
			delete[] arrayT;
			arrayT = _dupeArray;
		}

		void AddAt(T* _newValue, const u_int)
		{
			T** _dupeArray = new T * [arraySize + 1];
			_dupeArray[0] = _newValue;
			for (u_int _index = 0; _index < arraySize + 1; _index++)
			{
				_dupeArray[_index] = arrayT[_index];
			}
			arraySize++;
			delete[] arrayT;
			arrayT = _dupeArray;
		}

	};*/
};

