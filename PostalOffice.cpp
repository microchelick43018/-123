#include "PostalOffice.h"

PostalOffice::PostalOffice()
{
	fstream fs;
	fs.open(FileManager::GetStorePath(), ios::in | ios::binary);
	int count;
	fs.read((char*)&count, sizeof(int));
	Message mess;
	for (int i = 0; i < count; i++)
	{
		mess.GetInfoFromFile(fs);
		_messages.push_back(mess);
	}
}

PostalOffice::~PostalOffice()
{
	PutInfoIntoFile();
}

void PostalOffice::AddMessage(Message& newMessage)
{
	_messages.push_back(newMessage);
}

Message& PostalOffice::GetMessage(int number)
{
	return _messages[number];
}

int PostalOffice::GetMessagesCount()
{
	return _messages.size();
}

void PostalOffice::RemoveMessage(int number)
{
	_messages.erase(_messages.begin() + number);
}

void PostalOffice::RemoveMessage(const Message& messageToDelete)
{
	for (int i = 0; i < _messages.size(); i++)
	{
		if (_messages[i] == messageToDelete)
		{
			_messages.erase(_messages.begin() + i);
			return;
		}
	}
	cout << "Ошибка! PostalOffice::RemoveMessage" << endl;
}

void PostalOffice::PutInfoIntoFile()
{
	fstream fs;
	fs.open(FileManager::GetStorePath(), ios::out | ios::binary | ios::trunc);
	int count = _messages.size();
	fs.write((char*)&count, sizeof(int));
	for (int i = 0; i < count; i++)
	{
		_messages[i].PutInfoIntoFile(fs);
	}
}

void PostalOffice::ShowMessages()
{
	cout.setf(ios::left);
	cout << setw(6) << "№";
	cout << setw(15) << "От кого";
	cout << setw(15) << "Кому";
	cout << setw(22) << "Адрес получателя";
	cout << setw(15) << "Приоритет";
	cout << setw(14) << "Статус";
	cout << setw(14) << "Оплачен";
	cout << setw(17) << "Имя курьера" << endl;
	cout.unsetf(ios::left);
	vector<Message>::iterator it = _messages.begin();
	for (int i = 0; it != _messages.end(); i++, it++)
	{
		cout << setw(6) << i + 1; (*it).ShowInfoForAdmin();
	}
}
