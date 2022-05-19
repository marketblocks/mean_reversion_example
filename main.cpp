#include "runner/runner.h"
#include "logging/logger.h"
#include "mean_reversion.h"

int main()
{
	// Create runner for strategy
	mb::runner<mean_reversion> runner = mb::create_runner<mean_reversion>();

	// Load custom config file
	mean_reversion_config meanReversionConfig = mb::load_or_create_config<mean_reversion_config>();

	// Start initialisation phase
	runner.initialise(std::move(meanReversionConfig));

	// Begin running strategy
	runner.run();

	return 0;
}