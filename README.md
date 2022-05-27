# Mean Reversion Example

This example features a very basic strategy that is used to demonstrate the back testing framework of marketblocks. It also features a custom config file and illustrates how they are easily and effortlessly integrated into the pipeline. 

Also note how the strategy is written completely independently from any back testing logic. This allows the strategy to go live just by changing the run mode variable in the runner.json config file (see more below).

### Reading the Code
The core algorithm is contained within `mean_reversion.cpp`. 

See `mean_reversion::run_iteration()` for the active stage of the strategy.

All marketblocks types and functions are located within the `mb` namespace.

### Running the Example Build

An example build has been provided in the `build` folder. Simply run `mean_reversion_example.exe` to begin running this example with the default configuration. 

The default run mode is back_test. This will run the strategy against historical data (included for BTC/USD) and output two files:
  1. report.txt (A summary indicating various parameters such as start/end times, total trades and final balances)

![image](https://user-images.githubusercontent.com/43093246/169858193-c9450f17-0256-4da0-b76b-f4d8812e4660.png)



  2. trades.csv (A list of all simulated trades)


![image](https://user-images.githubusercontent.com/43093246/169858302-26091073-1441-4c01-8cfc-c283ee992dd4.png)



As well as printing the contents of report.txt to the console window.


![image](https://user-images.githubusercontent.com/43093246/169858562-38b3065e-de1a-4d6d-808c-1c1d4326b64b.png)


Various parameters may be adjusted through the config files located inside the `configs` folder. All config files are JSON encoded.

<details><summary>mean_reversion.json - Custom config specific to this example</summary>
  
- `balanceTraded` - Specifies percentage of balance to use when executing trades (a value of 1.0 uses the entire available balance)
- `tradablePairs` - Specifies the pairs to run the asset against (Note: if running back test, additional data must be supplied to change this setting from "BTC/USD")
- `tradePriceThreshold` - Specifies how far below the mean the price must fall to trigger a trade
  
</details>

<details><summary>back_testing.json</summary>
  
- `dataDirectory` - Path to historical data
- `outputDirectory` - Path to save results
- `startTime` - Data start time specified as seconds from epoch
- `endTime` - Data end time specified as seconds from epoch
- `stepSize` - Data interval in seconds
- `dynamicDataLoading` - Flag to indicate whether to dynamically load historical data
  
</details>

<details><summary>runner.json</summary>

- `exchangeIds` - Specifies which exchanges to run the strategy on. Specifying an empty array will use all supported exchanges.
- `httpTimeout` - Specifies the timeout for HTTP requests in ms. A value of 0 disables the timeout.
- `runMode` - Sets the run mode. Valid options are `"live"`, `"live_test"` or `"back_test"`
- `websocketTimeout` - Specifies the timeout for the websocket connection handshake in ms. A value of 0 disables the timeout.
  
</details>

<details><summary>paper_trading.json</summary>
  
Contains parameters used by the trading simulator when the Live-Test run mode is enabled
  
  - `balances` - Initial virtual balances
  - `fee` - Simulated fee to use when executing paper trades
  
</details>

