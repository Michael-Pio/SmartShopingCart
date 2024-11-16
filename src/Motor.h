//Created by Michael Pio @14/11/2024
class Motor{
  public:
  int speed = 0;
  int SpeedPin = 0;
  int PinA = 0;
  int PinB = 0;
  
  public:
  Motor(int PinA ,int PinB , int SpeedPin);
  void resetMotor();
  void updateMotor();
  void Forward(int speed);
  void Backward(int speed);
};
