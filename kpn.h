#ifndef KPN_H
#define KPN_H

#include <systemc.h>
#include <sstream>


SC_MODULE(kpn)
{
  private:
    sc_fifo<int> a, b, c, d;
    //sc_out<int> e;

    void add(){
        while(true){
            b.write(a.read() + c.read());
        }
    }

    void split(){
        int cnt_ = 0;
        while(true) {
            int input_ = b.read();
            a.write(input_);
            d.write(input_);
            std::cout << "Output e: " << input_ << std::endl;
            if (cnt_++ >= 10) sc_stop();
        }
    }

    void delay(){
        while(true){
            c.write(d.read());
        }
    }

  public:
    SC_CTOR(kpn): a("a"), b("b"), c("c"), d("d")//, e("e")
    {
        // NOTE: Default fifo size of 16

        // Initial values
        b.write(1);
        c.write(0);

        SC_THREAD(add);
        SC_THREAD(split);
        SC_THREAD(delay);
    }
};

#endif // KPN_H
