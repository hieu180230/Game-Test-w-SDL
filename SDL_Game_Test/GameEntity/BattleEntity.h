#pragma once
#include <string>
#include <vector>
#include "../Vector2D.h"
#include "../Entity&Component/Entity&Component.h"

class Squad;
class Champion;

class Minion : Component {
private:
	enum MinionStatus {
		IDLE,
		MOVE,
		ATTACK,
	};

	float health;
	float base_damage;
	Vector2D position;
	float base_speed;
	float charge_multiplier;
	weak_ptr<Squad> in_squad;
	MinionStatus status;
	weak_ptr<Minion> enemy;
public:
	Minion() {
		health = 0;
		base_damage = 0;
		position = Vector2D{ 0, 0 };
		base_speed = 1;
		charge_multiplier = 1;
		in_squad = weak_ptr<Squad>();
		status = MinionStatus::IDLE;
		enemy = weak_ptr<Minion>();
	}
	~Minion();

	void rally();
	void find_nearest_enemy();
	void update() override;
};

class Squad : Component {
private:
	enum SquadType {
		INFANTRY,
		ARCHER,
	};

	SquadType minion_type;
	weak_ptr<Champion> champion;
	std::vector<Minion> minions;
	int level;
	int size;

public:
	Squad() {
		minion_type = SquadType::INFANTRY;
		champion = weak_ptr<Champion>();
		minions = std::vector<Minion>();
		level = 1;
		size = 5;
	}
	~Squad();

	void update() override;
};

class Champion : Minion {
private:
	float mana;
	bool skill_available;
	std::string skill_id;
public:
	std::string name;
	Champion() {
		mana = 0;
		skill_available = false;
		name = "holder";
		skill_id = "a";
	}
	~Champion();
	bool can_use_skill();
	void use_skill();
	void update() override;
};
