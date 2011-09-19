#ifndef POLISHSTATE_H 
#define POLISHSTATE_H 

class PolishState : public OutputState {

  public:
    static OutputState* getInstance();

    virtual void write(AirSpace s);

};

#endif /* POLISHSTATE_H */
