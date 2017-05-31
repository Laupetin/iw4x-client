#pragma once

namespace Components
{
	class Theatre : public Component
	{
	public:
		Theatre();

		static void StopRecording();

	private:
		class DemoInfo
		{
		public:
			std::string name;
			std::string mapname;
			std::string gametype;
			std::string author;
			int length;
			std::time_t timeStamp;

			json11::Json to_json() const
			{
				return json11::Json::object
				{
					{ "mapname", mapname },
					{ "gametype", gametype },
					{ "author", author },
					{ "length", length },
					{ "timestamp", Utils::String::VA("%lld", timeStamp) } //Ugly, but prevents information loss
				};
			}
		};

		static DemoInfo CurrentInfo;
		static unsigned int CurrentSelection;
		static std::vector<DemoInfo> Demos;

		static char BaselineSnapshot[131072];
		static int BaselineSnapshotMsgLen;
		static int BaselineSnapshotMsgOff;

		static void WriteBaseline();
		static void StoreBaseline(PBYTE snapshotMsg);

		static void LoadDemos(UIScript::Token);
		static void DeleteDemo(UIScript::Token);
		static void PlayDemo(UIScript::Token);

		static unsigned int GetDemoCount();
		static const char* GetDemoText(unsigned int item, int column);
		static void SelectDemo(unsigned int index);

		static void GamestateWriteStub(Game::msg_t* msg, char byte);
		static void RecordGamestateStub();
		static void BaselineStoreStub();
		static void BaselineToFileStub();
		static void AdjustTimeDeltaStub();
		static void ServerTimedOutStub();
		static void UISetActiveMenuStub();

		static uint32_t InitCGameStub();
		static void MapChangeStub();
		static void MapChangeSVStub(char* a1, char* a2);

		static void RecordStub(int channel, char* message, char* file);
		static void StopRecordStub(int channel, char* message);
	};
}
