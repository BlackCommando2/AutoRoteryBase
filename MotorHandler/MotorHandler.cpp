class MotorHandler{
    public:
    Motor *m1, *m2, *m3, *m4;
    MotorSpeeds * ms = new MotorSpeeds();
    MotorHandler(){}
    void set(Motor *_m1,Motor *_m2,Motor *_m3,Motor *_m4){
        m1 = _m1;
        m2 = _m2;
        m3 = _m3;
        m4 = _m4;
    }
    void setMotorSpeeds(MotorSpeeds *m){
        ms = m;
    }

    void apply(){
        m1->setPWM(ms->m1);
        m2->setPWM(ms->m2);
        m3->setPWM(ms->m3);
        m4->setPWM(ms->m4);
        //Serial.println(String(m1))
    }
}base;