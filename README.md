# TelegramBot
Telegram bot library

## Requirements
* HTTPClient32
* ArduinoJson

## Examples

### Send message
```
TelegramBot* bot = new TelegramBot(F("<bot_token>"));
	
TelegramSendMessage* msg  = new TelegramSendMessage(bot);
msg->setText("Test!")->setChatId("-<chat_id>");

DEBUG("sendMessage result: ");
DEBUGLN(msg->getResponse());

delete msg;
delete bot;
```

### Send photo from SD card
```
TelegramBot* bot = new TelegramBot(F("<bot_token>"));

TelegramSendPhoto* msg  = new TelegramSendPhoto(bot);
msg->setChatId(F("-<chat_id>"));
File photoFile = SD_MMC.open("/reportphoto_0.jpg", "r");
if (photoFile) {
	msg->setPhoto(F("photo.jpg"), F("image/jpeg"), photoFile);
	if (msg->getResponse()) {
		DEBUGLN("Publisher: File sent succesfully");
		photoFile.close();
	} else {
		DEBUGLN("Publisher: File send ERROR");
		photoFile.close();
	}
} else {
	DEBUGLN("File open ERROR");
}

delete msg;
delete bot;
```

### Get updates
```
TelegramGetUpdates* query = new TelegramGetUpdates(bot);
query->setLimit(1)->setOffset(-15);
DEBUGLN("getUpdates result: ");
DEBUGLN(query->getResponse());

if (query->getUpdates()) {
	TelegramUpdate* update = query->getUpdate(0);
	TRACELN(String(F("Update received: ")) + String(update->update_id));
	
	if (update->entity->type.equalsIgnoreCase(F("message"))) {
		TelegramChannelPost* msg = (TelegramChannelPost*)update->entity;
		// skip own messages
		if (msg->from_id != F(TELEGRAM_BOTID)) {
			TRACEF("GOT MESSAGE: ");
			TRACELN(msg->text);
		}
	}
	delete update;
	
} else {
	TRACELNF("No updates");
}

delete query;
delete bot;
```