#pragma once

#include <Arduino.h>
#include "TelegramCertificate.h"

#include <HTTPClient32.h>

class TelegramBot {
    public:
        TelegramBot(String key) {
            this->authKey = key;
        }

        /*
        String getUpdates(long offset, uint16_t msg_limit, String allowed_updates_json) {
            HTTPClient32* client = createClient(HTTP_METHOD_POST, "getUpdates");

            HTTPClient32PostMultipartBody* body = client->setPostMultipartBody();
            body->addContentString(F("offset"), String(offset));
            body->addContentString(F("limit"), String(msg_limit));
            
            if (allowed_updates_json.length() > 0) {
                body->addContentString(F("allowed_updates"), allowed_updates_json);
            }

            return getResult(client);
        }

        String getNewUpdates(uint16_t msg_limit, String allowed_updates_json) {
            String params = String(F("getUpdates?limit=")) + msg_limit;
            if (allowed_updates_json.length() > 0) {
                params += String(F("allowed_updates=") + allowed_updates_json;
            }
            HTTPClient32* client = createClient(HTTP_METHOD_GET, params));

            return getResult(client);
        }

        String getNewUpdate(uint16_t msg_limit = 1) {
            return getNewUpdates(msg_limit, TELEGRAMBOT_GETUPDATES_ALLOWEDUPDATES);
        }

        String getUpdates(long offset, uint16_t msg_limit = 1) {
            return getUpdates(offset, msg_limit, TELEGRAMBOT_GETUPDATES_ALLOWEDUPDATES);
        }*/

        /*//@implement
        String sendMessage(String text, String chat_id, int message_id = 0, String parse_mode = "", String reply_markup = "") {
            HTTPClient32* client = createClient(HTTP_METHOD_POST, "sendMessage");

            HTTPClient32PostMultipartBody* body = client->setPostMultipartBody();
            body->addContentString(F("text"), text);
            body->addContentString(F("chat_id"), chat_id);
            
            if (message_id != 0) {
                body->addContentString(F("message_id"), String(message_id));
            }

            if (parse_mode.length()) {
                body->addContentString(F("parse_mode"), parse_mode);
            }

            if (reply_markup.length()) {
                body->addContentString(F("reply_markup"), reply_markup);
            }

            return getResult(client);
        }

        bool sendPhoto(String text, String chat_id, File &file) {
            return false;
        }*/

        HTTPClient32* createClient(HTTPClient32::METHOD_TYPE method, String command);

        String getResult(HTTPClient32* client);

    protected:
        String authKey;
};