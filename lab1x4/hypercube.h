#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include "vector.h"

template<unsigned int N> //N is the dimension of the hypercube
class Hypercube : private Vector< Hypercube<N-1> >{
  public:
    Hypercube(){
        //std::cout << "Hypercube<"<<N<<">::Hypercube()" << std::endl;
    };
    Hypercube (const std::size_t size): Vector< Hypercube<N-1> >(size,Hypercube<N-1>(size)){
        //std::cout << "Hypercube<" << N << ">::Hypercube(size_t size)" << std::endl;
        //previous size will not be taken into consideration but dimension must still be correct, ex. Hypercube<2> m(3); Hypercube<4> m2(5); m = m2[0][0]; OK
    };

    using Vector< Hypercube<N-1> >::operator[];
    //operator= will be inherited from Vector class so no need to define it
};

template<>
class Hypercube<1u> : private Vector<int>{
  public:
    Hypercube(){
        //std::cout << "Hypercube<1>::Hypercube()"<<std::endl;
    };
    Hypercube (const std::size_t i): Vector<int>::Vector(i) {
        //std::cout << "Hypercube<1>::Hypercube(size_t i)"<<std::endl;
    };

    using Vector<int>::operator[];
};
#endif
