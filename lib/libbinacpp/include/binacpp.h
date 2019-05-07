
/*
	Author: 
	Date  : 2017/10/15
	
	C++ library for Binance API.
*/


#ifndef BINACPP_H
#define BINACPP_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <exception>

#include <curl/curl.h>
#include <json/json.h>

#include <functional>


#define BITHUMB_HOST "https://global-openapi.bithumb.pro/openapi/api"


using namespace std;


static map<string, string> post_data;
typedef function<bool(pair<string, string>, pair<string, string>)> comparator;

comparator compFunctor =
			[](std::pair<string, string> elem1 ,pair<string, string> elem2)
			{
				return elem1.first < elem2.first;
			};

class BthmCPP {

	static string api_key;
	static string secret_key;
	static CURL* curl;

	

	public:

		

		static void curl_api( string &url, string &result_json );
		static void curl_api_with_header( string &url, string &result_json , vector <string> &extra_http_header, string &post_data, string &action );
		static size_t curl_cb( void *content, size_t size, size_t nmemb, string *buffer ) ;
		
		static void init( string &api_key, string &secret_key);
		static void cleanup();

		static string sign(map<string, string> post_data);

		// Public API
		static void get_serverTime( Json::Value &json_result); 	

		static void get_allPrices( Json::Value &json_result );
		static double get_price( const char *symbol );

		static void get_allBookTickers( Json::Value &json_result );
		static void get_bookTicker( const char *symbol, Json::Value &json_result ) ;

		static void get_depth( const char *symbol, Json::Value &json_result );
		static void get_aggTrades( const char *symbol, int fromId, time_t startTime, time_t endTime, int limit, Json::Value &json_result ); 
		static void get_24hr( const char *symbol, Json::Value &json_result ); 
		static void get_klines( const char *symbol, const char *interval, time_t startTime, time_t endTime,  Json::Value &json_result );


		// API + Secret keys required
		static void get_account( long recvWindow , Json::Value &json_result );
		
		static void get_myTrades( 
			const char *symbol, 
			int limit,
			long fromId,
			long recvWindow, 
			Json::Value &json_result 
		);
		
		static void get_openOrders(  
			const char *symbol, 
			Json::Value &json_result 
		) ;
		

		static void get_allOrders(   
			const char *symbol, 
			long orderId,
			int limit,
			long recvWindow,
			Json::Value &json_result 
		);


		static void send_order( 
			const char *symbol, 
			const char *side,
			const char *type,
			double quantity,
			double price,
			Json::Value &json_result ) ;


		static void get_order( 
			const char *symbol, 
			long orderId,
			const char *origClientOrderId,
			long recvWindow,
			Json::Value &json_result ); 


		static void cancel_order( 
			const char *symbol, 
			long orderId,
			//const char *origClientOrderId,
			//const char *newClientOrderId,
			//long recvWindow,
			Json::Value &json_result 
		);

		// API key required
		static void start_userDataStream( Json::Value &json_result );
		static void keep_userDataStream( const char *listenKey  );
		static void close_userDataStream( const char *listenKey );


		// WAPI
		static void withdraw( 
			const char *asset,
			const char *address,
			const char *addressTag,
			double amount, 
			const char *name,
			long recvWindow,
			Json::Value &json_result );

		static void get_depositHistory( 
			const char *asset,
			int  status,
			long startTime,
			long endTime, 
			long recvWindow,
			Json::Value &json_result );

		static void get_withdrawHistory( 
			const char *asset,
			int  status,
			long startTime,
			long endTime, 
			long recvWindow,
			Json::Value &json_result ); 

		static void get_depositAddress( 
			const char *asset,
			long recvWindow,
			Json::Value &json_result );


};


#endif
