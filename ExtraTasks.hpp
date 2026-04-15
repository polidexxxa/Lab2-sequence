#ifndef _EXTRATASKS_HPP_
#define _EXTRATASKS_HPP_

//задачи п-1, п-6, п-8

#include "Exceptions.hpp"
#include "ArraySequence.hpp"
#include <iostream>

template<typename T> 
struct MinMaxAvgResult {
    T min;
    T max;
    double avg;
    int count;

    void print() const {
        std::cout << "Min: " << min << ", Max: " << max 
                  << ", Avg: " << avg << " (of " << count << " elements)" << std::endl;
    }
};

//п-1
template<typename T>
class Task_MinMaxAvg {
public:
    static MinMaxAvgResult<T> compute(const ArraySequence<T>& seq) {
        if (seq.GetLength() == 0) {
            throw EmptyContainerException("Cannot compute min/max/avg from empty sequence");
        }
        
        T first = seq.GetFirst();
        
        MinMaxAvgResult<T> result;

        result = const_cast<ArraySequence<T>&>(seq).template Reduce<MinMaxAvgResult<T>>(
            MinMaxAvgResult<T>{first, first, 0.0, 0},
            [](const MinMaxAvgResult<T>& acc, const T& x) -> MinMaxAvgResult<T> {
                return MinMaxAvgResult<T>{
                    (x < acc.min) ? x : acc.min,
                    (x > acc.max) ? x : acc.max,
                    acc.avg + static_cast<double>(x),          //avg временно хранит сумму
                    acc.count + 1
                };
            }
        );
        
        if (result.count > 0) {
            result.avg = result.avg / result.count;
        }
        
        return result;
    }
  
};


//п-6
template<typename T> 
class Task_MovingAverage {
public:
    static ArraySequence<double>* computeTripleAverage(const Sequence<T>& seq) {
        int n = seq.GetLength();
        
        if (n == 0) {
            return new ArraySequence<double>();
        }
        
        double* result = new double[n];
        
        if (n == 1) {
            result[0] = static_cast<double>(seq.Get(0));
        } 
        else if (n == 2) {
            result[0] = (static_cast<double>(seq.Get(0)) + seq.Get(1)) / 2.0;
            result[1] = (static_cast<double>(seq.Get(0)) + seq.Get(1)) / 2.0;
        } 
        else {
            result[0] = (static_cast<double>(seq.Get(0)) + seq.Get(1)) / 2.0;
            
            for (int i = 1; i < n - 1; i++) {
                double sum = static_cast<double>(seq.Get(i-1)) + seq.Get(i) + seq.Get(i+1);
                result[i] = sum / 3.0;
            }
            
            result[n-1] = (static_cast<double>(seq.Get(n-2)) + seq.Get(n-1)) / 2.0;
        }
        
        auto* res = new ArraySequence<double>(result, n);
        delete[] result;
        return res;
    }
};


//п-8
template<typename T>
class Task_ReflectionSum {
public:
    static ArraySequence<T>* computeFullReflection(const Sequence<T>& seq) {
        int n = seq.GetLength();
        
        int* indices = new int[n];
        for (int i = 0; i < n; i++) indices[i] = i;
        ArraySequence<int> indexSeq(indices, n);
        delete[] indices;
        
        auto* result = indexSeq.Map<T>(
            [&seq, n](int i) -> T {
                return seq.Get(i) + seq.Get(n - 1 - i);
            }
        );
        
        return dynamic_cast<ArraySequence<T>*>(result);
    }
};



#endif //_EXTRATASKS_HPP_
