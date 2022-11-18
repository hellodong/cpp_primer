

#ifndef _SCREEN_H_
#define _SCREEN_H_

class Screen{
    public:
        Screen() = default;
        void some_memb() const {
            ++access_ctr;
        }
        int get_some_memb() const {
          return access_ctr;  
        }
    private:
        mutable int access_ctr = 0; // mutable 
};


#endif

