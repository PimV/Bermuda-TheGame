#pragma once
class NPCFactory
{
private:
	static NPCFactory npcFactory;

public:
	NPCFactory();
	~NPCFactory();
	static NPCFactory* Instance() {
		return &npcFactory;
	};
};

