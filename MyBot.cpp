#include "MyBot.h"
#include <dpp/dpp.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

const std::string    BOT_TOKEN    = "token";
using namespace std;


void saveBuilds(const vector<string>& builds, const string& buildsFile) {
	ofstream file(buildsFile); //open file
	if (file.is_open()) {
		for (const string& build : builds)
			file << build << endl;
		file.close();
		cout << "Builds were saved" << endl;
	}
	else cout << "File wasn't open" << endl;
}
vector<string> loadBuilds(const string& fileName) {
	vector<string> builds;
	ifstream file(fileName);

	if (file.is_open()) {
		string build;
		while (getline(file, build))
			builds.push_back(build);

		file.close();
		cout << "File's were loaded" << endl;
	}
	else cout << "File wasn't open" << endl;
}

string randHero(vector<string> list) {
	srand(time(NULL));
	int rnd = rand() % list.size();
	string res = list[rnd];

	return res;
}

string heroList() {
	string heroes = "Abaddon Alchemist AncientApparition AntiMage ArcWarden Axe Bane Batrider Beastmaster Bloodseeker BountyHunter Brewmaster Bristleback Broodmother CentaurWarrunner ChaosKnight Chen Clinkz Clockwerk CrystalMaiden DarkSeer DarkWillow Dawnbreaker Dazzle DeathProphet Disruptor Doom DragonKnight DrowRanger EarthSpirit Earthshaker ElderTitan EmberSpirit Enchantress Enigma FacelessVoid Grimstroke Gyrocopter Hoodwink Huskar Invoker Io Jakiro Juggernaut KeeperoftheLight Kunkka LegionCommander Leshrac Lich Lifestealer Lina Lion LoneDruid Luna Lycan Magnus Marci Mars Medusa Meepo Mirana MonkeyKing Morphling Muerta NagaSiren NaturesProphet Necrophos NightStalker NyxAssassin OgreMagi Omniknight Oracle OutworldDestroyer Pangolier PhantomAssassin PhantomLancer Phoenix PrimalBeast Puck Pudge Pugna QueenofPainRazor Riki Rubick SandKing ShadowDemon ShadowFiend ShadowShaman Silencer SkywrathMage Slardar Slark Snapfire Sniper Spectre SpiritBreaker StormSpirit Sven Techies TemplarAssassin Terrorblade Tidehunter Timbersaw Tinker Tiny TreantProtector TrollWarlord Tusk Underlord Undying Ursa VengefulSpirit Venomancer Viper Visage VoidSpirit Warlock Weaver Windranger WinterWyvern WitchDoctor WraithKing Zeus";

	 //add heroes to vector
	vector<string> list;
 	istringstream iss(heroes);
	string word;

	for (; iss >> word; )
		list.push_back(word);

	// rand hero
	return randHero(list);
}
string heroBuild() {
	string fileName = "builds.txt";
	vector<string> builds = loadBuilds(fileName);

	return randHero(builds);
}

	int main()
	{
		dpp::cluster bot(BOT_TOKEN);
		bot.on_log(dpp::utility::cout_logger());

		bot.on_slashcommand([](const dpp::slashcommand_t& event) {
			if (event.command.get_command_name() == "hero") {
				event.reply(heroList());
				cout << "hero is runnig";
			}
			if (event.command.get_command_name() == "build") {
				event.reply(heroBuild());
			}
		});

		bot.on_ready([&bot](const dpp::ready_t& event) {
			if (dpp::run_once<struct register_bot_commands>()) {
				bot.global_command_create(dpp::slashcommand("hero", "randomHero", bot.me.id));
				bot.global_command_create(dpp::slashcommand("build", "randomBuild", bot.me.id));
			}
		});

		/* Start the bot */
		bot.start(dpp::st_wait);

		return 0;
	}
