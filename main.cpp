#include <CPU/CPU.h>
#include <fstream>
int main() {
    std::ifstream rom;
    rom.open("/home/f33dir/projects/C++/Gameboy/rom.gbc");
    CPU * cpu = new CPU();
    cpu->loadGame(rom);
    return 0;
}
