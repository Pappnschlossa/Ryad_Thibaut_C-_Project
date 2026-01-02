//
// Created by ryadg on 31/12/2025.
//

#ifndef C_PROJECT_ARRAY_H
#define C_PROJECT_ARRAY_H

#include <iostream>

template<typename T>
class Array {
public:
    Array(int size) : size(size) {
        array = new T*[size] ;
    }


    void add(T& element) {
        if (fill < size) {
            array[fill] = new T( element );
            fill += 1 ;
        }
    }
    void add(const T& element) {
        if (fill < size) {
            array[fill] = new T( element ) ;
            fill += 1 ;
        }
    }

    void remove(T& element) {

        for (int i = 0 ; i < fill ; i++) {
            if (array[i] == &element ) {
                removeIndex(i) ;
            }
        }
    }

    void remove(const T& element) {

        for (int i = 0 ; i < fill ; i++) {
            if (array[i] == &element ) {
                removeIndex(i) ;
            }
        }
    }

    int getFill() const {
        return fill ;
    }

    void print() {
        std :: cout << "[ " ;
        for (int i = 0 ; i < fill ; i++) {
            std :: cout << array[i]->print() << " " ;
        }
        std :: cout << "] \n" ;
    }
    const T* operator[](int ind) const {
        if (ind >= 0 && ind < fill) {
            return array[ind] ;
        }
        return nullptr;
    }
    T* operator[](int ind) {
        if (ind >= 0 && ind < fill) {
            return array[ind] ;
        }
        return nullptr;
    }

    void swap(int i, int j) {
        if (i < fill && j < fill) {
            T* tmp = array[i] ;
            array[i] = array[j] ;
            array[j] = tmp ;
        }
    }

    void shuffle(int nbSwaps) {
        if (nbSwaps > 0){
            srand(time(NULL));
            for ( int i = 0 ; i < nbSwaps ; i++) {

                int a = rand() % fill ;
                int b = rand() % fill ;
                swap( a, b) ;
            }
        }
    }

private:
    T** array ;
    int fill  = 0;
    int size ;

    void removeIndex(int ind) {

        if (ind < fill) {
            for (int i = ind; i < fill ; i++) {
                array[i] = array[i + 1] ;
            }
        }

        fill -= 1 ;
    }


};



#endif //C_PROJECT_ARRAY_H