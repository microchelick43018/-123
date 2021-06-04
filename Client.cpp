#include "Client.h"

void Client::SortMessagesBySenderName(list<Message>& _messages)
{
	list<Message>::iterator it = _messages.begin();
	list<Message>::iterator it2 = _messages.begin();
	for (it = _messages.begin(); it != _messages.end(); it++)
	{
		for (it2 = _messages.begin(); it2 != _messages.end(); it2++)
		{
			if (it->GetSenderName() > it2->GetSenderName())
			{
				swap<Message>(*it, *it2);
			}
		}
	}
}

void Client::SortMessagesByStatus(list<Message>& _messages)
{
	list<Message>::iterator it = _messages.begin();
	list<Message>::iterator it2 = _messages.begin();
	for (it = _messages.begin(); it != _messages.end(); it++)
	{
		for (it2 = _messages.begin(); it2 != _messages.end(); it2++)
		{
			if (it->GetStatus() > it2->GetStatus())
			{
				swap<Message>(*it, *it2);
			}
		}
	}
}

void Client::FilterMessagesByStatus(list<Message>& _messages, bool forReciever)
{
	cout << "Введите какой статус вы хотите увидеть (0 - В обработке, 1 - у курьера, 2 - доставлен): " << endl;
	int status = MakeAChoice(0, 2);
	list<Message>::iterator it = _messages.begin();
	for (it = _messages.begin(); it != _messages.end(); it++)
	{
		if (it->GetStatus() == status)
		{
			cout << "Найдено соответствие: " << endl;
			cout.setf(ios::left);
			cout << setw(6) << "№";
			cout << setw(15) << "От кого";
			cout << setw(15) << "Кому";
			cout << setw(22) << "Адрес получателя";
			cout << setw(15) << "Приоритет";

			if (forReciever == false)
			{
				cout << setw(14) << "Статус";
				cout << setw(14) << "Оплачен" << endl;
			}
			else
			{
				cout << endl;
			}
			cout.unsetf(ios::left);
			break;
		}
	}
	for (; it != _messages.end(); it++)
	{
		if (it->GetStatus() == status)
		{
			it->ShowInfo(forReciever);
		}
	}
}

void Client::FindMessagesByAdress(list<Message>& _messages, string adress)
{
	list<Message>::iterator it = _messages.begin();
	for (; it != _messages.end(); it++)
	{
		if (it->GetReciverAdress() == adress)
		{
			cout << "Найдено соответствие: " << endl;
			cout.setf(ios::left);
			cout << setw(6) << "№";
			cout << setw(15) << "От кого";
			cout << setw(15) << "Кому";
			cout << setw(22) << "Адрес получателя";
			cout << setw(15) << "Приоритет";
			cout << setw(14) << "Статус";
			cout << setw(14) << "Оплачен" << endl;
			cout.unsetf(ios::left);
			break;
		}
	}
	for (int i = 0; it != _messages.end(); it++, i++)
	{
		if (it->GetReciverAdress() == adress)
		{
			cout.setf(ios::left);
			cout << setw(6) << i + 1; it->ShowInfo(false);
			cout.unsetf(ios::left);
		}
	}
}

Client::Client()
{
	_balance = 0;
	FullName[0] = '\0';
}

Client::Client(const Client& obj) : User(obj)
{
	_balance = obj._balance;
}

Client::~Client()
{
	if (FullName[0] != '\0')
	{
		PutInfoIntoFile();
	}
}

void Client::AddIncomingMessage(Message& mess)
{
	_incomingMessages.push_back(mess);
}

void Client::AddOutgoingMessage(Message& mess)
{
	_outgoingMessages.push_back(mess);
}

void Client::CreateMessage(PostalOffice& office)
{
	string text, senderName, recieverName, recieverAdress;
	bool isPayed = false; int priorety; int status;
	Message newMessage;
	cin.clear();
	cin.ignore(100, '\n');
	cout << "Введите имя получателя: ";
	getline(cin, recieverName);
	cout << "Введите адрес получателя: ";
	getline(cin, recieverAdress);
	cout << "Задайте приоритет (от 1 до 10, 1 - очень срочный): ";
	priorety = MakeAChoice(10);
	status = 0;
	cin.ignore(50, '\n');
	cin.clear();
	cout << "Введите текст письма: " << endl;
	getline(cin, text);
	newMessage.Set(text, ConvertMasCharToString(FullName), recieverName, recieverAdress, isPayed, priorety, status);
	_outgoingMessages.push_back(newMessage);
}

Message& Client::GetOutgoingMessage(Message messToFind)
{
	list<Message>::iterator it = _outgoingMessages.begin();
	for (; it != _outgoingMessages.end(); it++)
	{
		if (*it == messToFind)
		{
			return *it;
		}
	}
}

void Client::PutInfoIntoFile()
{
	fstream fs;
	fs.open(FileManager::GetClientPath() + ConvertMasCharToString(FullName), ios::out | ios::trunc | ios::binary);
	fs.write((char*)&Password, sizeof(char) * 100);
	fs.write((char*)&_balance, sizeof(int));
	int incomingMessagesSize = _incomingMessages.size();
	int outgoingMessagesSize = _outgoingMessages.size();
	fs.write((char*)&incomingMessagesSize, sizeof(int));
	for (auto message : _incomingMessages)
	{
		message.PutInfoIntoFile(fs);
	}
	fs.write((char*)&outgoingMessagesSize, sizeof(int));
	for (auto message : _outgoingMessages)
	{
		message.PutInfoIntoFile(fs);
	}
	fs.close();
}

void Client::GetInfoFromFile(string fullName)
{
	fstream fs;
	fs.open(FileManager::GetClientPath() + fullName, ios::in | ios::binary);
	ConvertStringToMasChar(fullName, FullName);
	fs.read((char*)&Password, sizeof(char) * 100);
	fs.read((char*)&_balance, sizeof(int));
	int incomingMessagesSize;
	int outgoingMessagesSize;
	fs.read((char*)&incomingMessagesSize, sizeof(int));
	Message mess;
	for (int i = 0; i < incomingMessagesSize; i++)
	{
		mess.GetInfoFromFile(fs);
		_incomingMessages.push_back(mess);
	}
	fs.read((char*)&outgoingMessagesSize, sizeof(int));
	for (int i = 0; i < outgoingMessagesSize; i++)
	{
		mess.GetInfoFromFile(fs);
		_outgoingMessages.push_back(mess);
	}
	fs.close();
}

void Client::MakeADeposit()
{
	cout << "Введите сумму депозита (минимум - 50, максимум - 1000): " << endl;
	int dep = MakeAChoice(50, 100000);
	if (ReadBankCard() == true)
	{
		_balance += dep;
	}
}

void Client::ShowBalance()
{
	cout << "Баланс: " << _balance << '$' << endl;
}

int Client::GetBalance()
{
	return _balance;
}

void Client::PayForMessage(PostalOffice& office)
{
	if (_balance < 100)
	{
		cout << "У вас недостаточно средств для оплаты!" << endl;
	}
	bool hasUnpayedMess = false;
	list<Message>::iterator it = _outgoingMessages.begin();
	for (; it != _outgoingMessages.end(); it++)
	{
		if ((*it).GetPayed() == false)
		{
			hasUnpayedMess = true;
			break;
		}
	}
	if (hasUnpayedMess == false)
	{
		cout << "У вас нет оплаченных сообщений!" << endl;
		return;
	}
	cout << "Выберите неоплаченное сообщение: " << endl;
	ShowOutgoingMessages();
	int choice = MakeAChoice(_outgoingMessages.size()) - 1;
	it = _outgoingMessages.begin();
	advance(it, choice);
	bool& b = it->GetPayed();
	if (b == false)
	{

		b = true;
		office.AddMessage(*it);
		_balance -= 100;
		cout << "Успешно!" << endl;
	}
	else
	{
		cout << "Письмо уже оплачено!" << endl;
		return;
	}
}

void Client::SetBalance(int newBalance)
{
	_balance = newBalance;
}

void Client::ShowIncomingMessages()
{
	cout.setf(ios::left);
	cout << setw(6) << "№";
	cout << setw(15) << "От кого";
	cout << setw(15) << "Кому";
	cout << setw(22) << "Адрес получателя";
	cout << setw(15) << "Приоритет" << endl;
	cout.unsetf(ios::left);
	list<Message>::iterator it = _incomingMessages.begin();
	for (int i = 0; it != _incomingMessages.end(); i++, it++)
	{
		cout.setf(ios::left);
		cout << setw(6) << i + 1;
		cout.unsetf(ios::left);
		(*it).ShowInfo(true);
	}
	cout << endl;
}

void Client::ShowHistory()
{
	system("cls");
	bool isIncomingMessage = true;
	cout << "1 - Просмотреть входящие сообщения." << endl;
	cout << "2 - Просмотреть исходящие сообщения." << endl;
	int choice = MakeAChoice(2);
	list<Message>& messages = _incomingMessages;
	if (choice == 2)
	{
		isIncomingMessage = false;
		messages = _outgoingMessages;
	}
	if (messages.size() == 0)
	{
		cout << "Список пуст!" << endl;
		return;
	}
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		if (isIncomingMessage == true)
		{
			ShowIncomingMessages();
		}
		else
		{
			ShowOutgoingMessages();
		}
		cout << "1 - Отсортировать по имени отправителя." << endl;
		cout << "2 - Отсортировать по статусу." << endl;
		cout << "3 - Фильтр по статусу." << endl;
		cout << "4 - Просмотреть текст сообщения." << endl;
		if (isIncomingMessage == false)
		{
			cout << "5 - Найти по адресу получателя." << endl;
			cout << "6 - Выход." << endl;
		}
		else
		{
			cout << "5 - Выход." << endl;
		}
		choice = MakeAChoice(6 - isIncomingMessage);
		if (isIncomingMessage == true && choice == 5)
		{
			exit = true;
			cout << "Нажмите на любую клавишу, чтобы продолжить..." << endl;
			_getch();
			break;
		}
		switch (choice)
		{
		case 1:
		{
			SortMessagesBySenderName(messages);
			break;
		}
		case 2:
		{
			SortMessagesByStatus(messages);
			break;
		}
		case 3:
		{
			FilterMessagesByStatus(messages, isIncomingMessage);
			break;
		}
		case 4:
		{
			cout << "Выберите сообщение, которое хотите просмотреть: " << endl;
			int choice2 = MakeAChoice(messages.size()) - 1;
			list<Message>::iterator it = messages.begin();
			advance(it, choice2);
			it->ShowText();
			break;
		}
		case 5:
		{
			cout << "Введите адрес, который хотите найти: " << endl;
			string adress;
			cin.clear();
			cin.ignore(50, '\n');
			getline(cin, adress);
			FindMessagesByAdress(messages, adress);
			break;
		}
		case 6:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
		cout << "Нажмите на любую клавишу, чтобы продолжить..." << endl;
		_getch();
	}
}

void Client::ShowOutgoingMessages()
{
	if (_outgoingMessages.size() == 0)
	{
		cout << "Письм нет!" << endl;
		return;
	}
	cout.setf(ios::left);
	cout << setw(6) << "№";
	cout << setw(15) << "От кого";
	cout << setw(15) << "Кому";
	cout << setw(22) << "Адрес получателя";
	cout << setw(15) << "Приоритет";
	cout << setw(14) << "Статус";
	cout << setw(14) << "Оплачен" << endl;
	cout.unsetf(ios::left);
	list<Message>::iterator it = _incomingMessages.begin();
	for (int i = 0; it != _incomingMessages.end(); i++, it++)
	{
		cout.setf(ios::left);
		cout << setw(6) << i + 1;
		cout.unsetf(ios::left);
		(*it).ShowInfo(false);
	}
	cout << endl;
}
