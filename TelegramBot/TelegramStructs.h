#pragma once

#include <Arduino.h>
#include "TelegramClient.h"
#include <ArduinoJson.h>


class TelegramEntity {
    public:
        String date;
        String type;

        virtual ~TelegramEntity() {};

        void setType(String t, String d) {
            date = d;
            type = t;
        }
};

class TelegramUpdate {
    public:

        uint32_t        update_id;
        TelegramEntity* entity = NULL;

        ~TelegramUpdate() {
            if (entity) {
                delete entity;
            }
        }

        TelegramUpdate(uint32_t id, TelegramEntity* e): update_id(id), entity(e) {};

        static TelegramUpdate* create(uint32_t update_id, JsonObject update);
};


class TelegramBasicMessage: public TelegramEntity {
    public:
        String text;
        String from_id;
        String from_name;

        String message_id;  
        String reply_to_message_id;

        TelegramBasicMessage(JsonObject msg) {
            this->setType(F("message"), msg.getMember(F("date")).as<String>());
            this->message_id = msg.getMember(F("message_id")).as<String>();
        
            if (msg.containsKey(F("text"))) {
                this->text = msg.getMember(F("text")).as<String>();
            }

            this->from_id = msg["from"]["id"].as<String>();
            this->from_name = msg["from"]["first_name"].as<String>();

            if (msg.containsKey(F("reply_to_message"))) {
                this->reply_to_message_id = msg["reply_to_message"]["message_id"].as<String>();
            }
        }

        static TelegramBasicMessage* createFromMessage(JsonObject msg);
};

class TelegramChannelPost: public TelegramBasicMessage {
    public:
        String chat_id;
        String chat_title;

        TelegramChannelPost(JsonObject msg): TelegramBasicMessage(msg) {
            this->chat_id = msg["chat"]["id"].as<String>();
            this->chat_title = msg["chat"]["title"].as<String>();
        }

        static TelegramChannelPost* createFromMessage(JsonObject msg);
};