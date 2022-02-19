#include "TelegramStructs.h"
#include <ArduinoJson.h>

TelegramUpdate* TelegramUpdate::create(uint32_t update_id, JsonObject update) {
    if (update.containsKey(F("update_id"))) {
        if (update.containsKey(F("message"))) {
            TelegramUpdate* result = new TelegramUpdate(update_id, TelegramBasicMessage::createFromMessage(update.getMember(F("message"))) );
            if (result->entity) {
                return result;
            } else {
                delete result;
                return NULL;
            }
        }
        if (update.containsKey(F("channel_post"))) {
            TelegramUpdate* result = new TelegramUpdate(update_id, TelegramChannelPost::createFromMessage(update.getMember(F("channel_post"))) );
            if (result->entity) {
                return result;
            } else {
                delete result;
                return NULL;
            }
        }
    }
    return NULL;
}

TelegramBasicMessage* TelegramBasicMessage::createFromMessage(JsonObject msg) {
    if (!msg.containsKey(F("message_id"))) {
        return NULL;
    }
    return new TelegramBasicMessage(msg);
}

TelegramChannelPost* TelegramChannelPost::createFromMessage(JsonObject msg) {
    if (!msg.containsKey(F("message_id"))) {
        return NULL;
    }
    return new TelegramChannelPost(msg);
}
