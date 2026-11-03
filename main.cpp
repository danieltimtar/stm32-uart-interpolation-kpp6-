#include "interpolation.h"
#include <iostream>
#include <vector>
#include <string>
#include "serial.h"
#include <unistd.h>

int main() {
    double a1, a2, a3;
    std::cout << "Masukkan 3 sudut: ";
    std::cin >> a1 >> a2 >> a3;

    std::vector<double> angles = {a1, a2, a3};
    std::vector<int> digital_units = interpolate_list(angles);

    std::cout << "Hasil interpolasi:\n";
    for (size_t i = 0; i < digital_units.size(); i++) {
        std::cout << "  Sudut " << angles[i] << " deg -> "
                  << digital_units[i] << '\n';
    }

    std::string data_str;
    for (size_t i = 0; i < digital_units.size(); i++) {
        data_str += std::to_string(digital_units[i]);
        if (i + 1 < digital_units.size()) data_str += ' ';
    }
    data_str += '\n';
    std::cout << "Data dikirim: " << data_str;

    try {
        std::string port_name = find_serial_port();
        std::cout << "Pakai port: " << port_name << '\n';
        int fd = open_serial(port_name);

        send_serial(fd, data_str);

        std::string reply = read_serial_all(fd, 2000, 300);
        std::cout << "Balasan STM (echo): " << reply << '\n';

        close(fd);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}