class feedbackHandler{
    
    public:
    Direction *directions = new Direction();
    encoderFeedback *encX = new encoderFeedback();
    encoderFeedback *encY = new encoderFeedback();
    encoderFeedback *encR = new encoderFeedback();
    double offset=2.06;
    void setDirections(Direction *d)
    {
        this->directions = d;
    }
    void setup(){
        mpu.setup();
    }
    void setEncoderXYR(encoderFeedback *x,encoderFeedback *y,encoderFeedback *r){
        encX = x;
        encY = y;
        encR = r;
    }
    void compute(){
        directions -> fx = encX->getReadings();
        directions -> fy = encY->getReadings();
        // directions -> fr = 1*(encR->getReadings() - encX->getReadings());
        directions->fr=mpu.getReadings()*2;
        // Serial.println("X:"+String(directions -> fx)+"\tY:"+String(directions -> fy )+"\tR:"+String(directions -> fr));
        // Serial.println("Original: "+ (String)mpu.getOrignalReadings());
    }
    operator String(){
        return "fx="+String(directions -> fx)+" fy="+String(directions -> fy)+" fr="+String(directions -> fr);
    }

}feedback;