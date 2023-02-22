class MotorSpeeds{
    public:
    String a;
    int m1=0,m2=0, m3=0, m4=0;
    void display(){
        Serial.println("M1: "+String(m1)+"\tM2: "+String(m2)+"\tM3: "+String(m3)+"\tM4: "+String(m4));
    }
    void input(){
        a=Serial.readStringUntil(',');
        m1=a.toDouble();
        a=Serial.readStringUntil(',');
        m2=a.toDouble();
        a=Serial.readStringUntil(',');
        m3=a.toDouble();
        a=Serial.readStringUntil(',');
        m4=a.toDouble();
    }
};

class Direction{
    public:
    String a;
    double rfx, rfy, rfr, magnitude;
    double fx = 0, fy = 0, fr = 0;
    bool isZero = false;

    void display()
    {
        // Serial.println(fx);
        // Serial.println(String(fx)+","+String(fy)+","+String(fr));
        Serial.println("fx: "+String(fx)+"\tfy: "+String(fy)+"\tfr: "+String(fr));
    }
    void displayRatio(){
        Serial.printf("rfx: %lf, rfy: %lf, rfr: %lf, magnitude: %lf\n",rfx,rfy,rfr,magnitude);
    }
    double max(){
        if(fx>fy){
            if(fx > fr)
                return fx;
            else
                return fr;
        }
        else{
            if(fy>fr)
                return fy;
            else
                return fr;
        }

    }

    double absMax()
    {
        if (abs(fx) > abs(fy))
        {
            if (abs(fx) > abs(fr))
                return abs(fx);
            else
                return abs(fr);
        }
        else
        {
            if (abs(fy) > abs(fr))
                return abs(fy);
            else
                return abs(fr);
        }
    }
    void input(){
        a=Serial.readStringUntil(',');
        fx=a.toDouble();
        a=Serial.readStringUntil(',');
        fy=a.toDouble();
        a=Serial.readStringUntil(',');
        fr=a.toDouble();
        Serial.println((String)fx+","+(String)fy+","+(String)fr);
    }
    void process(){
        magnitude = abs(fx) + abs(fy) + abs(fr);
        // magnitude = magnitude == 0 ? 1 : magnitude;
        if(magnitude == 0)
        {
            magnitude = 1;
            isZero = true;
        }
        else{
            isZero = false;
        }
        rfx = fx/magnitude;
        rfy = fy/magnitude;
        rfr = fr/magnitude;
    }
    void invertProcess(){
        fx = rfx * magnitude;
        fy = rfy * magnitude;
        fr = rfr * magnitude;
    }

    void displayGraph(){
        Serial.printf("%lf,%lf,%lf\n",fx,fy,fr);
    }
    void displayRatioGraph(){
        Serial.printf("%lf,%lf,%lf\n",rfx,rfy,rfr);
    }
    Direction operator +(Direction a)
    {
        Direction temp;
        temp.fx=fx+a.fx;
        temp.fy=fy+a.fy;
        temp.fr=fr+a.fr;
        
        return temp;
    }
     Direction operator -(Direction a)
    {
        Direction temp;
        temp.fx=fx-a.fx;
        temp.fy=fy-a.fy;
        temp.fr=fr-a.fr;
        return temp;
    }
     Direction operator *(Direction a)
    {
        Direction temp;
        temp.fx=fx*a.fx;
        temp.fy=fy*a.fy;
        temp.fr=fr*a.fr;
        return temp;
    }
     Direction operator /(Direction a)
    {
        Direction temp;
        temp.fx=fx/a.fx;
        temp.fy=fy/a.fy;
        temp.fr=fr/a.fr;
        return temp;
    }

    Direction operator +(double a)
    {
        Direction temp;
        temp.fx=fx+a;
        temp.fy=fy+a;
        temp.fr=fr+a;
        return temp;
    }
    Direction operator -(double a)
    {
        Direction temp;
        temp.fx=fx-a;
        temp.fy=fy-a;
        temp.fr=fr-a;
        return temp;
    }
    Direction operator *(double a)
    {
        Direction temp;
        temp.fx=fx*a;
        temp.fy=fy*a;
        temp.fr=fr*a;
        return temp;
    }
    Direction operator /(double a)
    {
        Direction temp; 
        temp.fx=fx/a;
        temp.fy=fy/a;
        temp.fr=fr/a;
        return temp;
    }
    operator String(){
        return "fx="+String(fx)+" fy="+String(fy)+" fr="+String(fr);
    }
    void parseJson(JSONVar msg)
    {
        fx=msg["fx"];
        fy=msg["fy"];
        fr=msg["fr"];
        // display();
        // Serial.println("parse: "+String(msg["fx"]));
        // rfx=msg["rfx"];
        // rfy=msg["rfy"];
        // rfr=msg["rfr"];
        // magnitude=msg["magnitude"];
    }
};