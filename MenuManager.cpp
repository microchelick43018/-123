#include "MenuManager.h"
PostalOffice postalOffice;

namespace MenuManager
{
	void ShowClientMenu()
	{
		cout << "1 - Создать письмо." << endl;
		cout << "2 - Пополнить баланс." << endl;
		cout << "3 - Оплатить письмо." << endl;
		cout << "4 - Просмотр истории письм." << endl;
		cout << "5 - Выход из аккаунта" << endl;
	}

	void MenuManager::ShowAdminMenu()
	{
		cout << "1 - Обслужить письма." << endl;
		cout << "2 - Сменить курьера определенного письма." << endl;
		cout << "3 - Выход из аккаунта." << endl;
	}

	void MenuManager::ShowMainMenu()
	{
		cout << "1 - Войти как клиент." << endl;
		cout << "2 - Войти как администратор." << endl;
		cout << "3 - Войти как курьер." << endl;
		cout << "4 - Зарегистрироваться как клиент." << endl;
		cout << "5 - Зарегистрироваться как администратор." << endl;
		cout << "6 - Зарегистрироваться как курьер." << endl;
		cout << "7 - Выйти из программы." << endl;
	}

	void MenuManager::ShowCourierMenu()
	{
		cout << "1 - Просмотр списка писем." << endl;;
		cout << "2 - Обслужить следующее письмо." << endl;
		cout << "3 - Выйти из программы." << endl;
	}
}

void MakingChoice::TabtoContinue()
{
	cout << "Нажмите любую клавишу, чтобы продолжить...";
	_getch();
}

void MakingChoice::WorkAsUser()
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		MenuManager::ShowMainMenu();
		choice = MakeAChoice(7);
		switch (choice)
		{
		case 1:
		{
			shared_ptr<Client> client = make_shared<Client>();
			bool b = client->LogIn(FileManager::GetClientPath());
			if (b == true)
			{
				client->GetInfoFromFile(client->GetFullName());
				WorkAsClient(*client);
			}
			break;
		}
		case 2:
		{
			shared_ptr<Admin> admin = make_shared<Admin>();
			if (admin->LogIn(FileManager::GetAdminPath()) == true)
			{
				admin->GetInfoFromFile(admin->GetFullName());
				WorkAsAdmin(*admin);
			}
			break;
		}
		case 3:
		{
			shared_ptr<Courier> courier = make_shared<Courier>();
			if (courier->LogIn(FileManager::GetCourierPath()) == true)
			{
				courier->GetInfoFromFile(courier->GetFullName());
				WorkAsCourier(*courier);
			}
			break;
		}
		case 4:
		{
			Client client;
			client.SignUp(FileManager::GetClientPath());
			WorkAsClient(client);
			break;
		}
		case 5:
		{
			Admin admin;
			admin.SignUp(FileManager::GetAdminPath());

			WorkAsAdmin(admin);
			break;
		}
		case 6:
		{
			Courier courier;
			courier.SignUp(FileManager::GetCourierPath());
			WorkAsCourier(courier);
			break;
		}
		case 7:
			exit = true;
			break;
		default:
			break;
		}
		system("cls");
	}
}

void MakingChoice::WorkAsClient(Client& client)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		client.ShowBalance();
		MenuManager::ShowClientMenu();
		choice = MakeAChoice(5);
		switch (choice)
		{
		case 1:
		{
			client.CreateMessage(postalOffice);
			break;
		}
		case 2:
		{
			client.MakeADeposit();
			break;
		}
		case 3:
		{
			client.PayForMessage(postalOffice);
			break;
		}
		case 4:
		{
			client.ShowHistory();
			break;
		}
		case 5:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
		TabtoContinue();
		system("cls");
	}
	postalOffice.PutInfoIntoFile();
}

void MakingChoice::WorkAsAdmin(Admin& admin)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		MenuManager::ShowAdminMenu();
		choice = MakeAChoice(5);
		switch (choice)
		{
		case 1:
		{
			admin.ServeMessage(postalOffice);
			break;
		}
		case 2:
		{
			admin.EditMessage(postalOffice);
			break;
		}
		case 3:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
		TabtoContinue();
		system("cls");
	}
	postalOffice.PutInfoIntoFile();
}

void MakingChoice::WorkAsCourier(Courier& courier)
{
	int choice;
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		
		MenuManager::ShowCourierMenu();
		choice = MakeAChoice(4);
		switch (choice)
		{
		case 1:
		{
			courier.ShowMessages();
			break;
		}
		case 2:
		{
			courier.ServeMessage(postalOffice);
			break;
		}
		case 3:
			exit = true;
			break;
		default:
			break;
		}
		TabtoContinue();
		system("cls");
	}
}
