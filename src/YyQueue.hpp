//
// Created by i059483 on 8/29/15.
//

#ifndef YMQ_YYQUEUE_HPP
#define YMQ_YYQUEUE_HPP


#include <assert.h>
#include <stdlib.h>
#include "YAtomicPtr.hpp"

namespace ymq {


    template<typename T, int N>
    class YyQueue {

    public:

        inline YyQueue()
                : begin_pos_(0),
                  end_pos_(0),
                  back_pos_(0) {

            begin_chunk_ = (Chunk *) malloc(sizeof(Chunk));
            assert(begin_chunk_ != NULL);
            end_chunk_ = begin_chunk_;
            back_chunk_ = NULL;

        }

        inline ~YyQueue(){
            // destroy the queue;

            while(1){

                if( end_chunk_ == begin_chunk_){
                    free(end_chunk_);
                    break;
                } else{
                    Chunk* c = end_chunk_->pprev_;
                    free(end_chunk_);
                    end_chunk_ = c;
                }

                Chunk* c = spare_chunk_.xchg(NULL);
                if(c){
                    free(c);
                }
            }
        }

        // return reference to first object
        inline T &front() {

            return begin_chunk_->values[begin_pos_];
        }

        // return reference to last object
        inline T &back() {

            return end_chunk_->values[end_pos_];
        }

        inline void push() {

            back_chunk_ = end_chunk_;
            back_pos_ = end_pos_;

            if (++end_pos_ != N)
                return;

            // this chunk is full, back_pos_ is N-1, end_pos_ is N
            // check if spare chunk is available to be re-used

            Chunk* sc = spare_chunk_.xchg(NULL);
            if (sc){

                end_chunk_->pnext_ = sc;
                sc->pprev_ = end_chunk_;

            }else {
                Chunk *new_chunk = (Chunk *) malloc(sizeof(Chunk));
                assert(new_chunk != NULL);
                end_chunk_->pnext_ = new_chunk;
                new_chunk->pprev_ = end_chunk_;
            }

            end_chunk_ = end_chunk_->pnext_;
            end_pos_ = 0;

        }

        inline void pop(){

            if(++begin_pos_ == N - 1){
                // this chunk is empty

                Chunk* c = begin_chunk_;
                begin_chunk_ = c->pnext_;
                begin_chunk_->pprev_ = NULL;
                begin_pos_ = 0;

                Chunk* sc = spare_chunk_.xchg(c);
                if (sc){
                    free(sc);
                }


            }
        }

        // undo push, caller should destroy the object
        inline void unpush(){

            if(--back_pos_ < 0){
                back_pos_ = N - 1;
                back_chunk_ = back_chunk_->pprev_;
            }

            if(end_pos_){
                --end_pos_;
            } else{
                end_pos_ = N - 1;
                end_chunk_ = end_chunk_->pprev_;
                free(end_chunk_->pnext_);
                end_chunk_->pnext_ = NULL;
            }

        }

    private:

        struct Chunk {

            T values[N];
            Chunk *pprev_;
            Chunk *pnext_;
        };

        Chunk *begin_chunk_; // point to first chuck,
        Chunk *end_chunk_;  // point to last chuck, initially equal to begin chunck, should ahead of back chunk
        Chunk *back_chunk_; // point to chuck after begin chuck, initially NULL

        int begin_pos_;
        int end_pos_; // always ahead of back_pos_1 by 1 position, the position after push back
        int back_pos_;

        //spare chunk, most recent freed chunk
        YAtomicPtr<Chunk> spare_chunk_;


        YyQueue(const YyQueue &);

        const YyQueue &operator=(const YyQueue &);
    };

}
#endif //YMQ_YYQUEUE_HPP
