#pragma once
#include <string>
#include <fstream>
#include "InputChecker.h"
#include "TypesWorker.h"
using namespace std;
class Message
{
private:
	char _courierName[100];
	char _text[300];
	char _senderName[100];
	char _recieverName[100];
	char _recieverAdress[50];
	bool _isPayed;
	int _priorety;
	int _status;
public:
	Message();

	Message(string text, string senderName, string recieverName, string recieverAdress, bool isPayed, int priorety, int status);

	void GetInfoFromFile(fstream& fs);

	bool& GetPayed();

	string GetReciverAdress();

	string GetReciverName();

	string GetSenderName();

	string GetCourierName();

	int GetStatus();

	void PutInfoIntoFile(fstream& fs);

	void Set(string text, string senderName, string recieverName, string recieverAdress, bool isPayed, int priorety, int status);

	void SetStatus(int newStatus);

	void SetCourierName(string name);

	void ShowInfo(bool forReciver);

	void ShowInfoForAdmin();

	void ShowText();

	friend bool operator==(const Message& m1, const Message& m2);
};

