/**
 * @brief 実技演習 Step2のサンプルコード
 * 
 */

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
