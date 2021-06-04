#pragma once
#include "User.h"
#include "PostalOffice.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include "Message.h"
#include "PostalOffice.h"
using namespace std;
class Client : public User
{
private:
	int _balance;
	list<Message> _incomingMessages;
	list<Message> _outgoingMessages;

	void SortMessagesBySenderName(list<Message>& _messages);
	void SortMessagesByStatus(list<Message>& _messages);
	void FilterMessagesByStatus(list<Message>& _messages, bool forReciever);
	void FindMessagesByAdress(list<Message>& _messages, string adress);
public:
	Client();

	Client(const Client& obj);

	~Client();
	
	void AddIncomingMessage(Message& mess);

	void AddOutgoingMessage(Message& mess);

	void CreateMessage(PostalOffice& office);

	Message& GetOutgoingMessage(Message messToFind);

	void GetInfoFromFile(string fullName) override;

	void PutInfoIntoFile() override;

	void MakeADeposit();

	void ShowBalance();

	int GetBalance();

	void PayForMessage(PostalOffice& office);

	void SetBalance(int newBalance);

	void ShowIncomingMessages();

	void ShowHistory();

	void ShowOutgoingMessages();
};

