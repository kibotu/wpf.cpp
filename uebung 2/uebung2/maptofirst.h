#ifndef MAPTOFIRST_H
#define MAPTOFIRST_H

#include <utility>

namespace MyMap {

    template<typename T1, typename T2, template<typename> class Op >
    class MapToFirst{
        Op<T1> op;
        public:
            MapToFirst(){
                op = Op<T1>();
            }
            bool operator() (const std::pair<T1, T2> &t1, const  std::pair<T1, T2> &t2){
                return op(t1.first, t2.first);
            }
    };
}
#endif // MAPTOFIRST_H
