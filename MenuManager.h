#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include "InputChecker.h"
#include "FileManager.h"
#include "Client.h"
#include "Admin.h"
#include "Courier.h"
#include "PostalOffice.h"

using namespace std;

extern PostalOffice postalOffice;
namespace MenuManager
{
	void ShowClientMenu();

	void ShowAdminMenu();

	void ShowMainMenu();

	void ShowCourierMenu();
}

namespace MakingChoice
{
	void WorkAsUser();

	void WorkAsClient(Client& client);

	void WorkAsAdmin(Admin& admin);

	void WorkAsCourier(Courier& courier);

	void TabtoContinue();
}

