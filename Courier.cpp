#include "Courier.h"

Courier::Courier()
{
	
}

Courier::~Courier()
{
	PutInfoIntoFile();
}

void Courier::AddMessage(const Message& newMessage)
{
	_messages.push_back(newMessage);
}

Message& Courier::getMessage(const Message& messageToGet)
{
	for (int i = 0; i < _messages.size(); i++)
	{
		if (messageToGet == _messages[i])
		{
			return _messages[i];
		}
	}
	cout << "Ошибка! Courier::GetMessage" << endl;
}

void Courier::GetInfoFromFile(string fullName)
{
	fstream fs;
	fs.open(FileManager::GetCourierPath() + fullName, ios::in | ios::binary);
	fs.read((char*)&Password, sizeof(char) * 100);
	int count;
	fs.read((char*)&count, sizeof(int));
	Message message;
	for (int i = 0; i < count; i++)
	{
		message.GetInfoFromFile(fs);
		_messages.push_back(message);
	}
	fs.close();
}

void Courier::PutInfoIntoFile()
{
	fstream fs;
	fs.open(FileManager::GetCourierPath() + ConvertMasCharToString(FullName), ios::out | ios::trunc | ios::binary);
	fs.write((char*)&Password, sizeof(char) * 100);
	int count = _messages.size();
	fs.write((char*)&count, sizeof(int));
	for (int i = 0; i < count; i++)
	{
		_messages[i].PutInfoIntoFile(fs);
	}
	fs.close();
}

void Courier::RemoveMessage(const Message& messageToDelete)
{
	for (int i = 0; i < _messages.size(); i++)
	{
		if (_messages[i] == messageToDelete)
		{
			_messages.erase(_messages.begin() + i);
			return;
		}
	}
	cout << "Ошибка! Courier::RemoveMessage" << endl;
}

void Courier::ServeMessage(PostalOffice& office)
{
	if (_messages.size() == 0)
	{
		cout << "Нечего обслуживать!" << endl;
		return;
	}
	ShowMessages();
	cout << "Выберите сообщение, которое хотите обслужить: " << endl;
	int choice = MakeAChoice(_messages.size()) - 1;
	Client reciever;
	Client sender;
	reciever.GetInfoFromFile(_messages[choice].GetReciverName());
	sender.GetInfoFromFile(_messages[choice].GetSenderName());
	Message& senderMessage = sender.GetOutgoingMessage(_messages[choice]);
	senderMessage.SetStatus(3);
	if (reciever.GetFullName()[0] == '\0')
	{
		cout << "Указан не тот адрес или пользователь. Письмо никто не получит" << endl;
	}
	else
	{
		reciever.AddIncomingMessage(_messages[choice]);
	}
	office.RemoveMessage(_messages[choice]);
}

void Courier::ShowMessages()
{
	if (_messages.size() == 0)
	{
		cout << "Письм нет!" << endl;
		return;
	}
	cout << setw(6) << "№";
	cout << setw(15) << "От кого";
	cout << setw(15) << "Кому";
	cout << setw(22) << "Адрес получателя";
	cout << setw(15) << "Приоритет";
	cout << setw(14) << "Статус";
	cout << setw(14) << "Оплачен" << endl;
	vector<Message>::iterator it = _messages.begin();
	for (int i = 0; it != _messages.end(); i++, it++)
	{
		cout << setw(6) << i + 1 << " - "; (*it).ShowInfo(false);
	}
}
