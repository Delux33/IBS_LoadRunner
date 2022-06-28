Action1()
{

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_header("Sec-Fetch-Site", 
		"cross-site");

	web_add_header("X-Client-Data", 
		"CMisygE=");

	web_url("newtab_ogb", 
		"URL=https://www.google.com/async/newtab_ogb?hl=ru&async=fixed:0", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	lr_start_transaction("Web_tours");

	web_add_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(10);

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

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(13);

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

	lr_think_time(23);

	web_submit_data("login.pl_2", 
		"Action=http://127.0.0.1:8090/WebTours/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=Dima", ENDITEM, 
		"Name=password", "Value=123", ENDITEM, 
		"Name=passwordConfirm", "Value=123", ENDITEM, 
		"Name=firstName", "Value=Dmitrii", ENDITEM, 
		"Name=lastName", "Value=Tryanin", ENDITEM, 
		"Name=address1", "Value=Vaneeva", ENDITEM, 
		"Name=address2", "Value=dsfsdf", ENDITEM, 
		"Name=register.x", "Value=62", ENDITEM, 
		"Name=register.y", "Value=3", ENDITEM, 
		LAST);

	lr_think_time(4);

	web_submit_data("login.pl_3", 
		"Action=http://127.0.0.1:8090/WebTours/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/login.pl", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=Dimae", ENDITEM, 
		"Name=password", "Value=123", ENDITEM, 
		"Name=passwordConfirm", "Value=123", ENDITEM, 
		"Name=firstName", "Value=Dmitrii", ENDITEM, 
		"Name=lastName", "Value=Tryanin", ENDITEM, 
		"Name=address1", "Value=Vaneeva", ENDITEM, 
		"Name=address2", "Value=dsfsdf", ENDITEM, 
		"Name=register.x", "Value=43", ENDITEM, 
		"Name=register.y", "Value=16", ENDITEM, 
		LAST);

	lr_end_transaction("Customer_profile",LR_AUTO);

	lr_start_transaction("continue");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(13);

	web_url("button_next.gif", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/login.pl", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("continue",LR_AUTO);

	lr_start_transaction("logout");

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(9);

	web_url("SignOff Button", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);

	return 0;
}