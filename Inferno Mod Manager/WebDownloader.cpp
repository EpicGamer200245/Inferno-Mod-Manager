﻿#include "WebDownloader.h"

#include <iostream>
#include <string>

namespace InfernoModManager {
	System::Collections::Generic::List<System::String^>^ WebDownloader::getAllData()
	{
		System::Collections::Generic::List<System::String^>^ compList = gcnew System::Collections::Generic::List<System::String^>();
		System::Net::WebClient^ web = gcnew System::Net::WebClient();
		web->Headers->Add("user-agent", "Inferno Mod Manager");
		for each (System::String ^ address in WebDownloader::Repos)
		{
			try {
				System::String^ data = web->DownloadString(address);
				data->Replace("\r", "");
				for each (System::String ^ section in data->Split('\n'))
				{
					compList->Add(section);
				}
			}
			catch (System::Exception^ e)
			{
				System::IO::File::AppendAllText("logg.log", "Error caught on line 24 " + e->Message);
			}
		}
		AllData = compList;
		delete compList;

		return AllData;
	}

	void  WebDownloader::ifBlankSet()
	{
		if (!WebDownloader::Repos || WebDownloader::Repos->Count == 0) {
			WebDownloader::Repos = gcnew System::Collections::Generic::List<System::String^>;
			WebDownloader::Repos->Add("https://raw.githubusercontent.com/Inferno-Dev-Team/Inferno-Mod-Manager/main/git.yo");
		}
		if (!WebDownloader::AllData || WebDownloader::AllData->Count == 0)
			WebDownloader::AllData = gcnew System::Collections::Generic::List<System::String^>;
	}

	void WebDownloader::downloadFile(System::String^ fileloc, System::String^ filename)
	{
		System::Net::WebClient^ web = gcnew System::Net::WebClient();
		web->Headers->Add("user-agent", "Inferno Mod Manager");
		web->DownloadFile(fileloc, filename);
		delete web;
	}

}
