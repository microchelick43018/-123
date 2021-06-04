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
	cout << "������� ����� ������ �� ������ ������� (0 - � ���������, 1 - � �������, 2 - ���������): " << endl;
	int status = MakeAChoice(0, 2);
	list<Message>::iterator it = _messages.begin();
	for (it = _messages.begin(); it != _messages.end(); it++)
	{
		if (it->GetStatus() == status)
		{
			cout << "������� ������������: " << endl;
			cout.setf(ios::left);
			cout << setw(6) << "�";
			cout << setw(15) << "�� ����";
			cout << setw(15) << "����";
			cout << setw(22) << "����� ����������";
			cout << setw(15) << "���������";

			if (forReciever == false)
			{
				cout << setw(14) << "������";
				cout << setw(14) << "�������" << endl;
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
			cout << "������� ������������: " << endl;
			cout.setf(ios::left);
			cout << setw(6) << "�";
			cout << setw(15) << "�� ����";
			cout << setw(15) << "����";
			cout << setw(22) << "����� ����������";
			cout << setw(15) << "���������";
			cout << setw(14) << "������";
			cout << setw(14) << "�������" << endl;
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
	cout << "������� ��� ����������: ";
	getline(cin, recieverName);
	cout << "������� ����� ����������: ";
	getline(cin, recieverAdress);
	cout << "������� ��������� (�� 1 �� 10, 1 - ����� �������): ";
	priorety = MakeAChoice(10);
	status = 0;
	cin.ignore(50, '\n');
	cin.clear();
	cout << "������� ����� ������: " << endl;
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
	cout << "������� ����� �������� (������� - 50, �������� - 1000): " << endl;
	int dep = MakeAChoice(50, 100000);
	if (ReadBankCard() == true)
	{
		_balance += dep;
	}
}

void Client::ShowBalance()
{
	cout << "������: " << _balance << '$' << endl;
}

int Client::GetBalance()
{
	return _balance;
}

void Client::PayForMessage(PostalOffice& office)
{
	if (_balance < 100)
	{
		cout << "� ��� ������������ ������� ��� ������!" << endl;
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
		cout << "� ��� ��� ���������� ���������!" << endl;
		return;
	}
	cout << "�������� ������������ ���������: " << endl;
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
		cout << "�������!" << endl;
	}
	else
	{
		cout << "������ ��� ��������!" << endl;
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
	cout << setw(6) << "�";
	cout << setw(15) << "�� ����";
	cout << setw(15) << "����";
	cout << setw(22) << "����� ����������";
	cout << setw(15) << "���������" << endl;
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
	cout << "1 - ����������� �������� ���������." << endl;
	cout << "2 - ����������� ��������� ���������." << endl;
	int choice = MakeAChoice(2);
	list<Message>& messages = _incomingMessages;
	if (choice == 2)
	{
		isIncomingMessage = false;
		messages = _outgoingMessages;
	}
	if (messages.size() == 0)
	{
		cout << "������ ����!" << endl;
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
		cout << "1 - ������������� �� ����� �����������." << endl;
		cout << "2 - ������������� �� �������." << endl;
		cout << "3 - ������ �� �������." << endl;
		cout << "4 - ����������� ����� ���������." << endl;
		if (isIncomingMessage == false)
		{
			cout << "5 - ����� �� ������ ����������." << endl;
			cout << "6 - �����." << endl;
		}
		else
		{
			cout << "5 - �����." << endl;
		}
		choice = MakeAChoice(6 - isIncomingMessage);
		if (isIncomingMessage == true && choice == 5)
		{
			exit = true;
			cout << "������� �� ����� �������, ����� ����������..." << endl;
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
			cout << "�������� ���������, ������� ������ �����������: " << endl;
			int choice2 = MakeAChoice(messages.size()) - 1;
			list<Message>::iterator it = messages.begin();
			advance(it, choice2);
			it->ShowText();
			break;
		}
		case 5:
		{
			cout << "������� �����, ������� ������ �����: " << endl;
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
		cout << "������� �� ����� �������, ����� ����������..." << endl;
		_getch();
	}
}

void Client::ShowOutgoingMessages()
{
	if (_outgoingMessages.size() == 0)
	{
		cout << "����� ���!" << endl;
		return;
	}
	cout.setf(ios::left);
	cout << setw(6) << "�";
	cout << setw(15) << "�� ����";
	cout << setw(15) << "����";
	cout << setw(22) << "����� ����������";
	cout << setw(15) << "���������";
	cout << setw(14) << "������";
	cout << setw(14) << "�������" << endl;
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
