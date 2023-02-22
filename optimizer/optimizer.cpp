double pow2[30];
class optimizer {
    Direction *line = new Direction();
    Direction *point = new Direction();
  public:
    int maxJump = 17, minJump = -6;
    void set(Direction *_line, Direction *_point) {
      line = _line;
      point = _point;
      for (int i = minJump; i <= maxJump; i++) {
        pow2[i - minJump] = pow(2, i);
      }
    }
    optimizer() {}
    optimizer(Direction *_line, Direction *_point) {
      set(_line, _point);
    }

    double indexCost(double index) {
      return pow(pow(((line->rfx * index) - point->fx), 2) +
                 pow(((line->rfy * index) - point->fy), 2) +
                 pow(((line->rfr * index) - point->fr), 2), 0.5) ;
    }
    bool indexDirection(double index) {
      return indexCost(index) - indexCost(index + 0.01) > 0;
    }
    double optimize(double start = 0) {
      line->process();
      double index = start;
      bool dir = indexDirection(index);
      bool ndir = dir;
      for (int jump = maxJump; jump >= minJump;)
      {
        dir = ndir;
        index = index + (dir ? 1 : -1) * pow2[jump - minJump];
        ndir = indexDirection(index);
        if (dir != ndir)
        {
          jump -= 1;
        }
      }
      return index;
    }

    void minimize() {
      point->magnitude = -1 * optimize();
      point->rfx = line->rfx;
      point->rfy = line->rfy;
      point->rfr = line->rfr;

      double fx = point->fx;
      double fy = point->fy;
      double fr = point->fr;

      point->invertProcess();

      point->fx += fx;
      point->fy += fy;
      point->fr += fr;
    }
};