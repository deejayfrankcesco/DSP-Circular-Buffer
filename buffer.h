/*▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽
⎧=============================================================================⎫
⎪ Circular FIFO Float buffer oriented to DSP applications                     ⎪
⎪ Francesco Martina                                                           ⎪
⎪ Devoted to Giulia                                                           ⎪
⎪—————————————————————————————————————————————————————————————————————————————⎪
⎪ © All Right Reserved                                                        ⎪
⎩=============================================================================⎭
△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△*/

class buffer
{
private:
    
    //internal var
    float* storage;
    long size;
    long new_index,oldest_data_index;
    long n_samples;
    
    //utility functions
    long index_cycle(int long index);

public:
    buffer(long n);                             //Construct buffer with n float spaces
    long Buff_Size();                           //Return buffer size
    bool IsEmpty();
    bool IsFull();
    bool push(const float& val);                //Return false if succesfully pushed
    void fpush(const float& val);               //Force write data, overwriting oldest
    bool pop(float& data);                      //Request data, return false if there are no more data
    long N();                                   //Return number of elements

    //DSP get sample utlities (relative index extraction)
    //(0) refer to the last inserted sample, (-1) the penultimate etc.
    //In getSample you can specify an offset (for example your FIR filter
    //"latency", to refer as (0) a past sample. This permits to use both negative
    //indexes (for past samples) and positive (for future sample) referring to the FIR
    //zero time moment.
    
    //return 0 if the sample has been found, 1 if it does not exist

    bool getSample(float& data, long i, unsigned long offset);
    bool getPastSample(float& data, long i);    //only negative(past) samples are allowed in this method, same as getSample with offset zero
    
    ~buffer();
    
};
