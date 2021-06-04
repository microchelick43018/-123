#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <direct.h>
#include <fstream>
using namespace std;
using namespace std::experimental::filesystem;
class FileManager
{
private:
	static const string ADMIN_PATH;
	static const string CLIENT_PATH;
	static const string OFFICE_PATH;
	static const string COURIER_PATH;
public:
	static string GetAdminPath();

	static string GetClientPath();

	static string GetTablesPath();

	static string GetStorePath();

	static string GetCourierPath();

	static void CreateAdminsDir();

	static void CreateClientsDir();

	static void CreateCourierDir();

	static void GetVectorOfCouriers(vector<string>& names);
};