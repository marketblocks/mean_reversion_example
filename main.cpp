#include "runner/runner.h"
#include "logging/logger.h"
#include "strategy.h"

int main()
{
	// Create runner for strategy
	mb::runner<strategy> runner = mb::create_runner<strategy>();

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