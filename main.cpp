#include "runner/runner.h"
#include "logging/logger.h"
#include "mean_reversion.h"

int main()
{
	// Create runner for strategy
	mb::runner<mean_reversion> runner = mb::create_runner<mean_reversion>();

	try
	{
		// Start initialisation phase
		runner.initialise();

		// Begin running strategy
		runner.run();
	}
	catch (const std::exception& e)
	{
		mb::logger::instance().critical(e.what());
	}

	return 0;
}