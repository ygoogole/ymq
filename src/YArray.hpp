//
// Created by i059483 on 10/8/15.
//

#ifndef YMQ_YARRAY_HPP
#define YMQ_YARRAY_HPP

#include <vector>

namespace ymq{

    template< int ID = 0> class YArrayItem {

    public:
        inline YArrayItem()
            :index_(-1){
        }

        inline virtual ~YArrayItem(){

        }

        inline int get_index(){
            return index_;
        }

        inline void set_index(int index){
            index_ = index;
        }

    private:
        int index_;

        YArrayItem (const YArrayItem &);
        const YArrayItem& operator= (const YArrayItem &);

    };



    template< typename T, int ID = 0> class YArray{

    private:
        typedef typename std::vector<T*>::size_type size_type_t;

    public:

        inline YArray(){

        }

        inline ~YArray(){

        }

        inline size_type_t size(){
            return items_.size();
        }

        inline bool empty(){
            return items_.empty();
        }

        // return a reference to item at specified index
        inline T* &operator [] (int index){
            return items_[index];
        }

        inline void push_back(T* item){
            if (item){
                ((item_t *)item)->set_index( (int) items_.size());
            }
            items_.push_back(item);
        }

        inline void erase (T* item){
            erase((item_t *)item->get_index());
        }

        inline void erase (size_type_t index){

            T* item = items_.back();
            if (item){
                (item_t *)item->set_index(index);
            }
            items_[index] = item;
            items_.pop_back();
        }

        inline void swap (size_type_t index1, size_type_t index2){
            if (items_[index1]){
                ((item_t *)items_[index1])->set_index(index2);
            }
            if (items_[index2]){
                ((item_t *)items_[index2])->set_index(index1);
            }

            std::swap(items_[index1], items_[index2]);
        }

        inline size_type_t get_index(T* item) {
            return (size_type_t) ((item_t *)item)->get_index();
        }

    private:

//        typedef typename std::vector<T*>::size_type size_type_t;
        typedef std::vector<T*> items_t;
        items_t items_;
        typedef YArrayItem<ID> item_t;

        YArray (const YArray &);
        const YArray& operator= (const YArray &);
    };
}



#endif //YMQ_YARRAY_HPP
