# 組み込み講座（第1回 2025年6月11日📅開催）

---

# 実技演習資料🛠️

実際に組み込みで使われるマイコンを搭載した基板で「実技演習」をしましょう！
プログラムはC言語を知らなくてもわかるようにコメントに意味を記載してます。

---

## ステップ1：LEDの点灯・消灯をしよう！💡

### 目標

* ESP32の内蔵LEDを点灯・消灯できるようにする

### 実習のポイント ✅

* GPIOピンを**出力モード**に設定しよう
* **HIGH**で点灯、**LOW**で消灯する仕組みを理解しよう

### コードの流れ🧠（コメント付き）

```cpp
void setup() {
  pinMode(2, OUTPUT);  // GPIO 2 を出力モードに設定（内蔵LEDが接続されている）
}

void loop() {
  digitalWrite(2, HIGH);  // LEDを点灯
  delay(1000);            // 1秒待つ
  digitalWrite(2, LOW);   // LEDを消灯
  delay(1000);            // 1秒待つ
}
```

---

## ステップ2：センサーで温度・湿度・気圧を取得しよう🌡️

### 使用デバイス

* BME280 センサー（I2C通信）

### 実習のポイント ✅

* I2C通信の**ライブラリ利用**方法を学ぼう
* センサーからの値を**float型**で扱おう

### コードの流れ🧠（コメント付き）

```cpp
#include <Wire.h>                  // I2C通信ライブラリ
#include <Adafruit_BME280.h>      // BME280用ライブラリ

Adafruit_BME280 bme;              // センサーのインスタンスを作成

void setup() {
  Wire.begin();                   // I2C通信の開始
  bool status = bme.begin(0x76); // センサー初期化（I2Cアドレス指定）
  if (!status) {
    Serial.println("BME280が見つかりませんでした");
    while (1); // 初期化失敗時は停止
  }
}

void loop() {
  float temp = bme.readTemperature();   // 温度を取得
  float hum  = bme.readHumidity();      // 湿度を取得
  float pres = bme.readPressure() / 100.0F; // 気圧（hPa）を取得

  // 値をシリアルモニタに出力
  Serial.print("気温: "); Serial.print(temp); Serial.println(" *C");
  Serial.print("湿度: "); Serial.print(hum);  Serial.println(" %");
  Serial.print("気圧: "); Serial.print(pres); Serial.println(" hPa");

  delay(2000); // 2秒ごとに更新
}
```

---

## ステップ3：WiFiに接続してLEDを操作しよう！🌐💡

### 概要

* ESP32をWiFiに接続し、WebブラウザからLEDの制御ができるようにする

### 実習のポイント ✅

* WiFi接続の状態を確認する方法を覚えよう
* クライアントが来たときにHTTPレスポンスを返そう

### コードの流れ🧠（コメント付き）

```cpp
#include <WiFi.h>

const char* ssid = "YOUR_SSID";          // WiFiのSSIDを入力
const char* password = "YOUR_PASSWORD";  // パスワードを入力

WiFiServer server(80);                   // ポート80番でWebサーバを用意

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);                    // LED用ピンを出力に設定

  WiFi.begin(ssid, password);            // WiFiに接続開始
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("接続中...");
  }
  Serial.println("WiFi接続完了");
  Serial.println(WiFi.localIP());        // IPアドレスを表示

  server.begin();                        // サーバ起動
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("クライアントが接続しました");
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    // LEDの状態を反転（ON→OFF→ON...）
    digitalWrite(2, !digitalRead(2));

    // HTMLレスポンスを返す
    client.println("<h1>LEDが切り替わりました！</h1>");
    client.stop();
  }
}
```

---

## 質疑応答 💬

* わからなかったことはここで聞いてみましょう！