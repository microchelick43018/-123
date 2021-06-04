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
	cout << "Выберите сообщение (0 - отмена): " << endl;
	int choice = MakeAChoice(0, office.GetMessagesCount()) - 1;
	Message& message = office.GetMessage(choice);
	while (message.GetCourierName()[0] != '\0' && choice != -1)
	{
		cout << "это сообщение уже обслужено. Выберите другое." << endl;
		choice = MakeAChoice(0, office.GetMessagesCount()) - 1;
	}
	if (choice == -1)
	{
		return;
	}
	Client sender;
	sender.GetInfoFromFile(message.GetSenderName());
	sender.GetOutgoingMessage(message).SetStatus(2);
	message.SetStatus(2);
	vector<string> courierNames;
	FileManager::GetVectorOfCouriers(courierNames);
	if (courierNames.size() == 0)
	{
		cout << "Курьеров нет!" << endl;
		return;
	}
	cout << "Выберите курьера: " << endl;
	for (int i = 0; i < courierNames.size(); i++)
	{
		cout << i + 1 << " - " << courierNames[i] << endl;
	}
	choice = MakeAChoice(courierNames.size()) - 1;
	Courier courier;
	courier.GetInfoFromFile(courierNames[choice]);
	sender.GetOutgoingMessage(message).SetCourierName(courier.GetFullName());
	message.SetCourierName(courier.GetFullName());
	courier.AddMessage(message);
}

void Admin::EditMessage(PostalOffice& office)
{
	office.ShowMessages();
	cout << "Выберите сообщение, которое хотите отредактировать (0 - отмена): ";
	int choice = MakeAChoice(0, office.GetMessagesCount()) - 1;
	if (choice == -1)
	{
		return;
	}
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
	message.SetCourierName(newCourier.GetFullName());
	newCourier.AddMessage(message);

	message.SetCourierName(oldCourier.GetFullName());
	Client sender;
	sender.GetInfoFromFile(message.GetSenderName());
	sender.GetOutgoingMessage(message).SetCourierName(message.GetSenderName());
	message.SetCourierName(newCourier.GetFullName());
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
