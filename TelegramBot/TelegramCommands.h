#pragma once

#include <Arduino.h>
#include <HTTPClient32.h>
#include "TelegramClient.h"
#include <ArduinoJson.h>

class TelegramUpdate;

class TelegramCommand {
    public:
        TelegramCommand(TelegramBot* bot) {
            this->bot = bot;
        }

        virtual ~TelegramCommand() {
            if (this->client) {
                delete client;
            }
            freeResponse();
        }

        void freeResponse() {
            if (json) {
                delete json;
                json = NULL;
            }
        }

        virtual bool getResponse();

        JsonVariant getResult() {
            if (!json) {
                return JsonVariant();
            }
            json->getMember(F("result"));
            return json->getMember(F("result"));
        }

        JsonArray getResultArr() {
            JsonVariant result = this->getResult();
            if (result.is<JsonArray>()) {
                return result.as<JsonArray>();
            }
            return JsonArray();
        }

        JsonObject getResultObject() {
            JsonVariant result = this->getResult();
            if (result.is<JsonObject>()) {
                return result.as<JsonObject>();
            }
            return JsonObject();
        }

        String getRawResult();

    protected:
        TelegramBot*    bot;
        HTTPClient32*   client = NULL;
        String          result;
        DynamicJsonDocument* json = NULL;

        void init(HTTPClient32::METHOD_TYPE method, String command) {
            client = bot->createClient(method, command);
        }
};


class TelegramGetUpdates: protected TelegramCommand {
    protected:
        HTTPClient32PostMultipartBody*  body = NULL;
        HTTPClient32MultipartString*    offsetValue = NULL;
        HTTPClient32MultipartString*    limitValue = NULL;
        HTTPClient32MultipartString*    allowedValue = NULL;
        uint16_t                        updates = 0;

    public:
        TelegramGetUpdates(TelegramBot* bot): TelegramCommand(bot) {
            this->init(HTTP_METHOD_POST, F("getUpdates"));
            body = client->setPostMultipartBody();
            setAllowedUpdates(F("[\"message\",\"channel_post\"]"));
        }

        TelegramGetUpdates* setOffset(String offset);

        TelegramGetUpdates* setLimit(uint16_t msg_limit);

        TelegramGetUpdates* setAllowedUpdates(String allowed_updates_json);

        virtual bool getResponse();

        TelegramUpdate* getUpdate(uint16_t num);

        uint16_t getUpdates() {
            return updates;
        }
};

class TelegramSendMessage: public TelegramCommand {
    protected:
        HTTPClient32PostMultipartBody*  body;
        HTTPClient32MultipartString*    textValue = NULL;
        HTTPClient32MultipartString*    chatIdValue = NULL;
        HTTPClient32MultipartString*    replyMarkupValue = NULL;
        HTTPClient32MultipartString*    parseValue = NULL;

    public:
        TelegramSendMessage(TelegramBot* bot);

        TelegramSendMessage* setText(String text);

        TelegramSendMessage* setChatId(String chat_id);

        TelegramSendMessage* setParseMode(String parse_mode);

        TelegramSendMessage* setReplyMarkup(String reply_markup);
};

class TelegramSendPhoto: public TelegramCommand {
    protected:
        HTTPClient32PostMultipartBody*  body;
        HTTPClient32MultipartString*    textValue = NULL;
        HTTPClient32MultipartString*    chatIdValue = NULL;
        HTTPClient32MultipartString*    replyMarkupValue = NULL;
        HTTPClient32MultipartString*    parseValue = NULL;
        HTTPClient32MultipartFileFS*    fileValue = NULL;

    public:
        TelegramSendPhoto(TelegramBot* bot);

        TelegramSendPhoto* setText(String text);

        TelegramSendPhoto* setChatId(String chat_id);

        TelegramSendPhoto* setParseMode(String parse_mode);

        TelegramSendPhoto* setReplyMarkup(String reply_markup);

        TelegramSendPhoto* setPhoto(String filename, String contentType, File &file);
};