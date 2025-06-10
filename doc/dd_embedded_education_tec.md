# 組み込み講座（第1回 2025年6月11日📅開催）

---

# 実技演習資料🛠️

実際に組み込みで使われるマイコンを搭載した基板で「実技演習」をしましょう！
プログラムはC言語を知らなくてもわかるようにコメントに意味を記載してます。

---

## ステップ1：LEDの点灯・消灯してみよう！

### 目標

- 基板のLEDをマイコンに点灯・消灯させる

### 実習のポイント ✅

- GPIOピンを**出力モード**に設定しよう
- **HIGH**で点灯、**LOW**で消灯するのを理解しよう

### コード

```cpp
// LEDの定義
#define LED_PIN     2    // LEDが接続されているピン番号
#define DELAY_TIME  1000 // 1000ミリ秒 = 1秒

void setup()
{
    // LEDピンを出力(OUTPUT)モードに設定処理
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    // LED点灯
    digitalWrite(LED_PIN, HIGH);
    delay(DELAY_TIME);

    // LED消灯
    digitalWrite(LED_PIN, LOW);
    delay(DELAY_TIME);
}
```

---

## ステップ2：：文字を表示してみよう！

### 目標

- 基板のマイコンに文字をシリアル通信（UART）で表示させる

### 実習のポイント ✅

- 表示する文字を変えてみよう
- シリアル通信を理解しよう

### コード
```cpp
// シリアル通信の設定
#define BAUD_RATE    115200  // UART通信ボーレート
#define DELAY_TIME   1000    // 送信間隔（ミリ秒）

void setup()
{
    // シリアル通信(UART)の初期化
    Serial.begin(BAUD_RATE);
}

void loop()
{
    // メッセージを送信
    Serial.println("Hello from ESP32!");

    // 一定時間待機
    delay(DELAY_TIME);
}
```

---

## ステップ3：WiFiに接続してLEDを遠隔操作してみよう！

### 目標

- マイコンのWiFiに接続してWEBブラウザからLEDを制御ができるようにする

### 実習のポイント ✅

- WiFiに接続してみよう！
- HTMLでLDEをON、OFFをしてみよう！

### コード

```cpp
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
```

---

## 質疑応答 💬

- わからなかったことはここで聞いてみましょう！