
char* host = "www.wunderground.com";
char* page = "/api/Your_Key/conditions/q/CA/San_Francisco.json";

char* result = httpget(host, page);

printf(result);