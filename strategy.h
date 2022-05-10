#pragma once

#include "exchanges/exchange.h"

class strategy
{
public:
	void initialise(std::vector<std::shared_ptr<mb::exchange>> exchanges);
	void run_iteration();
};