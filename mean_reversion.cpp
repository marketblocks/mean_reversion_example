#include "mean_reversion.h"
#include "common/utils/containerutils.h"

mean_reversion_data::mean_reversion_data(std::shared_ptr<mb::exchange> exchange)
	: _exchange{ exchange }
{
	_tradablePairs = _exchange->get_tradable_pairs();
}

double mean_reversion_data::get_current_mean(const mb::tradable_pair& pair)
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

void mean_reversion_data::set_open_position(const mb::tradable_pair& pair, bool open)
{
	_openPositions[pair] = open;
}

bool mean_reversion_data::has_open_position(const mb::tradable_pair& pair)
{
	auto it = _openPositions.find(pair);
	if (it != _openPositions.end())
	{
		return it->second;
	}

	return false;
}

void mean_reversion::initialise(std::vector<std::shared_ptr<mb::exchange>> exchanges)
{
	_meanReversionData = to_vector<mean_reversion_data>(exchanges, [](std::shared_ptr<mb::exchange> exchange)
		{
			return mean_reversion_data{ exchange };
		});
}

void mean_reversion::run_iteration()
{
	for (auto& meanReversionItem : _meanReversionData)
	{
		for (auto& pair : meanReversionItem.tradable_pairs())
		{
			double mean = meanReversionItem.get_current_mean(pair);
			double price = meanReversionItem.exchange()->get_price(pair);

			if (meanReversionItem.has_open_position(pair))
			{
				if (price >= mean)
				{
					meanReversionItem.exchange()->add_order(mb::trade_description{ mb::order_type::MARKET, pair, mb::trade_action::SELL, price, 1.0 });
					meanReversionItem.set_open_position(pair, false);
				}
			}
			else
			{
				if (price <= mean * 0.97)
				{
					meanReversionItem.exchange()->add_order(mb::trade_description{ mb::order_type::MARKET, pair, mb::trade_action::BUY, price, 1.0 });
					meanReversionItem.set_open_position(pair, true);
				}
			}

			meanReversionItem.update_mean(pair, price);
		}
	}
}