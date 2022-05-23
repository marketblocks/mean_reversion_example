#include "mean_reversion.h"
#include "common/utils/containerutils.h"
#include "common/utils/financeutils.h"

double mean_reversion_data::get_current_mean(const mb::tradable_pair& pair) const
{
	auto it = _averagePrices.find(pair);
	if (it != _averagePrices.end())
	{
		return it->second.mean();
	}

	return 0.0;
}

void mean_reversion_data::update_mean(const mb::tradable_pair& pair, double price)
{
	_averagePrices[pair].add_value(price);
}

void mean_reversion_data::set_open_position(const mb::tradable_pair& pair, mb::trade_description trade)
{
	_openPositions.emplace(pair, std::move(trade));
}

bool mean_reversion_data::has_open_position(const mb::tradable_pair& pair) const
{
	return _openPositions.contains(pair);
}

const mb::trade_description& mean_reversion_data::get_open_trade_description(const mb::tradable_pair& pair) const
{
	return _openPositions.at(pair);
}

void mean_reversion_data::set_close_position(const mb::tradable_pair& pair)
{
	_openPositions.erase(pair);
}

mean_reversion::mean_reversion(mean_reversion_config config)
	: _exchanges{}, _meanReversionData{}, _config{ std::move(config) }
{}

void mean_reversion::initialise(std::vector<std::shared_ptr<mb::exchange>> exchanges)
{
	_exchanges = std::move(exchanges);

	_meanReversionData.reserve(_exchanges.size());

	for (auto exchange : _exchanges)
	{
		_meanReversionData.emplace(exchange->id(), mean_reversion_data{});
	}
}

void mean_reversion::run_iteration()
{
	for (auto exchange : _exchanges)
	{
		mean_reversion_data& meanReversionData = _meanReversionData.find(exchange->id())->second;

		for (auto& pair : _config.tradable_pairs())
		{
			double price = exchange->get_price(pair);
			double mean = meanReversionData.get_current_mean(pair);

			if (meanReversionData.has_open_position(pair))
			{
				const mb::trade_description& openPosition = meanReversionData.get_open_trade_description(pair);

				if (price >= mean && price > openPosition.asset_price())
				{
					mb::trade_description trade{ mb::order_type::MARKET, pair, mb::trade_action::SELL, price, openPosition.volume() };
					exchange->add_order(trade);
					meanReversionData.set_close_position(pair);
				}
			}
			else
			{
				if (price <= mean * _config.trade_price_threshold())
				{
					double availableBalance = mb::find_or_default(exchange->get_balances(), pair.price_unit(), 0.0);
					double volume = mb::calculate_volume(price, availableBalance * _config.balance_traded());
					mb::trade_description trade{ mb::order_type::MARKET, pair, mb::trade_action::BUY, price, volume };
					exchange->add_order(trade);
					meanReversionData.set_open_position(pair, std::move(trade));
				}
			}

			meanReversionData.update_mean(pair, price);
		}
	}
}