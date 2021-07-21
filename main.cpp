#include <CPU/CPU.h>
#include <fstream>
int main() {
    std::ifstream rom;
    rom.open("../rom.gbc");
    CPU * cpu = new CPU();
    cpu->loadGame(rom);
    uint8_t v = 0xFF;
    v++;
    return 0;
}
