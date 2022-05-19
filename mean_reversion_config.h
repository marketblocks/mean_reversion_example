#pragma once

#include <vector>

#include "trading/tradable_pair.h"
#include "common/json/json.h"

class mean_reversion_config
{
private:
	std::vector<mb::tradable_pair> _tradablePairs;
	double _tradePriceThreshold;
	double _balanceTraded;

public:
	mean_reversion_config();

	mean_reversion_config(
		std::vector<mb::tradable_pair> tradablePairs,
		double tradePriceThreshold,
		double balanceTraded);

	static constexpr std::string name() noexcept { return "mean_reversion"; }

	const std::vector<mb::tradable_pair>& tradable_pairs() const noexcept { return _tradablePairs; };
	double trade_price_threshold() const noexcept { return _tradePriceThreshold; }
	double balance_traded() const noexcept { return _balanceTraded; }
};

template<>
mean_reversion_config mb::from_json(const mb::json_document& json);

template<>
void mb::to_json(const mean_reversion_config& config, mb::json_writer& writer);