#include "Abilities.h"
#include "AbilityMananger.h"
#include "Input.h"
#include <vector>
#include <iostream>
#include <random>
#include <tuple>

std::tuple<bool, AbilityStatus>  DoubleHit::apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager){
	abilityManager.SetFlag();
	return {false, AbilityStatus::SUCCESS };
	
}

std::tuple<bool, AbilityStatus> Scanner::apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager){
	std::vector<int> coordinates =abilityManager.GetInput()->inputCoordinates();
	field.ValidCoordinaties(coordinates[0], coordinates[1]);
	
	bool  status1 = field.GetStatus(coordinates[0], coordinates[1]) == CellStatus::Ship;
	bool status2 = false;
	if (coordinates[1] + 1 < field.GetCol()) {
		status2 = field.GetStatus(coordinates[0], coordinates[1] + 1) == CellStatus::Ship;
	}
		
	bool status3 = false;
	if (coordinates[0] + 1 < field.GetRow()) {
		status3 = field.GetStatus(coordinates[0] + 1, coordinates[1]) == CellStatus::Ship;
	}
		
	bool status4 = false;
	if ((coordinates[0] + 1 < field.GetRow()) && (coordinates[1] + 1 < field.GetCol())) {
		status4 = field.GetStatus(coordinates[0] + 1, coordinates[1] + 1) == CellStatus::Ship;
	}
		
	if (status1 || status2 || status3 || status4) {
		return {true, AbilityStatus::SHIP };
	}
	return { false, AbilityStatus::EMPTY };
}



std::tuple<bool, AbilityStatus> Shelling::apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager){
	int countShips = shipManager.GetShipCount();
	srand(time(0));
	int rNum = rand();
	int indexShip = rNum%(countShips);  

	int sizeShip = shipManager.GetShip(indexShip).GetLength();
	int indexSegment = rNum%(sizeShip);  

	while (shipManager.GetShip(indexShip).GetSegment(indexSegment)->GetState() == SegmentState::Destroyed) {
		if (indexSegment + 1 < sizeShip) {
			indexSegment += 1;
		}
		else if (indexShip+1<countShips) {
			indexShip += 1;
			sizeShip = shipManager.GetShip(indexShip).GetLength();
		}
		else {
			indexShip = 0;
			sizeShip = shipManager.GetShip(indexShip).GetLength();
		}

	}
	ShipSegment* segment = shipManager.GetShip(indexShip).GetSegment(indexSegment);
	SegmentState result = segment->Hit();
	if (result == SegmentState::Damaged) {
		return {false, AbilityStatus::NOT_DESTROYED};
	}
	return {true, AbilityStatus::DESTROYED };
	
}
