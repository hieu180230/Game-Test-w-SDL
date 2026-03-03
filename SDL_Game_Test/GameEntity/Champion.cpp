#include "BattleEntity.h"

/* the skill data will be a json as example

{
	"skill_id_1" : ["condition_1", "value_1"],
	"skill_id_2" : ["condition_2", "value_2"],
}

*/

bool Champion::can_use_skill() {
	//get corresponding condition and value
	//switch condition
	//  if time then measure time diff
	//  if on death/on health percentage then check hp
	//  ...
	//  if condition == true return condition
	return true;
}

void Champion::use_skill() {
	//use skill
	//if skill effect is temporary
	skill_available = false;
	//if skill effect is permanent
	return;
}

void Champion::update() {

}