MPU6050 mpu6050(Wire);
void setMpu6050()
{
    Wire.begin();
    mpu6050.begin();
}
class mpu
{
public:
    double currAngle = 0, readings;

    double rpm;
    bool autoCalibrate = true;
    int directionalOffset = 1;
    long prevReadings, prevTime;
    double rotationalOffset = 8;
    int interval = 10;
    bool keepHistory;
    void setup(bool history = true)
    {
        keepHistory = history;
        setMpu6050();
        if (autoCalibrate)
        {
            Serial.println("calibrating");
            calibrate();
        }
    }
    void setOffset(int off = 1)
    {
        directionalOffset = off;
    }
    double getOrignalReadings()
    {
        mpu6050.update();
        return mpu6050.getAngleZ();
    }
    double getReadings()
    {
        mpu6050.update();
        currAngle = mpu6050.getAngleZ() * directionalOffset * rotationalOffset;
        // Serial.println((String)mpu6050.getAngleZ()+", "+(String)(currAngle*2));
        // Serial.println(currAngle);
        return currAngle;
    }
    
    void calibrate()
    {
        mpu6050.calcGyroOffsets(true);
    }
} mpu;