#pragma once

#include "exchanges/exchange.h"
#include "common/utils/mathutils.h"

class mean_reversion_data
{
private:
	std::shared_ptr<mb::exchange> _exchange;
	std::vector<mb::tradable_pair> _tradablePairs;
	std::unordered_map<mb::tradable_pair, mb::mean_calculator<double>> _averagePrices;
	std::unordered_map<mb::tradable_pair, bool> _openPositions;

public:
	mean_reversion_data(std::shared_ptr<mb::exchange> exchange);

	std::shared_ptr<mb::exchange> exchange() const noexcept { return _exchange; }
	const std::vector<mb::tradable_pair>& tradable_pairs() const noexcept { return _tradablePairs; }

	double get_current_mean(const mb::tradable_pair& pair);
	void update_mean(const mb::tradable_pair& pair, double price);

	void set_open_position(const mb::tradable_pair& pair, bool open);
	bool has_open_position(const mb::tradable_pair& pair);
};

class mean_reversion
{
private:
	std::vector<mean_reversion_data> _meanReversionData;
	
public:
	void initialise(std::vector<std::shared_ptr<mb::exchange>> exchanges);
	void run_iteration();
};