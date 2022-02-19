#include "TelegramCommands.h"
#include <ArduinoJson.h>
#include <TelegramStructs.h>

bool TelegramCommand::getResponse() {
    freeResponse();
    result = bot->getResult(client);
    DEBUG("telegram: ");
    DEBUGLN(result);
    DynamicJsonDocument* doc = new DynamicJsonDocument(2048);
    DeserializationError error = deserializeJson(*doc, result.c_str());
    if (!error && doc->containsKey(F("ok")) && doc->containsKey(F("result"))) {
        json = doc;
        return json->getMember(F("ok")).as<bool>();
    }
    return false;
}

String TelegramCommand::getRawResult() {
    return this->result;
}

TelegramGetUpdates* TelegramGetUpdates::setOffset(String offset) {
    if (!offsetValue) {
        offsetValue = body->addContentString(F("offset"), offset);
    } else {
        offsetValue->setValue(offset);
    }
    freeResponse();
    return this;
}

TelegramGetUpdates* TelegramGetUpdates::setLimit(uint16_t msg_limit) {
    if (!offsetValue) {
        limitValue = body->addContentString(F("msg_limit"), String(msg_limit));
    } else {
        limitValue->setValue(String(msg_limit));
    }
    freeResponse();
    return this;
}

TelegramGetUpdates* TelegramGetUpdates::setAllowedUpdates(String allowed_updates_json) {
    if (!offsetValue) {
        allowedValue = body->addContentString(F("allowed_updates"), String(allowed_updates_json));
    } else {
        allowedValue->setValue(String(allowed_updates_json));
    }
    freeResponse();
    return this;
}

bool TelegramGetUpdates::getResponse() {
    freeResponse(); updates = 0;
    if (TelegramCommand::getResponse() && getResultArr().size() > 0) {
        updates = getResultArr().size();
        return true;
    }
    return false;
}

TelegramUpdate* TelegramGetUpdates::getUpdate(uint16_t num) {
    if (updates == 0 || num >= updates) {
        if (!this->getResponse()) {
            return NULL;
        }
    }
    JsonObject updateRec = getResultArr()[num];
    if (!updateRec.containsKey(F("update_id"))) {
        return NULL;
    }
    return TelegramUpdate::create(updateRec.getMember(F("update_id")).as<unsigned int>(), updateRec);
}

TelegramSendMessage::TelegramSendMessage(TelegramBot* bot) : TelegramCommand(bot){
    this->init(HTTP_METHOD_POST, F("sendMessage"));
    body = client->setPostMultipartBody();
}

TelegramSendMessage* TelegramSendMessage::setText(String text) {
    if (!textValue) {
        textValue = body->addContentString(F("text"), text);
    } else {
        textValue->setValue(text);
    }
    return this;
}

TelegramSendMessage* TelegramSendMessage::setChatId(String chat_id) {
    if (!chatIdValue) {
        chatIdValue = body->addContentString(F("chat_id"), chat_id);
    } else {
        chatIdValue->setValue(chat_id);
    }
    return this;
}

TelegramSendMessage* TelegramSendMessage::setParseMode(String parse_mode) {
    if (!parseValue) {
        parseValue = body->addContentString(F("parse_mode"), parse_mode);
    } else {
        parseValue->setValue(parse_mode);
    }
    return this;
}

TelegramSendMessage* TelegramSendMessage::setReplyMarkup(String reply_markup) {
    if (!replyMarkupValue) {
        replyMarkupValue = body->addContentString(F("reply_markup"), reply_markup);
    } else {
        replyMarkupValue->setValue(reply_markup);
    }
    return this;
}

TelegramSendPhoto::TelegramSendPhoto(TelegramBot* bot) : TelegramCommand(bot){
    this->init(HTTP_METHOD_POST, F("sendPhoto"));
    body = client->setPostMultipartBody();
}

TelegramSendPhoto* TelegramSendPhoto::setText(String text) {
    if (!textValue) {
        textValue = body->addContentString(F("caption"), text);
    } else {
        textValue->setValue(text);
    }
    return this;
}

TelegramSendPhoto* TelegramSendPhoto::setChatId(String chat_id) {
    if (!chatIdValue) {
        chatIdValue = body->addContentString(F("chat_id"), chat_id);
    } else {
        chatIdValue->setValue(chat_id);
    }
    return this;
}

TelegramSendPhoto* TelegramSendPhoto::setParseMode(String parse_mode) {
    if (!parseValue) {
        parseValue = body->addContentString(F("parse_mode"), parse_mode);
    } else {
        parseValue->setValue(parse_mode);
    }
    return this;
}

TelegramSendPhoto* TelegramSendPhoto::setReplyMarkup(String reply_markup) {
    if (!replyMarkupValue) {
        replyMarkupValue = body->addContentString(F("reply_markup"), reply_markup);
    } else {
        replyMarkupValue->setValue(reply_markup);
    }
    return this;
}

TelegramSendPhoto* TelegramSendPhoto::setPhoto(String filename, String contentType, File &file) {
    if (!fileValue) {
        fileValue = body->addContentFileFS(F("photo"), filename, contentType, file);
    } else {
        fileValue->setValue(filename, contentType, file);
    }
    return this;
}
