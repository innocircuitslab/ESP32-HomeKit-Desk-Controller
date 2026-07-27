#include "HomeSpan.h"

struct OnOffOutput : Service::LightBulb {

  SpanCharacteristic *power;
  int outputPin;

  OnOffOutput(int pin) : Service::LightBulb() {

    outputPin = pin;
    power = new Characteristic::On(false);

    pinMode(outputPin, OUTPUT);
    digitalWrite(outputPin, LOW);
  }

  boolean update() override {

    digitalWrite(
      outputPin,
      power->getNewVal() ? HIGH : LOW
    );
    

    return true;
  }
};

void setup() {

  Serial.begin(115200);

  homeSpan.begin(
    Category::Lighting,
    "ESP32 Smart Desk"
  );

  // الجهاز الأول: إضاءة المكتب
  new SpanAccessory();

  new Service::AccessoryInformation();
  new Characteristic::Name("Desk Light");
  new Characteristic::Identify();

  new OnOffOutput(23);


  // الجهاز الثاني: يمثل المروحة مؤقتاً
  new SpanAccessory();

  new Service::AccessoryInformation();
  new Characteristic::Name("Desk Fan");
  new Characteristic::Identify();

  new OnOffOutput(22);
}

void loop() {
  homeSpan.poll();
}





