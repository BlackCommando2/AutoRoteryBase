class virtualBase{
    public:
    Direction *odom = new Direction();
    Direction *feedback = new Direction();
    Motor *mx = new Motor();
    Motor *my = new Motor();
    Motor *mr = new Motor();

    virtualBase(){}
    virtualBase(Direction *_odom, Direction *_feedback){
        set(_odom,_feedback);
    }

    void set(Direction *_odom, Direction *_feedback){
        odom = _odom;
        feedback = _feedback;
        mx->virtualMode = true;
        my->virtualMode = true;
        mr->virtualMode = true;
    }

    void feedbackCompute(){
        feedback->fx = mx->getReadings();
        feedback->fy = my->getReadings();
        feedback->fr = mr->getReadings();
        feedback->process();
    }

    void apply(){
        mx->setPWM(odom->fx);
        my->setPWM(odom->fy);
        mr->setPWM(odom->fr);
    }
}vbase;