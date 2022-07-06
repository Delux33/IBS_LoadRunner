Delete_ticket()
{
	int i;
	
	lr_start_transaction("02_Delete_ticket");
	
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
	
	lr_think_time(5);
	
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
	
	lr_think_time(5);
	
	lr_start_transaction("Itineraries");
	
	web_reg_find("Text=No flights have been reserved.",
                 "SaveCount=not_flights",
                 LAST);
	
	if (atoi(lr_eval_string("{not_flights}")) > 0) {
		web_reg_find("Text=No flights have been reserved.",LAST);
	} else {
		web_reg_find("Text=Flights List",LAST);
	}

    web_url("Itinerary Button",
    "URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=itinerary",
    "TargetFrame=body",
    "Resource=0",
    "RecContentType=text/html",
    "Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home",
    "Snapshot=t3.inf",
    "Mode=HTML",
    LAST);
	
    web_reg_save_param("c_flightids",
    "lb=<input type=\"hidden\" name=\"flightID\" value=\"",
    "rb=\"  />",
    "ord=all",
    LAST);

    web_reg_save_param("c_cgifields",
    "lb=<input type=\"hidden\" name=\".cgifields\" value=\"",
    "rb=\"  />",
    "ord=all",
    LAST);
		
	web_url("Itinerary Button",
    "URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=itinerary",
    "TargetFrame=body",
    "Resource=0",
    "RecContentType=text/html",
    "Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home",
    "Snapshot=t3.inf",
    "Mode=HTML",
    LAST);

    lr_end_transaction("Itineraries", LR_AUTO);
    
    lr_think_time(5);

    lr_start_transaction("CancelItinerary");
    	
    lr_param_sprintf("c_buffer", "%s=on&", lr_eval_string("{c_flightids_count}"));
    	
    for (i = 1; i <= atoi(lr_eval_string("{c_flightids_count}")); i++) {
    	
    lr_param_sprintf("c_buffer", "%sflightID=%s&", lr_eval_string("{c_buffer}"), lr_paramarr_idx("c_flightids", i));

    lr_param_sprintf("c_buffer", "%s.cgifields=%s&", lr_eval_string("{c_buffer}"), lr_paramarr_idx("c_cgifields", i));

    lr_save_string(lr_eval_string("{c_buffer}removeFlights.x=36&removeFlights.y=4"), "c_wcr");

    lr_save_string(lr_eval_string(lr_eval_string("{c_flightids_{c_flightids_count}}")), "c_cancelflight");

    web_reg_find("Text={c_cancelflight}", "Fail=Found", LAST);
    	
    web_custom_request("itinerary.pl_2",
    "URL=http://127.0.0.1:8090/WebTours/itinerary.pl",
    "Method=POST",
   	"Resource=0",
   	"RecContentType=text/html",
   	"Referer=http://127.0.0.1:8090/WebTours/itinerary.pl",
   	"Snapshot=t23.inf",
   	"Mode=HTTP",
   	"Body={c_wcr}",
   	LAST);
    
	}
    
    lr_end_transaction("CancelItinerary", LR_AUTO);
    
    lr_think_time(5);
    
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
    
    lr_end_transaction("02_Delete_ticket", LR_AUTO);
    
    return 0;

}