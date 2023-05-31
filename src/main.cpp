#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>

U8G2_SSD1306_128X64_NONAME_2_HW_I2C oled(U8G2_R0, /*reset=*/U8X8_PIN_NONE);
const byte BUTTON_PIN = 7;
const byte SOUND_PIN = 6;

unsigned long int time = millis();
const long int warningTime = 60000; // AutoShutoff time

byte rollMode = 1;
int dicenr1 = 1;     // Dice random number 1
int dicenr2 = 1;     // Dice random number 2
boolean BUZZ = true; // Sound on

void Roll();
void CleanScreen();
void randomGenerator();
void slow();

void setup(void)
{
    // oled.setI2CAddress(0x3C * 2); //set display adress if needed (default 0x3C)
    oled.begin();

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(SOUND_PIN, OUTPUT);
    // Serial.begin(9600);

    randomSeed(analogRead(A0));
    Roll();
    delay(1000);
}

void loop(void)
{
    if (digitalRead(BUTTON_PIN) == LOW)
    {

        rollMode = 0;
        do
        {
            randomGenerator();
            Roll();
        } while (digitalRead(BUTTON_PIN) == LOW);
        slow();
        time = millis();
        rollMode = 2;
    }

    Roll();
}

void Roll()
{
    String number[25] = {"One", "Two", "Three", "Four", "Five", "Six"};

    int x;
    int x1;
    const int y = 2;
    oled.setFont(u8g_font_helvB10);

    oled.firstPage();
    do
    {
        if (rollMode == 1)
        {
            oled.drawStr(36, 64, "Last Roll");
        }
        else if (rollMode == 0)
        {
            oled.drawStr(36, 64, "Roll Dice");
        }

        x = 76;

        oled.drawFrame(2 + x, y, 48, 48);
        if (dicenr1 == 1)
        {
            oled.drawDisc(26 + x, 24 + y, 4); // Center
            x1 = 13;
        }
        else if (dicenr1 == 2)
        {
            oled.drawDisc(12 + x, 10 + y, 4); // upper L
            oled.drawDisc(40 + x, 38 + y, 4); // lower R
            x1 = 14;
        }
        else if (dicenr1 == 3)
        {
            oled.drawDisc(26 + x, 24 + y, 4); // Center
            oled.drawDisc(12 + x, 10 + y, 4); // upper L
            oled.drawDisc(40 + x, 38 + y, 4); // lower R
            x1 = 7;
        }
        else if (dicenr1 == 4)
        {
            oled.drawDisc(12 + x, 10 + y, 4); // upper L
            oled.drawDisc(40 + x, 10 + y, 4); // upper R
            oled.drawDisc(12 + x, 38 + y, 4); // lower L
            oled.drawDisc(40 + x, 38 + y, 4); // lower R
            x1 = 11;
        }
        else if (dicenr1 == 5)
        {
            oled.drawDisc(12 + x, 10 + y, 4); // upper L
            oled.drawDisc(40 + x, 10 + y, 4); // upper R
            oled.drawDisc(12 + x, 38 + y, 4); // lower L
            oled.drawDisc(40 + x, 38 + y, 4); // lower R
            oled.drawDisc(26 + x, 24 + y, 4); // Center
            x1 = 13;
        }
        else if (dicenr1 == 6)
        {
            oled.drawDisc(12 + x, 10 + y, 4); // upper L
            oled.drawDisc(40 + x, 10 + y, 4); // upper R
            oled.drawDisc(12 + x, 38 + y, 4); // lower L
            oled.drawDisc(40 + x, 38 + y, 4); // lower R
            oled.drawDisc(12 + x, 24 + y, 4); // center L
            oled.drawDisc(40 + x, 24 + y, 4); // center R
            x1 = 16;
        }
        if (rollMode == 2)
        {

            oled.setCursor(x1 + x, 62 + y);
            oled.print(number[dicenr1 - 1]);
        }

    } while (oled.nextPage());
    delay(100);
}

void slow()
{
    int d = 0;
    for (int i = 0; i < (random(6, 16)); i++)
    {
        randomGenerator();
        Roll();
        delay(d);
        d = d + 40;
    }

    if (BUZZ)
    {
        tone(SOUND_PIN, 800, 500);
    }
}

void randomGenerator()
{

    dicenr1 = random(1, 7);
    dicenr2 = random(1, 7);

    if (BUZZ)
    {
        tone(SOUND_PIN, 700, 80);
    }
}

void CleanScreen()
{
    if (BUZZ)
    {
        tone(SOUND_PIN, 1000, 20);
    }
    oled.firstPage();
    do
    {
    } while (oled.nextPage());
    delay(10);
}
