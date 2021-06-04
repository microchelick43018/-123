#pragma once
#include "User.h"
#include "Message.h"
#include "Client.h"
#include "PostalOffice.h"
#include <iomanip>
#include <vector>
class Courier : public User
{
private:
	vector<Message> _messages;
public:

	Courier();

	~Courier();

	void AddMessage(const Message& newMessage);

	Message& getMessage(const Message& messageToGet);

	void GetInfoFromFile(string fullName);

	void PutInfoIntoFile();

	void RemoveMessage(const Message& messageToDelete);

	void ServeMessage(PostalOffice& office);

	void ShowMessages();
};

