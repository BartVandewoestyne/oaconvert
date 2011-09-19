#ifndef OUTPUTWRITER_H 
#define OUTPUTWRITER_H 

class OutputWriter {

  public:
    OutputWriter();

    void write(AirSpace s);

  private:
    void changeState(OutputState*);

  private:
    OutputState* _state;

};

#endif /* OUTPUTWRITER_H */
