#include "serial.h"
#include <libusbp.hpp>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <cstdint>
#include <stdexcept>

const uint16_t kVendorId = 0x1a86;
const uint16_t kProductId = 0x7523;

std::string find_serial_port() {
    libusbp::device device =
        libusbp::find_device_with_vid_pid(kVendorId, kProductId);
    libusbp::serial_port port(device);
    return port.get_name();
}

int open_serial(const std::string& port_name) {
    int fd = open(port_name.c_str(), O_RDWR | O_NOCTTY);
    if (fd < 0) {
        throw std::runtime_error("Gagal membuka " + port_name);
    }
    termios tty{};
    tcgetattr(fd, &tty);
    cfmakeraw(&tty);
    tty.c_cflag |= (CLOCAL | CREAD);
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    tcsetattr(fd, TCSANOW, &tty);
    tcflush(fd, TCIOFLUSH);  // buang sisa data lama
    return fd;
}

void send_serial(int fd, const std::string& data) {
    ssize_t n = write(fd, data.data(), data.size());
    if (n < 0) {
        throw std::runtime_error("Gagal menulis ke serial");
    }
    tcdrain(fd);  // tunggu sampai semua byte benar-benar terkirim
}

std::string read_serial_all(int fd, int first_timeout_ms, int idle_ms) {
    std::string result;
    int timeout = first_timeout_ms;

    while (true) {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd, &set);
        timeval tv{timeout / 1000, (timeout % 1000) * 1000};

        int ret = select(fd + 1, &set, nullptr, nullptr, &tv);
        if (ret < 0) throw std::runtime_error("Error saat menunggu data serial");
        if (ret == 0) break;  // diam selama timeout -> selesai

        char buf[256];
        ssize_t n = read(fd, buf, sizeof(buf));
        if (n < 0) throw std::runtime_error("Gagal membaca serial");
        result.append(buf, n);
        timeout = idle_ms;  // setelah data pertama, pakai batas diam yang pendek
    }

    if (result.empty()) {
        throw std::runtime_error("Timeout: tidak ada balasan dari STM");
    }
    return result;
}