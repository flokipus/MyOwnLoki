//
// Created by thranduil on 14.05.2020.
//

#ifndef LOKIMATH_MEAN_H
#define LOKIMATH_MEAN_H

#include<vector>

namespace lokimath{
    template<class T = double>
    struct mean{
        template<class InputIt>
        static T calc(InputIt first, InputIt last);
    private:
        struct mean_aux{
            mean_aux(T val_, size_t count_): val(val_), count(count_){}
            T val;
            size_t count;
        };
        static mean_aux squash(const mean_aux &m1, const mean_aux &m2){
            size_t total = m1.count + m2.count;
            T r1 = T(m1.count) / T(total);
            T r2 = T(m2.count) / T(total);
            T new_val = m1.val * r1 + m2.val * r2;
            return {new_val, total};
        }
    };

    template<class T>
    template<class InputIt>
    T mean<T>::calc(InputIt first, InputIt last) {
        auto seq_size = static_cast<size_t>(last - first);
        if(seq_size == 0)
            return T(0);

        std::vector<mean_aux> intermediate_means(seq_size, mean_aux(T(0), 0));
        auto iter = first;
        for(size_t i = 0; i < seq_size; i++){
            intermediate_means[i].val = T(*(iter));
            intermediate_means[i].count = 1;
            ++iter;
        }

        bool forward = true;
        while(seq_size > 1){
            if(forward) {
                for (size_t j = 0; j < seq_size / 2; j++) {
                    intermediate_means[j] = squash(intermediate_means[2 * j], intermediate_means[2 * j + 1]);
                }
                if (seq_size % 2 != 0) { // if count is not even, append last mean with doing nothing
                    size_t last_ind = seq_size / 2;
                    intermediate_means[last_ind] = intermediate_means[seq_size - 1];
                    forward = true;
                }
            }
            else{ // backward
                size_t offset = seq_size % 2;
                for(size_t j = 0; j < seq_size /2; j++){
                    intermediate_means[j + offset] = squash(intermediate_means[2*j + offset], intermediate_means[2*j + 1 + offset]);
                }
            }
            seq_size = (seq_size+1)/2;
            forward = not forward;
        }
        return intermediate_means[0].val;
    }
}

#endif //LOKIMATH_MEAN_H
