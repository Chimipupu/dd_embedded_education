/**
 * @brief 実技演習 Step1のサンプルコード
 * 
 */

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
