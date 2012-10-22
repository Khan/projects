

void Bitzee::Bitzee()
{
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  pinMode(PIN_BMP_R, INPUT);
  pinMode(PIN_BMP_F, INPUT);

  pinMode(PIN_AUD_R, OUTPUT);
  pinMode(PIN_AUD_P, OUTPUT);

  pinMode(PIN_CAM_PWR, OUTPUT);
  pinMode(PIN_CAM_IMG, OUTPUT);
  
  pinMode(PIN_MTR_EN, OUTPUT);
  pinMode(PIN_MTR_L1, OUTPUT);
  pinMode(PIN_MTR_L2, OUTPUT);
  pinMode(PIN_MTR_L3, OUTPUT);
  pinMode(PIN_MTR_L4, OUTPUT);

  irrecv.enableIRIn(); // Start the receiver
}

void Bitzee::forward() { }
void Bitzee::forwardLeft() { }
void Bitzee::forwardRight() { }
void Bitzee::backward() { }
void Bitzee::backwardLeft() { }
void Bitzee::backwardRight() { }
void Bitzee::coast() { }
void Bitzee::coastLeft() { }
void Bitzee::coastRight() { }
void Bitzee::stop() { }
void Bitzee::stopLeft() { }
void Bitzee::stopRight() { }
void Bitzee::speed(int n) { }
void Bitzee::accelerate(int n) { }
void Bitzee::decelerate(int n) { }
void Bitzee::blinkLEDs(int t, int r, int g, int b) { }
void Bitzee::recordImage() { }
void Bitzee::recordSound() { }
void Bitzee::playSound() { }

// Calibrating Bit-zee's motors
void Bitzee::calibrate(int[] values) { }

