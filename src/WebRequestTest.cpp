//#include "WebRequestTest.h"
//#include "curl/curl.h"
//#include "lua.hpp"
//
//size_t WebRequestTest::reqCallbackTest(void* content, size_t size, size_t nmemb, void* userp) {
//
//	size_t realSize = size * nmemb;
//	printf("%.*s\n", realSize, (char*)content);
//	return realSize;
//}
//
//size_t WebRequestTest::reqCallback(void* content, size_t size, size_t nmemb, void* userp) {
//
//	size_t realSize = size * nmemb;
//	printf("%.*s\n", realSize, (char*)content);
//	return realSize;
//}
//
//int WebRequestTest::webreq(lua_State* L) {
//
//	const char* url = lua_tostring(L, 1);
//	CURL* curl;
//	CURLcode res;
//
//
//	curl = curl_easy_init();
//
//	if (curl) {
//		curl_easy_setopt(curl, CURLOPT_URL, url);
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WebRequestTest::reqCallback);
//		res = curl_easy_perform(curl);
//		curl_easy_cleanup(curl);
//	}
//
//	return 0;
//}
//
//int WebRequestTest::print(lua_State* L) {
//
//	std::cout << "Hola desde lua :D" << std::endl;
//	return 0;
//}
//
//int WebRequestTest::sum(lua_State* L) {
//
//	int a = lua_tonumber(L, 1);
//	int b = lua_tonumber(L, 2);
//	lua_pushnumber(L, a + b);
//	return 1;
//}
//
//void WebRequestTest::testWebLua()
//{
//	CURL* curl;
//	CURLcode res;
//
//	curl = curl_easy_init();
//
//	if (curl) {
//		curl_easy_setopt(curl, CURLOPT_URL, "http://monsterballgo.com/api/names");
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WebRequestTest::reqCallbackTest);
//		res = curl_easy_perform(curl);
//		curl_easy_cleanup(curl);
//	}
//
//	lua_State* L = luaL_newstate();
//	luaL_openlibs(L);
//
//	lua_pushcfunction(L, print);
//	lua_setglobal(L, "mensaje");
//
//	lua_pushcfunction(L, sum);
//	lua_setglobal(L, "add");
//
//	lua_pushcfunction(L, webreq);
//	lua_setglobal(L, "webRequest");
//
//
//
//	//luaL_dostring(L, "print()");
//
//	if (luaL_dofile(L, "script.lua"))
//	{
//		const char* error = lua_tostring(L, -1);
//		std::cout << "Error al cargar el archivo: " << error << std::endl;
//	}
//}
