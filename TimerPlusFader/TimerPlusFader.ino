/*

  Original Millis() timer by James Lewis
  Updates by Brian Barlow and Chris Gergler

  Set up fader for interval timing

  - = off
  ^ = brighten
  0 = hold
  v = darken
  Example of intention: for visualization
  -------^^^^000vvvv------------^^^^000vvvv--------
*/





class Fader
{
public:
  const int minPWM = 0;
  const int maxPWM = 255; // Edit this if needed

  //Time settings
  byte pin;
  unsigned long wait_time;
  unsigned long previous_millis=0;
  bool waiting = true;




    // Fade settings
    unsigned long fade_time;
    int fade_value = 0;
    byte fade_increment = 25;
    unsigned long fade_interval = 75; // Used
    bool fade_increasing = true; // Used
    
  unsigned long delta()
  {
    return millis()-previous_millis;
  }
  void reset(){
  previous_millis=millis();
  }


    Fader(byte p, unsigned int wt, unsigned int fi, byte inc){
      wait_time = wt; //Number of millisecnds to pass
      fade_interval = fi;
      fade_increment = inc;
      pin = p;
      previous_millis=millis();
    }

    void fade_tick()
    {
      if(fade_increasing == true){
      fade_value += fade_increment;
      }
      if(fade_increasing == false){
        fade_value -= fade_increment;
      }

      if(fade_value > maxPWM) {
        fade_value = maxPWM;
        fade_increasing = false;
      }
      if(fade_value < minPWM) {
        fade_value = minPWM;
        fade_increasing = true;
        waiting = true;
      }

    }


    void Fade() {
      if(!(delta() >= fade_interval)){ return;}
      fade_tick();
      reset();
      analogWrite(pin,fade_value);
    }

    void wait(unsigned long millis)
    {
      if(waiting==false) {
        //wait_bucket = 0; 
        Fade(); 
        return; }

      //wait_bucket = (millis - previous_millis);
      if(delta() >= wait_time) {
        waiting=false;
      }
    }
};



// Pin, Wait Time, Fade steps, fade rate
Fader pin5(5, 1000, 50, 5);
Fader pin0(5,500,100,3);
///////////////////////////////////
void setup() {
  //

};

void loop() {
 pin5.wait(millis());
}
///////////////////////////////////
