void noneFunction(){

}
class PIDDirections
{
public:
    Direction *target = new Direction();
    Direction *_feedback = new Direction();
    Direction *output = new Direction();
    Direction *UserIn = new Direction();
    long interval = 10000;
    long prevtime = 0;
    double xKp = 0.1, xKi = 0, xKd = 0;
    double yKp = 0.1, yKi = 0, yKd = 0;
    double rKp = 0.9, rKi = 0, rKd = 0;
    PID *fxPID, *fyPID, *frPID;
    bool keepHistory = true;
    bool continueRotation = false;
    long prevX = 0, prevY = 0, prevR = 0;
    double rotationPerCount = 0;
    double X_offset=1;//0.5
    double y_offset=1;
    double r_offset=1;
    void (*updateInput)() = noneFunction;
    PIDDirections() {}
    PIDDirections(Direction *in, Direction *out, Direction *setp)
    {
        set(in, out, setp);
    }
    void attachInputUpdate(void (*_updateInput)()){
        updateInput = _updateInput;
    } 
    void set(Direction *in, Direction *out, Direction *setp)
    {
        UserIn = setp;
        _feedback = in;
        output = out;
    }

    void modifyInput(){
        target->fx = UserIn->fx * X_offset;
        target->fy = UserIn->fy * y_offset;
        target->fr = UserIn->fr * r_offset;
    }

    void setup()
    {    
        fxPID = new PID(&_feedback->fx, &output->fx, &target->fx, xKp, xKi, xKd, DIRECT);
        fyPID = new PID(&_feedback->fy, &output->fy, &target->fy, yKp, yKi, yKd, DIRECT);
        frPID = new PID(&_feedback->fr, &output->fr, &target->fr, rKp, rKi, rKd, DIRECT);
        fxPID->SetMode(AUTOMATIC);
        fxPID->SetSampleTime(1);

        fyPID->SetMode(AUTOMATIC);
        fyPID->SetSampleTime(1);

        frPID->SetMode(AUTOMATIC);
        frPID->SetSampleTime(1);

        fxPID->SetOutputLimits(-100, 100);
        fyPID->SetOutputLimits(-100, 100);
        frPID->SetOutputLimits(-100, 100);
    }

    void compute()
    {
        modifyInput();
        fxPID->Compute();
        fyPID->Compute();
        frPID->Compute();
    }
}PID_xyr;