#pragma once

// Abstract class for different controller implementations
class Controller
{
public:
	Controller() = default;
	virtual ~Controller() = default;

	virtual void Update() const = 0;
};


