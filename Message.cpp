#include "Message.h"

Message::Message()
{
	_senderName[0] = '\0';
	_courierName[0] = '\0';
	_recieverName[0] = '\0';
	_recieverAdress[0] = '\0';
	_status = 0;
	_priorety = 1;
}

Message::Message(string text, string senderName, string recieverName, string recieverAdress, bool isPayed, int priorety, int status)
{
	Set(text, senderName, recieverName, recieverAdress, isPayed, priorety, status);
}

void Message::GetInfoFromFile(fstream& fs)
{
	fs.read((char*)&_courierName, sizeof(char) * 100);
	fs.read((char*)&_senderName, sizeof(char) * 100);
	fs.read((char*)&_recieverName, sizeof(char) * 100);
	fs.read((char*)&_text, sizeof(char) * 300);
	fs.read((char*)&_recieverAdress, sizeof(char) * 50);
	fs.read((char*)&_isPayed, sizeof(bool));
	fs.read((char*)&_priorety, sizeof(int));
	fs.read((char*)&_status, sizeof(int));
}

bool& Message::GetPayed()
{
	return _isPayed;
}

string Message::GetReciverAdress()
{
	return ConvertMasCharToString(_recieverName);
}

string Message::GetReciverName()
{
	return ConvertMasCharToString(_recieverName);
}

string Message::GetSenderName()
{
	return ConvertMasCharToString(_senderName);
}

string Message::GetCourierName()
{
	return ConvertMasCharToString(_courierName);
}

int Message::GetStatus()
{
	return _status;
}

void Message::PutInfoIntoFile(fstream& fs)
{
	fs.write((char*)&_courierName, sizeof(char) * 100);
	fs.write((char*)&_senderName, sizeof(char) * 100);
	fs.write((char*)&_recieverName, sizeof(char) * 100);
	fs.write((char*)&_text, sizeof(char) * 300);
	fs.write((char*)&_recieverAdress, sizeof(char) * 50);
	fs.write((char*)&_isPayed, sizeof(bool));
	fs.write((char*)&_priorety, sizeof(int));
	fs.write((char*)&_status, sizeof(int));
}

void Message::Set(string text, string senderName, string recieverName, string recieverAdress, bool isPayed, int priorety, int status)
{
	ConvertStringToMasChar(text, _text);
	ConvertStringToMasChar(senderName, _senderName);
	ConvertStringToMasChar(recieverName, _recieverName);
	ConvertStringToMasChar(recieverAdress, _recieverAdress);
	_isPayed = isPayed;
	_priorety = priorety;
	_status = status;
}

void Message::SetStatus(int newStatus)
{
	_status = newStatus;
}

void Message::SetCourierName(string name)
{
	ConvertStringToMasChar(name, _courierName);
}

void Message::ShowInfo(bool forReciver)
{
	/*			cout << setw(6) << "№";
			cout << setw(15) << "От кого";
			cout << setw(15) << "Кому";
			cout << setw(22) << "Адрес получателя";
			cout << setw(15) << "Приоритет";
			cout << setw(14) << "Статус";
			cout << setw(14) << "Оплачен" << endl;*/
	string s;
	s = ConvertMasCharToString(_senderName);
	string out = s; FillSpaces(out, 15 - s.size());

	s = ConvertMasCharToString(_recieverName);
	out += s; FillSpaces(out, 15 - s.size());

	s = ConvertMasCharToString(_recieverAdress);
	out += s; FillSpaces(out, 22 - s.size());

	s = to_string(_priorety);
	out += s; FillSpaces(out, 15 - s.size());

	if (forReciver == false)
	{
		if (_status == 0)
		{
			s = "В обработке";
		}
		else if (_status == 1)
		{
			s = "У курьера";
		}
		else if (_status == 2)
		{
			s = "Доставлен";
		}
		out += s;
		FillSpaces(out, 14 - s.size());
		if (_isPayed == true)
		{
			s = "Оплачен";
		}
		else
		{
			s = "Не оплачен";
		}
		out += s;
		FillSpaces(out, 14 - s.size());
	}
	cout << out << endl;
}

void Message::ShowInfoForAdmin()
{
	//cout << setw(6) << "№";
	//cout << setw(15) << "От кого";
	//cout << setw(15) << "Кому";
	//cout << setw(22) << "Адрес получателя";
	//cout << setw(15) << "Приоритет";
	//cout << setw(14) << "Статус";
	//cout << setw(14) << "Оплачен" << endl;
	string s;
	s = ConvertMasCharToString(_senderName);
	string out = s; FillSpaces(out, 15 - s.size());

	s = ConvertMasCharToString(_recieverName);
	out += s; FillSpaces(out, 15 - s.size());

	s = ConvertMasCharToString(_recieverAdress);
	out += s; FillSpaces(out, 22 - s.size());

	s = to_string(_priorety);
	out += s; FillSpaces(out, 15 - s.size());


	if (_status == 0)
	{
		s = "В обработке";
	}
	else if (_status == 1)
	{
		s = "У курьера";
	}
	else if (_status == 2)
	{
		s = "Доставлен";
	}
	out += s;
	FillSpaces(out, 14 - s.size());
	if (_isPayed == true)
	{
		s = "Оплачен";
	}
	else
	{
		s = "Не оплачен";
	}
	out += s;
	FillSpaces(out, 14 - s.size());

	s = ConvertMasCharToString(_courierName);
	out += s;
	FillSpaces(out, 17 - s.size());

	cout << out << endl;
}

void Message::ShowText()
{
	cout << "Текст: " << endl;
	WriteMasChar(_text);
	cout << endl;
}

bool operator==(const Message& m1, const Message& m2)
{
	bool b1 = StrCmp1(m1._text, m2._text) == 0;
	bool b2 = StrCmp1(m1._senderName, m2._senderName) == 0;
	bool b3 = StrCmp1(m1._recieverName, m2._recieverName) == 0;
	bool b4 = StrCmp1(m1._recieverAdress, m2._recieverAdress) == 0;
	bool b5 = m1._isPayed == m2._isPayed;
	bool b6 = m1._priorety == m2._priorety;
	bool b7 = m1._status == m2._status;
	bool b8 = StrCmp1(m1._courierName, m2._courierName) == 0;
	return b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8;
}
