#include "TelegramClient.h"

HTTPClient32* TelegramBot::createClient(HTTPClient32::METHOD_TYPE method, String command) {
    HTTPClient32* client = new HTTPClient32();
    client->prepareHTTPS(method, F("api.telegram.org"), 443, (String(F("/bot")) + authKey + '/' + command), TELEGRAM_CERTIFICATE_ROOT);
    return client;
}

String TelegramBot::getResult(HTTPClient32* client) {
    if (!client->HTTP()) {
        return String(F(""));
    }
    /*HTTPClient32Headers* headers = client->getResponseHeaders();
    //DEBUGLN("RESPONSE:");
    for (uint8_t i = 0; i < headers->size(); i++) {
				HTTPClient32Headers::Header* h = headers->get(i);
				//DEBUGLN("Response header: " + h->name + "=" + h->value);
			}*/
    
    return client->getResponseString();
}
