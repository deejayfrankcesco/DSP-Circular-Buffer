/*
⎧=============================================================================⎫
⎪ Circular FIFO Buffer oriented to DSP applications                           ⎪
⎪ Francesco Martina 2022                                                      ⎪
⎩=============================================================================⎭
*/

#ifndef BUFFER_H
#define BUFFER_H

#define DEFAULT_SIZE  10;

class Buffer
{
private:

    double* storage;

    //note.
    //int types are here used since specific methods (see index_cycle) cannot exploit the unsigned int
    //range without going for the long type. (int range is enough for most of the applications)

    int size;
    int n_samples;
    int new_index, oldest_data_index;
    
    //internal utility
    unsigned int index_cycle(int index);

public:

    Buffer();
    Buffer(int n);                               //Construct buffer with n double type samples
    ~Buffer();

    ////Utility
    int Size();                                  //Return buffer size
    bool IsEmpty();
    bool IsFull();
    int N();                                     //Return number of stored samples

    ////Main Methods
    void reset();                                //Empty the buffer (resets the buffer pointers)
    void fill_zero();                            //Fill the buffer with null (zero) samples
    bool push(const double& val);                //Return false if succesfully pushed
    void fpush(const double& val);               //Force write data, overwriting oldest
    bool pop(double& data);                      //Request data, return false if there are no more data

    ////Macro
    //return the x[k] * z^i samples (only negative i are allowed)
    //The last pushed sample is getPastSample(double& sample, -1).
    
    bool getPastSample(double& data, int i);
    
};

#endif
