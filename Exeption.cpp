#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.h"


const char* NoAbilities::what() const noexcept {
	msg = "No abilities available. \n\0";
	return msg.c_str();
}

InvalidLen::InvalidLen(int len) : len(len) {}
const char* InvalidLen::what() const noexcept {
	msg = "Len of ship should be between 1 and 4. Your len: " + std::to_string(len) + ". Please Type new len for ship: \n\0";
	return msg.c_str();
}

OutofField::OutofField(int x, int y) : x(x), y(y) {}
const char* OutofField::what() const noexcept {
	msg = "The coordinates out of field: " + std::to_string(x) + ", " + std::to_string(y) + ". Please Type new coordinates: \n\0";
	return msg.c_str();
}



ShipOutofbyX::ShipOutofbyX(int x, int y) : x(x), y(y) {}
const char* ShipOutofbyX::what() const noexcept {
	msg = "invalid coordinate x (ship out of field) " + std::to_string(x) + ", " + std::to_string(y) + ". Please type new x coordinate: \n\0";
	return msg.c_str();
}



ShipOutofbyY::ShipOutofbyY(int x, int y) : x(x), y(y) {}
const char* ShipOutofbyY::what() const noexcept {
	msg = "invalid coordinate y (ship out of field) " + std::to_string(x) + ", " + std::to_string(y) + ". Please type new y coordinate: \n\0";
	return msg.c_str();
}



IntersectShip::IntersectShip(int x, int y) : x(x), y(y) {}
const char* IntersectShip::what() const noexcept {
	msg = "There is a ship " + std::to_string(x) + ", " + std::to_string(y) + ". You need to place a ship in empty ceils. Please type new coordinates: \n\0";
	return msg.c_str();
}



EmptyCell::EmptyCell(int x, int y) : x(x), y(y) {}
const char* EmptyCell::what() const noexcept {
	msg = "invalid coorditaties (its empty) " + std::to_string(x) + ", " + std::to_string(y) + ". Please type new coordinates: \n\0";
	return msg.c_str();
}
