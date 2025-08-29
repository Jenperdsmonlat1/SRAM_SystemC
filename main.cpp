#include <iostream>
#include <systemc.h>
#include "modules/sram_block.h"


int sc_main(int argc, char **argv) {

    if (argc < 4) {
        std::cout << "Erreur, pas assez d'arguments." << std::endl;
        std::cout << "Format: ./main <AddrIn> <EN> <WE> <DIn>" << std::endl;
        return EXIT_FAILURE;
    }

    SRAM sram("SRAM");

    sc_signal<bool> en, we;
    sc_signal<sc_uint<8>> addr_in;
    sc_signal<sc_uint<32>> d_in, d_out;

    sram.en(en);
    sram.we(we);
    sram.addr_in(addr_in);
    sram.w_data(d_in);
    sram.r_data(d_out);

    addr_in.write(atoi(argv[1]));
    en.write(atoi(argv[2]));
    we.write(atoi(argv[3]));
    d_in.write(atoi(argv[4]));

    sc_start(10, SC_NS);

    we.write(0);
    sc_start(10, SC_NS);

    std::cout << "Address input: " << addr_in.read() << std::endl;
    std::cout << "EN flag: " << en.read() << std::endl;
    std::cout << "WE flag: " << we.read() << std::endl;
    std::cout << "D_out value: " << d_out.read() << std::endl;

    return EXIT_SUCCESS;
}