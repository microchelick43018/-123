#pragma once
#include <list>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include "Message.h"
#include "InputChecker.h"
#include "FileManager.h"
#include "TypesWorker.h"
using namespace std;

class PostalOffice
{
private:
	vector<Message> _messages;
public:
	PostalOffice();

	~PostalOffice();

	void AddMessage(Message& newMessage);

	Message& GetMessage(int number);

	Message& GetMessage(const Message& mess);

	int GetMessagesCount();

	void PutInfoIntoFile();

	void RemoveMessage(int number);

	void RemoveMessage(const Message& messageToDelete);

	void ShowMessages();
};

