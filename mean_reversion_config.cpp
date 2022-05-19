#include "mean_reversion_config.h"
#include "common/utils/containerutils.h"

namespace
{
	namespace json_property_names
	{
		static constexpr std::string_view TRADABLE_PAIRS = "tradablePairs";
		static constexpr std::string_view TRADE_PRICE_THRESHOLD = "tradePriceThreshold";
		static constexpr std::string_view BALANCE_TRADED = "balanceTraded";
	}
}

mean_reversion_config::mean_reversion_config()
	: _tradablePairs{}, _tradePriceThreshold{ 0.0 }, _balanceTraded{ 0.0 }
{}

mean_reversion_config::mean_reversion_config(
	std::vector<mb::tradable_pair> tradablePairs,
	double tradePriceThreshold,
	double balanceTraded)
	:
	_tradablePairs{ std::move(tradablePairs) },
	_tradePriceThreshold{ tradePriceThreshold },
	_balanceTraded{ balanceTraded }
{}

template<>
mean_reversion_config mb::from_json(const mb::json_document& json)
{
	return mean_reversion_config
	{
		mb::parse_tradable_pairs(json.get<std::vector<std::string>>(json_property_names::TRADABLE_PAIRS)),
		json.get<double>(json_property_names::TRADE_PRICE_THRESHOLD),
		json.get<double>(json_property_names::BALANCE_TRADED)
	};
}

template<>
void mb::to_json(const mean_reversion_config& config, mb::json_writer& writer)
{
	std::vector<std::string> tradablePairNames = mb::to_vector<std::string>(config.tradable_pairs(), [](const mb::tradable_pair& pair)
		{
			return pair.to_string('/');
		});

	writer.add(json_property_names::TRADABLE_PAIRS, std::move(tradablePairNames));
	writer.add(json_property_names::TRADE_PRICE_THRESHOLD, config.trade_price_threshold());
	writer.add(json_property_names::BALANCE_TRADED, config.balance_traded());
}