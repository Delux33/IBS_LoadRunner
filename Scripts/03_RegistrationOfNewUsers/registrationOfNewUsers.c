registrationOfNewUsers()
{
	lr_start_transaction("03_Registration_of_new_users");
	
	lr_start_transaction("Web_tours");

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
		"Snapshot=t9.inf", 
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
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		LAST);
	
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
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Web_tours",LR_AUTO);

	lr_start_transaction("Sign_up_now");
	
	web_reg_find("Text=First time registering? Please complete the form below",LAST);
	
	lr_save_string(lr_eval_string("{login}"),"singletonLogin");
	
	lr_save_string(lr_eval_string("{password}"),"singletonPassword");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_url("login.pl", 
		"URL=http://127.0.0.1:8090/WebTours/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/home.html", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Sign_up_now",LR_AUTO);

	lr_start_transaction("Customer_profile");

	web_add_auto_header("Origin", 
		"http://127.0.0.1:8090");
	
	web_reg_find("Text/IC=Thank you, <b>{singletonLogin}</b>, for registering and welcome to the Web Tours family.",LAST);

	web_submit_data("login.pl_2", 
		"Action=http://127.0.0.1:8090/WebTours/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/login.pl", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={singletonLogin}", ENDITEM, 
		"Name=password", "Value={singletonPassword}", ENDITEM, 
		"Name=passwordConfirm", "Value={singletonPassword}", ENDITEM, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=register.x", "Value=43", ENDITEM, 
		"Name=register.y", "Value=16", ENDITEM, 
		LAST);

	lr_end_transaction("Customer_profile",LR_AUTO);

	lr_start_transaction("After_registration_button_continue");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");
	
	web_reg_find("Text/IC=Welcome, <b>{singletonLogin}</b>, to the Web Tours reservation pages.",LAST);

	web_url("button_next.gif", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/login.pl", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("After_registration_button_continue",LR_AUTO);

	lr_start_transaction("Logout");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_reg_find("Text=Welcome to the Web Tours site",LAST);

	web_url("SignOff Button", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	
	lr_end_transaction("03_Registration_of_new_users",LR_AUTO);

	return 0;
}