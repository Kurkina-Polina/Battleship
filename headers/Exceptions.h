#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class NoAbilities : public std::exception {
private:
	mutable std::string msg;  
public:
	NoAbilities(){}
	const char* what() const noexcept;

};
class InvalidLen : public std::exception {
private:
	int len;
	mutable std::string msg;  
public:
	InvalidLen(int len_);
	const char* what() const noexcept;

};

class OutofField : public std::exception {
private:
	int x;
	int y;
	mutable std::string msg;  
public:
	OutofField(int x, int y);
	const char* what() const noexcept ;
	
};

class ShipOutofbyX : public std::exception {
	int x;
	int y;
	mutable std::string msg;  
public:
	ShipOutofbyX(int x, int y);
	const char* what() const noexcept;
};

class ShipOutofbyY : public std::exception {
	int x;
	int y;
	mutable std::string msg;  
public:
	ShipOutofbyY(int x, int y);
	const char* what() const noexcept;
	
};

class IntersectShip : public std::exception {
	int x;
	int y;
	mutable std::string msg;  
public:
	IntersectShip(int x, int y);
	const char* what() const noexcept;
};

class EmptyCell : public std::exception {
	int x;
	int y;
	mutable std::string msg;  
public:
	EmptyCell(int x, int y);
	const char* what() const noexcept;
};

class GameException : public std::runtime_error {
public:
	explicit GameException(const std::string& message)
		: std::runtime_error(message) {}
};

class FileError : public std::runtime_error
{
public:
	FileError(const std::string& msg) : std::runtime_error(msg) {}
};

class InputError : public std::runtime_error
{
public:
	InputError(const std::string& msg) : std::runtime_error(msg) {}
};


#endif