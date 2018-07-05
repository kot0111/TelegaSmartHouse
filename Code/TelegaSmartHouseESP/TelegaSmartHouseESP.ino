/* Код для прошивки микроконтроллера esp8266
Автор - kot0111
Необходимо указать ssid и пароль WiFi, свой id и токен бота, полученный при его создании. 
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
char ssid[] = "WiFi Ssid";
char password[] = "WiFi password";
bool updinfo = false;
String instring;
String user = "Telegram id";
String chat_id;
String outstring;
#define Bottoken "Bot token"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
String keyboardJson = "[[\"/ledon\", \"/ledoff\", \"/tempupd\"]]";
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
void loop() {
  int numNewMessages = bot.getUpdates(
                         bot.last_message_received + 1);
  handleNewMessages(numNewMessages);
  if (Serial.available() > 0){
    updinfo= false;
    instring = Serial.readStringUntil('\n');
    outstring= "Temp: " + instring;
    bot.sendMessage(chat_id, outstring, "");
    
  }
}
void handleNewMessages(int numNewMessages) {
  if (!updinfo) {
    for (int i = 0; i < numNewMessages; i++) {
       chat_id = String(bot.messages[i].chat_id);
      String user_id = String(bot.messages[i].from_id);
      String text = bot.messages[i].text;
      if (text == "/ledon" && user_id == user ) {
        Serial.println("turnOn");
        bot.sendMessage(chat_id, "Relay is ON", "");
      }
      if (text == "/ledoff" && user_id == user) {
        Serial.println("turnOff");
        bot.sendMessage(chat_id, "Relay is OFF", "");
      }
      if (text == "/start"  && user_id == user) {
        bot.sendMessageWithReplyKeyboard(chat_id,
                                         "Choose from one of the following options",
                                         "", keyboardJson, true);
      }
      if (text == "/tempupd"  && user_id == user) {
        Serial.println("tempUpd");
        updinfo = true;
      }
    }
  }
}
