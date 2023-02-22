class odometry
{
public:
    // double m1_x = -1;
    // double m1_y = 1;
    // double m1_r = 1;
    // Direction *directions = new Direction();
    // MotorSpeeds *ms = new MotorSpeeds();
    // double m2_x = -1;
    // double m2_y = -1;
    // double m2_r = -1;

    // double m3_x = 1;
    // double m3_y = -1;
    // double m3_r = 1;

    // double m4_x = 1;
    // double m4_y = 1;
    // double m4_r = -1;
    // double max = 0;

    Direction *directions = new Direction();
    MotorSpeeds *ms = new MotorSpeeds();

    double m1_x = 1;                  // left front
    double m1_y = 1;
    double m1_r = 1;

    double m2_x = 1;                  // right front
    double m2_y = -1; 
    double m2_r = 1;//

    double m3_x = -1;                 // right rear
    double m3_y = -1;
    double m3_r = 1;

    double m4_x = -1;                 // left rear
    double m4_y = 1;
    double m4_r = 1;
    double max = 0;

    
    void setDirections(Direction *d)
    {
        this->directions = d;
    }

    void setMotors(MotorSpeeds *m){
        this->ms = m;
    }
    void manageMax(int num){
        if(abs(num) > abs(max))
            max = abs(num);
    }
    int mapFun(int m){
        return map(m,-max,max,-255,255);
    }
    void mapAll(){
        ms->m1=mapFun(ms->m1);
        ms->m2=mapFun(ms->m2);
        ms->m3=mapFun(ms->m3);
        ms->m4=mapFun(ms->m4);
    }
    void compute()
    {
        // directions->display();
        ms->m1 = (m1_x * directions->fx + m1_y * directions->fy + m1_r * directions->fr);
        max = abs(ms->m1);
        ms->m2 = (m2_x * directions->fx + m2_y * directions->fy + m2_r * directions->fr);
        manageMax(ms->m2);
        ms->m3 = (m3_x * directions->fx + m3_y * directions->fy + m3_r * directions->fr);
        manageMax(ms->m3);
        ms->m4 = (m4_x * directions->fx + m4_y * directions->fy + m4_r * directions->fr);
        manageMax(ms->m4);
        // Serial.println("max: "+String(max));
        if(max>255){
            mapAll();
        }
        // ms->display();
    }
};


class TriBaseOdometry
{
public:
    double a = (-0.5),
           b = (-0.5),
           c = 1,
           d = (-(pow(3, (0.5))) / 2),
           e = (pow(3, (0.5)) / 2),
           f = 0,
           g = 1,
           h = 1,
           i = 1,
           det = (a * e * i + b * f * g + c * d * h - c * e * g - a * f * h - b * d * i),
           max = 0;

    Direction *directions = new Direction();
    MotorSpeeds *ms = new MotorSpeeds();

    double m2_x = (e * i - f * h) / det;
    double m2_y = (h * c - i * b) / det;
    double m2_r = (b * f - c * e) / det;

    double m3_x = (g * f - d * i) / det;
    double m3_y = (a * i - g * c) / det;
    double m3_r = (d * c - a * f) / det;

    double m1_x = (d * h - g * e) / det;
    double m1_y = (g * b - a * h) / det;
    double m1_r = (a * e - d * b) / det;

    void setDirections(Direction *d)
    {
        this->directions = d;
    }

    void setMotors(MotorSpeeds *m)
    {
        this->ms = m;
    }
    void manageMax(int num)
    {
        if (abs(num) > abs(max))
            max = abs(num);
    }
    int mapFun(int m)
    {
        return map(m, -max, max, -255, 255);
    }
    void mapAll()
    {
        ms->m1 = mapFun(ms->m1);
        ms->m2 = mapFun(ms->m2);
        ms->m3 = mapFun(ms->m3);
    }
    void compute()
    {
        // directions->display();
        ms->m1 = (m1_x * directions->fx + m1_y * directions->fy + m1_r * directions->fr);
        max = abs(ms->m1);

        ms->m2 = (m2_x * directions->fx + m2_y * directions->fy + m2_r * directions->fr);
        manageMax(ms->m2);

        ms->m3 = (m3_x * directions->fx + m3_y * directions->fy + m3_r * directions->fr);
        manageMax(ms->m3);

        // Serial.println("max: "+String(max));
        if (max > 255)
        {
            mapAll();
        }
        // ms->display();
    }
} OdometryHelper;