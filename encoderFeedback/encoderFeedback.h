class encoderFeedback{
    public:
    int CPR = 720;
    double linearOffset = 0.4;
    double wheelDiametre = 58;
    long prevReadings = 0;
    long prevTime = 0;
    bool keepHistory = true;
    long readings = 0;
    long double rpm = 0;
    int interval = 10;
    UniversalEncoder *enc = new UniversalEncoder();
    encoderFeedback(bool history = true){
        keepHistory = history;
    }
    encoderFeedback(UniversalEncoder *e, bool history = true){
        
        keepHistory = history;
        setEncoder(e);
        prevTime = micros(); // not needed as never used
    }
    void setEncoder(UniversalEncoder *e){
        enc = e;
    }
    long getReadings(){
        readings = enc->getReadings();
        // // Serial.println(String(readings)+"read");
        // rpm = (((double)(readings - prevReadings) / CPR) * ((double)1000 * 60  / interval) * 0.58 * linearOffset);

        // if(!keepHistory){
        //     prevReadings = readings;
        // }
        return readings;     
    }
    void reset(){
        enc->reset();
    }
};
