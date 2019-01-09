/*▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽
⎧=============================================================================⎫
⎪ Circular FIFO Float buffer oriented to DSP applications                     ⎪
⎪ Francesco Martina                                                           ⎪
⎪—————————————————————————————————————————————————————————————————————————————⎪
⎪ © All Right Reserved                                                        ⎪
⎩=============================================================================⎭
△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△*/

#include "buff.h"

//Constructors
buffer::buffer(){
    size = DEFAULT_SIZE;                    //load default size
    storage = new float[size];              //instantiate data memory spoace
    new_index = 0;                          //free cell is the first cell
    oldest_data_index = 0;
    n_samples = 0;                          //no data
}

buffer::buffer(long n){
    size = n;                               //load size
    storage = new float[size];              //instantiate data memory spoace
    new_index = 0;                          //free cell is the first cell
    oldest_data_index = 0;
    n_samples = 0;                          //no data    
}

/////////////////// Function
long buffer::Buff_Size(){
    return size;
}

bool buffer::IsEmpty(){
    if(!n_samples) return 1; else return 0;
}

bool buffer::IsFull(){
    if(n_samples == size) return 1; else return 0;
}

bool buffer::push(const float& val){
    if(!IsFull()){                          //check if there is free space
        storage[new_index] = val;           //write data
        new_index = (new_index+1)%size;     //incement free sample space index
        n_samples++;
        return 0;
    }else return 1;                         //buffer is full
}

void buffer::fpush(const float& val){
        //force push
        storage[new_index] = val;           //overwrite data
        new_index = (new_index+1)%size;     //incement "free" (overwrite) space index
        if(!IsFull())
            n_samples++;                    //if it was full it will remain full
        else
            oldest_data_index = (oldest_data_index+1)%size; //update the old data index to preserve order
}

bool buffer::pop(float& data){
    if(!IsEmpty()){
        data = storage[oldest_data_index];  //request data
        oldest_data_index = (oldest_data_index+1)%size;
        n_samples--;
        return 1;                           //return true on success
    }else{
        //data = 0;
        return 0;
    } 
}

long buffer::N(){
    return n_samples;
}

long buffer::index_cycle(int long index){                   //return cyclic index in buffer (ex. if size = 3, f(1)=1, f(-1)=2, f(3)=0)
    if (index >= 0)
        return index % size;
    else
        return size - ((-index) % size);
}

bool buffer::getPastSample(float& data, long i){
    return getSample(data, i, 0);
}

bool buffer::getSample(float& data, long i, unsigned long offset){
    if(i<(-n_samples+1+offset) && i>offset)
        return 1;                                           //the sample does not exist
    data = storage[index_cycle((new_index-1+i-offset))];    //return the relative indexed sample
    return 0;
}
///////////////////

//Destructor
buffer::~buffer(){
    delete[] storage;                       //free memory space
}
