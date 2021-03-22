#include <iostream>
#include <fstream>//для работы с чтением и записью данных из файлов и в файлы
#include <string>
using namespace std;

//открытие файла для чтения. Закидывает все в path
string open_file(string path)
{
	ifstream file; //ifstream отвечает за чтение данных из файла
	file.open(path);
	string book = string();

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		cout << "Файл открыт!" << endl;
		char char_;

		while (file.get(char_)) //метод get посимвольно считывает данные из файла
		{
			book.push_back(char_);
		}
	}

	file.close();
	return book;
}

void open_file_rewrite(string path, string new_string)
{
	ofstream file; //ofstream отвечает за возможность сохранения данных в файл
	file.open(path);

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		file << new_string;
	}

	file.close();
}

class H_List
{
private:

	class Node
	{
	public:
		Node* pNext;
		Node* pDown;
		string data;

		Node(string data_ = string(), Node* pNext_ = nullptr, Node* pDown_ = nullptr)
		{
			data = data_;
			pNext = pNext_;
			pDown = pDown_;
		}
	};

	int sizeString;
	int sizeWords;
	Node* head;

public:
	//конструктор
	H_List()
	{
		head = nullptr;
		sizeString = 0;
		sizeWords = 0;
	}

	//деструктор
	~H_List()
	{
		if (head != nullptr)
		{

			while (1)
			{
				if (head->pDown == nullptr && head->pNext == nullptr)
				{
					break;
				}
				Node* curent = head;
				Node* prev = head;

				while (curent->pNext != nullptr)
				{
					curent = curent->pNext;
					if (curent->pNext != nullptr)
					{
						prev = prev->pNext;
					}
				}

				if (curent->pDown != nullptr)
				{
					curent = curent->pDown;
					if (prev->pNext != nullptr)
					{
						prev = prev->pNext;
					}


					if (curent->pNext != nullptr)
					{
						prev = prev->pDown;
						while (curent->pNext != nullptr)
						{
							curent = curent->pNext;
							if (curent->pNext != nullptr)
							{
								prev = prev->pNext;
							}
						}
						delete curent;
						prev->pNext = nullptr;
						continue;

					}
					delete curent;
					prev->pDown = nullptr;
					continue;
				}

				delete curent;
				prev->pNext = nullptr;

			}
			Node* helper = head;
			delete head;
			helper = nullptr;
		}
	}

	//взятие текста
	void pushBack(string data)
	{
		if (head == nullptr)
		{
			//распределение строк
			string str = string();
			int i;
			for (i = 0; i < data.size(); i++)
			{
				if (data[i] == '\n')
				{
					i++;
					break;	
				}
				str.push_back(data[i]);
			}

			head = new Node(str);
			sizeString++;
			str = string();
			Node* curent = head;

			for (; i < data.size(); i++)
			{
				if (data[i] == '\n')
				{
					curent->pNext = new Node(str);
					curent = curent->pNext;
					sizeString++;
					str = string();
					continue;
				}
				str.push_back(data[i]);
			}

			//распределение слов
			curent = head;
			str = string();
			i = 0;
			int counter = 0;
			Node* curentLeft = head;
			while (curentLeft != nullptr)
			{
				curent = curentLeft;
				for (; i < curentLeft->data.size(); i++)
				{
					if (curentLeft->data[i] == ' ')
					{
						if (counter == 0)
						{
							curent->pDown = new Node(str);
							curent = curent->pDown;
							sizeWords++;
							str = string();
							counter = 1;
							continue;
						}
						else
						{
							curent->pNext = new Node(str);
							curent = curent->pNext;
							sizeWords++;
							str = string();
							continue;
						}
					}
					str.push_back(curentLeft->data[i]);
				}
				curentLeft = curentLeft->pNext;
				i = 0;
				counter = 0;
			}
		}
		else
		{
			Node* headd = head;
			while (headd->pNext != nullptr)
			{
				headd = headd->pNext;
			}

			//распределение строк
			string str = string();
			int i;
			for (i = 0; i < data.size(); i++)
			{
				if (data[i] == '\n')
				{
					i++;
					break;
				}
				str.push_back(data[i]);
			}

			headd->pNext = new Node(str);
			sizeString++;
			str = string();
			Node* curent = headd->pNext;

			for (; i < data.size(); i++)
			{
				if (data[i] == '\n')
				{
					curent->pNext = new Node(str);
					curent = curent->pNext;
					sizeString++;
					str = string();
					continue;
				}
				str.push_back(data[i]);
			}

			//распределение слов
			curent = headd->pNext;
			str = string();
			i = 0;
			int counter = 0;
			Node* curentLeft = headd->pNext;
			while (curentLeft != nullptr)
			{
				curent = curentLeft;
				for (; i < curentLeft->data.size(); i++)
				{
					if (curentLeft->data[i] == ' ')
					{
						if (counter == 0)
						{
							curent->pDown = new Node(str);
							curent = curent->pDown;
							sizeWords++;
							str = string();
							counter = 1;
							continue;
						}
						else
						{
							curent->pNext = new Node(str);
							curent = curent->pNext;
							sizeWords++;
							str = string();
							continue;
						}
					}
					str.push_back(curentLeft->data[i]);
				}
				curentLeft = curentLeft->pNext;
				i = 0;
				counter = 0;
			}
		}
	}

	void printString(int index)
	{
		int counter = 1;
		Node* curent = head;
		while (curent != nullptr)
		{
			if (counter == index)
			{
				cout << curent->data << endl;
				return void();
			}
			counter++;
			curent = curent->pNext;
		}
		cout << "Ошибка, не найдена нужная строка!" << endl;
	}

	void printWord(int string, int word)
	{
		int counterS = 1;
		int counterW = 1;
		Node* curent = head;
		while (curent != nullptr)
		{
			if (counterS == string)
			{
				curent = curent->pDown;
				while (curent != nullptr)
				{
					if (counterW == word)
					{
						cout << curent->data << endl;
						return void();
					}
					counterW++;
					curent = curent->pNext;
				}
				cout << "Слово не найдено" << endl;
				return void();
			}
			counterS++;
			curent = curent->pNext;
		}
		cout << "Ошибка, не найдено нужное слово!" << endl;
	}

	//запись
	void rewrite_by_words(int indexS, int indexW)
	{
		int counterS = 1;
		int counterW = 1;
		Node* curent = head;
		while (curent != nullptr)
		{
			if (counterS == indexS)
			{
				curent = curent->pDown;
				while (curent != nullptr)
				{
					if (counterW == indexW)
					{
						cout << "Введите слово:" << endl;
						string str = string();
						cin >> str;
						curent->data = str;
						return void();
					}
					counterW++;
					curent = curent->pNext;
				}
				cout << "Слово не найдено!" << endl;
				return void();
			}
			counterS++;
			curent = curent->pNext;
		}
		cout << "Ошибка, слово не найдено!" << endl;
	}

	//сохранение
	string save_by_words()
	{
		string str = string();
		Node* curent = head;
		Node* helper = head;
		while (helper != nullptr)
		{
			curent = helper;
			curent = curent->pDown;

			while (curent != nullptr)
			{
				for (int i = 0; i < curent->data.size(); i++)
				{
					str.push_back(curent->data[i]);
				}

				str.push_back(' ');
				curent = curent->pNext;
			}
			str.push_back('\n');
			helper = helper->pNext;
		}
		return str;
	}

	int GetSizeW()
	{
		return sizeWords;
	}

	int GetSizeS()
	{
		return sizeString;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	string path = "example.txt";
	H_List a;
	a.pushBack(open_file(path));
	a.pushBack("No way \n");
	a.printWord(3, 2);
	//a.rewrite_by_words(2, 1);
	//a.printWords(2, 1);
	//open_file_rewrite(path, a.save_by_words());

	cout << a.GetSizeS() << endl;
	cout << a.GetSizeW() << endl;

	return 0;
}