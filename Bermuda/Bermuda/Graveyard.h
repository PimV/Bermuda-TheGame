#pragma once
#include <vector>

struct GraveyardEntry
{
	std::string character;
	int daysSurvived;
	int dayDied;
	int monthDied;
	int yearDied;
};

class Graveyard
{
private:
	//variables
	std::vector<GraveyardEntry*> graveyard;

	//methodes
	void loadGraveyard();
	void saveGraveyard();
	static bool CompareEntries(const GraveyardEntry* left, const GraveyardEntry* right);

public:
	//methodes
	void addToGraveyard(GraveyardEntry*);
	std::vector<GraveyardEntry*> getAllEntries();

	Graveyard();
	virtual ~Graveyard();
};
