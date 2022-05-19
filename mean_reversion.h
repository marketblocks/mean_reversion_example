#pragma once

#include "mean_reversion_config.h"
#include "exchanges/exchange.h"
#include "common/utils/mathutils.h"

class mean_reversion_data
{
private:
	std::unordered_map<mb::tradable_pair, mb::mean_calculator<double>> _averagePrices;
	std::unordered_map<mb::tradable_pair, mb::trade_description> _openPositions;

public:
	double get_current_mean(const mb::tradable_pair& pair) const;
	void update_mean(const mb::tradable_pair& pair, double price);

	void set_open_position(const mb::tradable_pair& pair, mb::trade_description trade);
	bool has_open_position(const mb::tradable_pair& pair) const;
	const mb::trade_description& get_open_trade_description(const mb::tradable_pair& pair) const;
	void close_position(const mb::tradable_pair& pair);
};

class mean_reversion
{
private:
	std::vector<std::shared_ptr<mb::exchange>> _exchanges;
	mb::unordered_string_map<mean_reversion_data> _meanReversionData;
	mean_reversion_config _config;
	
public:
	mean_reversion(mean_reversion_config config);

	void initialise(std::vector<std::shared_ptr<mb::exchange>> exchanges);
	void run_iteration();
};