/*
⎧=============================================================================⎫
⎪ Circular FIFO Buffer oriented to DSP applications                           ⎪
⎪ Francesco Martina 2022                                                      ⎪
⎩=============================================================================⎭
*/

#include "buffer.h"

Buffer::Buffer(){
    size = DEFAULT_SIZE;                        //load default size
    storage = new double[size];                 //instantiate data memory spoace
    reset();                                    //reset the buffer pointers
}   
    
Buffer::Buffer(int n){ 
    size = n;                                   //load size
    storage = new double[size];                 //instantiate data memory spoace
    reset();                                    //reset the buffer pointers
}   
    
Buffer::~Buffer(){  
    delete[] storage;                           //free memory space
}

////Utility

int Buffer::Size(){
    return size;
}

bool Buffer::IsEmpty(){
    return !n_samples;
}

bool Buffer::IsFull(){
    return n_samples == size;
}

int Buffer::N(){
    return n_samples;
}

unsigned int Buffer::index_cycle(int index){    //return cyclic index in buffer (ex. if size = 3, f(1)=1, f(-1)=2, f(3)=0)
    if (index >= 0)
        return index % size;
    else
        return size + ((index + 1) % size) -1;  //be carefull, this works only if size is signed (don't modify its type to 'unsigned int')
}

////Main Methods

void Buffer::reset(){
    new_index = 0;                              //free cell is the first cell
    oldest_data_index = 0;  
    n_samples = 0;                              //no data
}   
    
void Buffer::fill_zero(){   
    reset();                                    //discard the previous buffer history
    while(!push(0));                            //push zero samples
}

bool Buffer::push(const double& val){

    //push data if the buffer is not full
    if(!IsFull()){                              //check if there is free space
        storage[new_index] = val;               //write data
        new_index = index_cycle(new_index + 1); //incement free sample space index
        n_samples++;
        return 0;
    }
    return 1;                                   //buffer is full
}

void Buffer::fpush(const double& val){

        //force the data push
        storage[new_index] = val;               //write/overwrite data
        new_index = index_cycle(new_index + 1); //incement free sample space index

        //manage the buffer status
        if(!IsFull())
            n_samples++;
        else
            oldest_data_index = index_cycle(oldest_data_index + 1); //update the tail index
}

bool Buffer::pop(double& data){

    //pop data if not empty
    if(!IsEmpty()){
        data = storage[oldest_data_index];      //request data
        oldest_data_index = index_cycle(oldest_data_index + 1); //update the tail index
        n_samples--;                            //update buffer status
        return 0;                               //return 0 on success
    }else{
        data = 0;                               //return a dummy null value in case of fail
        return 1;
    }
}

////Macro

bool Buffer::getPastSample(double& data, int i){
    
    //index check
    if((i >= 0) || (i < -n_samples)){
        data = 0;                               //return a dummy null value in case of fail
        return 1;
    }

    data = storage[index_cycle(new_index + i)]; //get the latest ith sample (with i < 0)
    return 0;
}
