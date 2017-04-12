// FutureStock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

// FALSE means previous yields better profit, TRUE means current yields better profit
bool determineProfitBetter(int prevBuy, int prevSell, int currBuy, int currSell, int budget)
{
   int prevStock(0), currStock(0);
   // Use 1:1 if budget is not input
   if (budget == 0) {
      prevStock = 1;
      currStock = 1;
   }
   // Calculate the number of shares purchasable given a budget
   else {
      prevStock = budget / prevBuy;
      currStock = budget / currBuy;
   }
   // Given the number of shares you can buy with your budget, find which profit is larger
   if (((prevSell - prevBuy) * prevStock) < ((currSell - currBuy) * currStock)) {
      return true;
   }
   return false;
}

void determineStockIndexes(vector<int> &stocks, int &buyIndex, int &sellIndex, int budget = 0)
{
   // Array should have at least 2 values, otherwise return since there's no profit to be made
   if (stocks.size() <= 1) {
      return;
   }
   // Initialize values to the first index stock price
   int bestBuyIndex(0), bestSellIndex(0), currBuyIndex(0), currSellIndex(0);
   // Loop through stock prices to find the best buy/sell values
   for (int i = 1; i < stocks.size(); ++i) {
      if (stocks[i] > stocks[currSellIndex]) {
         // As long as stock is increasing, we will continue to profit more. Save off the new sell index to make more money, buy index doesn't change
         currSellIndex = i;
      }
      else if (stocks[i] < stocks[currSellIndex]) {
         // The stock price is decreasing, but may be more valuable based on budget
         if (determineProfitBetter(stocks[bestBuyIndex], stocks[bestSellIndex], stocks[currBuyIndex], stocks[currSellIndex], budget)) {
            // Budget calculation shows an increase, set a new best buy/sell index pair despite the stock value decreasing
            bestBuyIndex = currBuyIndex;
            bestSellIndex = currSellIndex;
         }
         // The value has decreased, reset our indexes to the new min and start continue looking for the biggest positive difference
         currBuyIndex = i;
         currSellIndex = i;
      }
   }
   // Final check to see which is greater
   if(determineProfitBetter(stocks[bestBuyIndex], stocks[bestSellIndex], stocks[currBuyIndex], stocks[currSellIndex], budget)) {
      buyIndex = currBuyIndex;
      sellIndex = currSellIndex;
   }
   else {
      buyIndex = bestBuyIndex;
      sellIndex = bestSellIndex;
   }
}

/*
Interview code, not cleaned up, didn't implement budget portion

void determineStockIndexes(vector<int> &stocks, int &buyIndex, int &sellIndex)
{
   int prevBuyIndex(0), prevSellIndex(0), currBuyIndex(0), currSellIndex(0);
   for (int i = 1; i < stocks.size(); ++i) {
      if (stocks[i] > stocks[prevBuyIndex]) {
         // Stock increasing, save off the new sell index to make more money
         currSellIndex = i;
      }
      else if (stocks[i] < stocks[prevBuyIndex]) {
         // New lower price, check to save off new greatest indexes and start a new buy index check
         if ((stocks[prevSellIndex] - stocks[prevBuyIndex]) < (stocks[currSellIndex] - stocks[currBuyIndex])) {
            // Current buy/sell is better than prev, save it before starting over
            prevBuyIndex = currBuyIndex;
            prevSellIndex = currSellIndex;
         }
         currBuyIndex = i;
         currSellIndex = i;
      }
   }
   // Final check to see which is greater
   if ((stocks[prevSellIndex] - stocks[prevBuyIndex]) < (stocks[currSellIndex] - stocks[currBuyIndex])) {
      buyIndex = currBuyIndex;
      sellIndex = currSellIndex;
   }
   else {
      buyIndex = prevBuyIndex;
      sellIndex = prevSellIndex;
   }
}
*/

int main()
{
   vector<int> test;
   test.push_back(200);
   test.push_back(210);
   test.push_back(220);
   test.push_back(230);
   test.push_back(210);
   test.push_back(200);
   test.push_back(180);
   test.push_back(200);
   test.push_back(209);
   test.push_back(200);
   test.push_back(200);
   test.push_back(190);
   test.push_back(190);

   int buyIndex(0), sellIndex(0);
   determineStockIndexes(test, buyIndex, sellIndex);
   cout << "Buy: " << test[buyIndex] << "  Sell: " << test[sellIndex] << endl;

   determineStockIndexes(test, buyIndex, sellIndex, 1800);
   cout << "Buy: " << test[buyIndex] << "  Sell: " << test[sellIndex] << endl;

   system("PAUSE");
    return 0;
}

