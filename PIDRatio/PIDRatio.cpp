class PIDRatio
{
public:
    Direction *target = new Direction();
    Direction *prevUserIn = new Direction();
    Direction *currUserIn = new Direction();
    Direction *prevFeedback = new Direction();
    Direction *currentFeedback = new Direction();
    Direction *speedReferenceFeedback = new Direction();
    Direction *_feedback = new Direction();
    Direction *t_feedback = new Direction();
    Direction *traveled = new Direction();
    Direction *output = new Direction();
    Direction *UserIn = new Direction();
    optimizer *opt = new optimizer();
    double dist = 0, brakeOut = 0, zero = 0;
    bool braking = false;
    double xKp = 1.0, xKi = 0, xKd = 0;
    double yKp = 1.0, yKi = 0, yKd = 0;
    double rKp = 3.0, rKi = 0, rKd = 0;//3.0
    double brakeKp = 4.0, brakeKi = 0.1, brakeKd = 0;
    PID *fxPID, *fyPID, *frPID, *brake;

    PIDRatio() {}
    PIDRatio(Direction *in, Direction *out, Direction *setp)
    {
        set(in, out, setp);
    }
    void set(Direction *in, Direction *out, Direction *setp)
    {
        UserIn = setp;
        _feedback = in;
        output = out;
        opt->set(currUserIn, currentFeedback);
    }
    void setup()
    {
        fxPID = new PID(&currentFeedback->fx, &output->fx, &target->fx, xKp, xKi, xKd, DIRECT);
        fyPID = new PID(&currentFeedback->fy, &output->fy, &target->fy, yKp, yKi, yKd, DIRECT);
        frPID = new PID(&currentFeedback->fr, &output->fr, &target->fr, rKp, rKi, rKd, DIRECT);
        brake = new PID(&dist, &brakeOut, &zero, brakeKp, brakeKi, brakeKd, DIRECT);
        fxPID->SetMode(AUTOMATIC);
        fxPID->SetSampleTime(1);

        fyPID->SetMode(AUTOMATIC);
        fyPID->SetSampleTime(1);

        frPID->SetMode(AUTOMATIC);
        frPID->SetSampleTime(1);

        brake->SetMode(AUTOMATIC);
        brake->SetSampleTime(1);

        fxPID->SetOutputLimits(-255, 255);
        fyPID->SetOutputLimits(-255, 255);
        frPID->SetOutputLimits(-255, 255);
        brake->SetOutputLimits(-255, 255);
    }
    void compute()
    {
            // UserIn->display();
            UserIn->process();

            // Braking Logic
            if (UserIn->isZero && !prevUserIn->isZero)// Detecting Brake
            {
                prevUserIn->magnitude = 1;
                prevUserIn->invertProcess();
                *currUserIn = *prevUserIn;
                braking = true;
            }
            else
            {
                //Reducing User Input
                currUserIn->fx = UserIn->fx / 1;
                currUserIn->fy = UserIn->fy / 1;
                currUserIn->fr = UserIn->fr / 1;
                braking = false;  
            }
            *prevUserIn = *currUserIn;


            *t_feedback = *_feedback / 8; // test this
            *currentFeedback = *t_feedback - *prevFeedback;
            *speedReferenceFeedback = *currentFeedback;
            currUserIn->process();
            if (!currUserIn->isZero)
            {
                opt->minimize();
            }
            currUserIn->process();
            
            *prevFeedback=*t_feedback - *currentFeedback;
            if(braking){
                *traveled = *speedReferenceFeedback - *currentFeedback;
                dist = pow(pow((speedReferenceFeedback->fx - currentFeedback->fx), 2) +
                    pow((speedReferenceFeedback->fy - currentFeedback->fy), 2) +
                    pow((speedReferenceFeedback->fr - currentFeedback->fr), 2), 0.5) * 2;// * 2
                brake->Compute();
                traveled->process();
                traveled->magnitude = brakeOut;
                traveled->invertProcess();
                *currUserIn = *traveled;
            }
            *target=*currUserIn;
            fxPID->Compute();
            fyPID->Compute();
            frPID->Compute(); 
    }
} PID_ratio;