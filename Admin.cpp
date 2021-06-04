#include "Admin.h"

Admin::Admin()
{
	FullName[0] = '\0';
}

Admin::~Admin()
{
	if (FullName[0] != '\0')
	{
		PutInfoIntoFile();
	}
}

void Admin::ServeMessage(PostalOffice& office)
{
	if (office.GetMessagesCount() == 0)
	{
		cout << "Склад писем пуст!" << endl;
		return;
	}
	office.ShowMessages();
	cout << "Выберите сообщение: " << endl;
	int choice = MakeAChoice(office.GetMessagesCount()) - 1;
	Message message = office.GetMessage(choice);
	Client sender;
	sender.GetInfoFromFile(message.GetSenderName());
	sender.GetOutgoingMessage(message).SetStatus(2);
	vector<string> courierNames;
	FileManager::GetVectorOfCouriers(courierNames);
	if (courierNames.size() == 0)
	{
		cout << "Курьеров нет!" << endl;
	}
	cout << "Выберите курьера: " << endl;
	for (int i = 0; i < courierNames.size(); i++)
	{
		cout << i + 1 << " - " << courierNames[i] << endl;
	}
	choice = MakeAChoice(courierNames.size()) - 1;
	Courier courier;
	courier.GetInfoFromFile(courierNames[choice]);
	courier.AddMessage(message);
}

void Admin::EditMessage(PostalOffice& office)
{
	office.ShowMessages();
	cout << "Выберите сообщение, которое хотите отрдактировать: ";
	int choice = MakeAChoice(office.GetMessagesCount()) - 1;
	Message& message = office.GetMessage(choice);
	Courier oldCourier;
	oldCourier.GetInfoFromFile(message.GetCourierName());
	oldCourier.RemoveMessage(message);
	Courier newCourier;
	vector<string> courierNames;
	FileManager::GetVectorOfCouriers(courierNames);
	cout << "Выберите нового курьера: " << endl;
	for (int i = 0; i < courierNames.size(); i++)
	{
		cout << i + 1 << " - " << courierNames[i] << endl;
	}
	choice = MakeAChoice(courierNames.size()) - 1;
	newCourier.GetInfoFromFile(courierNames[choice]);
	newCourier.AddMessage(message);
}

void Admin::GetInfoFromFile(string fullName)
{
	fstream fs;
	fs.open(FileManager::GetAdminPath() + fullName, ios::binary | ios::in);
	ConvertStringToMasChar(fullName, FullName);
	fs.read((char*)&Password, sizeof(char) * 100);
	fs.close();
}

void Admin::PutInfoIntoFile()
{
	fstream fs;
	fs.open(ConnectStringAndChar(FileManager::GetAdminPath(), FullName), ios::binary | ios::out | ios::trunc);
	fs.write((char*)&Password, sizeof(char) * 100);
	fs.close();
}
