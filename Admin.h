#pragma once
#include "User.h"
#include <fstream>
#include "PostalOffice.h"
#include "Courier.h"
#include "Client.h"
class Admin : public User
{
private:

public:
	Admin();

	~Admin();

	void ServeMessage(PostalOffice& office);

	void EditMessage(PostalOffice& office);

	void GetInfoFromFile(string fullName) override;

	void PutInfoIntoFile() override;
};
