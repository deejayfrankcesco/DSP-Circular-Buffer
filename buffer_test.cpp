/*
⎧=============================================================================⎫
⎪ Circular FIFO Buffer oriented to DSP applications                           ⎪
⎪ Very Basic! Testing Code                                                    ⎪
⎪ Francesco Martina 2022                                                      ⎪
⎩=============================================================================⎭
*/

#include <iostream>
#include "buffer.h"

using namespace std;

int main()
{
    Buffer b(3);
    cout << "Buff Size: " << b.Size() << "\n";

    //push data
    for(int i=0;i<5;i++)
        cout << "Inserting data: " << i << " Returning: " << b.push(i) << "\n";

    cout << "Elements: " << b.N() << "\n\n";

    //popping data
    for(int i=0;i<5;i++){
        double data;
        int ret = b.pop(data);
        cout << "Pop data: " << data << " Returning: " << ret << "\n";
    }

    cout << "Elements: " << b.N() << "\n\n";

    //force push data
    for(int i=0;i<5;i++){
        cout << "Inserting data (Force): " << i << "\n";
        b.fpush(i);
    }

    cout << "Elements: " << b.N() << "\n\n";

    //popping data
    for(int i=0;i<5;i++){
        double data;
        int ret = b.pop(data);
        cout << "Pop data: " << data << " Returning: " << ret << "\n";
    }

    cout << "Elements: " << b.N() << "\n\n";

    //force push data
    for(int i=0;i<10;i++){
        cout << "Inserting data (Force): " << i << "\n";
        b.fpush(i);
    }

    cout << "Elements: " << b.N() << "\n\n";

    //reference data
    for(int i=0;i<5;i++){
        double data;
        int ret = b.getPastSample(data, -i);
        cout << "Read data: (i = " << -i << "), value: "  << data << " Returning: " << ret << "\n";
    }

    cout << "Elements: " << b.N() << "\n\n";

    b.fill_zero();
    //popping data
    for(int i=0;i<5;i++){
        double data;
        int ret = b.pop(data);
        cout << "Pop data: " << data << " Returning: " << ret << "\n";
    }

    return 0;
}
