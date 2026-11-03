#pragma once
#include <string>

std::string find_serial_port();
int open_serial(const std::string& port_name);
void send_serial(int fd, const std::string& data);
std::string read_serial_all(int fd, int first_timeout_ms, int idle_ms);
