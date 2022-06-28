TicketSearchWithoutPurchase()
{
	lr_start_transaction("05_Ticket_search_without_purchase");
	
	lr_start_transaction("Web_tours");
	
	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_reg_find("Text=Welcome to the Web Tours site",LAST);

	web_url("WebTours", 
		"URL=http://127.0.0.1:8090/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("Sec-Fetch-Mode", 
		"nested-navigate");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");


	web_url("header.html", 
		"URL=http://127.0.0.1:8090/WebTours/header.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	web_revert_auto_header("Sec-Fetch-Mode");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

/*Correlation comment - Do not change!  Original value='134128.001134062ziQQcAQpAfiDDDDDtVDQfpcftDf' Name ='userSession' Type ='RecordReplay'*/
	web_reg_save_param_regexp(
		"ParamName=userSession",
		"RegExp=userSession\\ value=(.*?)>",
		"Ordinal=3",
		SEARCH_FILTERS,
		"Scope=Body",
		"RequestUrl=*/nav.pl*",
		LAST);

	web_url("welcome.pl", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("Web_tours",LR_AUTO);
	
	lr_start_transaction("Login");

	web_add_header("Origin", 
		"http://127.0.0.1:8090");

	web_add_auto_header("Sec-Fetch-Mode", 
		"nested-navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	web_reg_find("Text/IC=Welcome, <b>{username}</b>, to the Web Tours reservation pages.",LAST);
	
	web_submit_data("login.pl",
		"Action=http://127.0.0.1:8090/WebTours/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:8090/WebTours/nav.pl?in=home",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={username}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=61", ENDITEM,
		"Name=login.y", "Value=2", ENDITEM,
		
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);
	
	lr_end_transaction("Login",LR_AUTO);

	lr_start_transaction("Togo_info_about_flight");
	
	web_reg_find("Text=Flight Selections",LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_url("Search Flights Button", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	
	web_add_auto_header("Origin", 
		"http://127.0.0.1:8090");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Ordinal=ALL",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
		
	web_reg_save_param_attrib(
		"ParamName=returnFlight",
		"TagName=input",
		"Extract=value",
		"Name=returnFlight",
		"Ordinal=ALL",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
	
	web_submit_data("reservations.pl", 
		"Action=http://127.0.0.1:8090/WebTours/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/reservations.pl?page=welcome", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={depart}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arrive}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
		"Name=roundtrip", "Value={roundtrip}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=findFlights.x", "Value=56", ENDITEM, 
		"Name=findFlights.y", "Value=14", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("Togo_info_about_flight",LR_AUTO);
	
	lr_start_transaction("Find_flight");
	
	web_reg_find("Text=Flight Reservation",LAST);
	
	lr_save_string(lr_eval_string(lr_paramarr_random("outboundFlight")),"outboundFlightVal");
	
	lr_save_string(lr_eval_string(lr_paramarr_random("returnFlight")),"returnFlightVal");

	web_submit_data("reservations.pl_2",
		"Action=http://127.0.0.1:8090/WebTours/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:8090/WebTours/reservations.pl",
		"Snapshot=t7.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlightVal}", ENDITEM,
		"Name=returnFlight", "Value={returnFlightVal}", ENDITEM,
		"Name=numPassengers", "Value={numPassengers}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=reserveFlights.x", "Value=50", ENDITEM,
		"Name=reserveFlights.y", "Value=7", ENDITEM,
		LAST);
	
	lr_end_transaction("Find_flight",LR_AUTO);
	
	lr_start_transaction("Logout");
    
    web_reg_find("Text=Welcome to the Web Tours site.",LAST);
    
    web_url("welcome.pl_2", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?signOff=1", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t78.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	
	lr_end_transaction("05_Ticket_search_without_purchase",LR_AUTO);
	
	return 0;
}
