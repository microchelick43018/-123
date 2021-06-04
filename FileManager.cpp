#include "FileManager.h"
const string FileManager::CLIENT_PATH = "Clients/";
const string FileManager::ADMIN_PATH = "Admins/";
const string FileManager::COURIER_PATH = "Couriers/";
const string FileManager::OFFICE_PATH = "PostaOffice";

string FileManager::GetAdminPath()
{
	return ADMIN_PATH;
}

string FileManager::GetClientPath()
{
	return CLIENT_PATH;
}

string FileManager::GetTablesPath()
{
	return COURIER_PATH;
}

string FileManager::GetStorePath()
{
	return OFFICE_PATH;
}

string FileManager::GetCourierPath()
{
	return COURIER_PATH;
}

void FileManager::GetVectorOfCouriers(vector<string>& names)
{
	string path = COURIER_PATH;
	for (auto& name : directory_iterator(path))
	{
		names.push_back(name.path().stem().string());
	}
	if (names.size() == 0)
	{
		return;
	}
	if (*names.begin() == "")
	{
		names.erase(names.begin());
	}
}

void FileManager::CreateAdminsDir()
{
	if (exists(ADMIN_PATH) == false)
	{
		create_directory(ADMIN_PATH);
	}
}

void FileManager::CreateClientsDir()
{
	if (exists(CLIENT_PATH) == false)
	{
		create_directory(CLIENT_PATH);
	}
}

void FileManager::CreateCourierDir()
{
	if (exists(COURIER_PATH) == false)
	{
		create_directory(COURIER_PATH);
	}
}