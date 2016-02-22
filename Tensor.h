#ifndef MATS_H
#define MATS_H

//Interface for every Vector-type data holder
template <typename T>
class Tensor
{
    public:
        Tensor() {}
        virtual ~Tensor() {};
        virtual int* shape()  = 0;
        virtual int size() = 0;
        virtual T* point()  = 0;
        virtual void print()  = 0;
        virtual T at(int x) = 0;
};
#endif