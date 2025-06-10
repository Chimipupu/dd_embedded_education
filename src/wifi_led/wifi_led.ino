/**
 * @brief 実技演習 Step3のサンプルコード
 * 
 */

#include <WiFi.h>

// WiFi APの設定
#define AP_SSID     "ESP32_AP"    // APのSSID
#define AP_PASSWORD "12345678"    // APのパスワード
#define AP_CHANNEL  1             // WiFiチャンネル
#define AP_MAX_CONN 4             // 最大接続数

// LEDの設定
#define LED_PIN     2             // LEDが接続されているピン番号

// Webサーバーの設定
#define WEB_PORT    80            // HTTPポート番号

// WiFiサーバーのインスタンス作成
WiFiServer server(WEB_PORT);

void setup()
{
    // シリアル通信の初期化
    Serial.begin(115200);

    // LEDピンを出力モードに設定
    pinMode(LED_PIN, OUTPUT);

    // WiFi APの設定
    WiFi.softAP(AP_SSID, AP_PASSWORD, AP_CHANNEL, 0, AP_MAX_CONN);
    // APのIPアドレスを表示
    Serial.println("WiFi AP Started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    // Webサーバーを開始
    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    // クライアントからの接続を待機
    WiFiClient client = server.available();
    if (client) {
        Serial.println("New Client connected");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // HTTPレスポンスヘッダー
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        // HTMLコンテンツ
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
                        client.println("<title>ESP32 LED Control</title>");
                        client.println("<style>");
                        client.println("body { font-family: Arial; text-align: center; margin: 20px; }");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 15px 32px;");
                        client.println("text-align: center; text-decoration: none; display: inline-block; font-size: 16px;");
                        client.println("margin: 4px 2px; cursor: pointer; border-radius: 4px; }");
                        client.println("</style></head>");
                        // ボディ
                        client.println("<body>");
                        client.println("<h1>ESP32 LED Control</h1>");
                        client.println("<p><a href='/on'><button class='button'>ON</button></a></p>");
                        client.println("<p><a href='/off'><button class='button'>OFF</button></a></p>");
                        client.println("</body></html>");
                        break;
                    } else {
                        // LEDの制御
                        if (currentLine.indexOf("GET /on") >= 0) {
                            digitalWrite(LED_PIN, HIGH);
                        } else if (currentLine.indexOf("GET /off") >= 0) {
                            digitalWrite(LED_PIN, LOW);
                        }
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }

        // クライアント接続を終了
        client.stop();
        Serial.println("Client disconnected");
    }
}