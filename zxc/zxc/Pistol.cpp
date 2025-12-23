#include "Pistol.h"
#include <iostream>

Pistol::Pistol(int initialAmmo) : ammo(initialAmmo) {}

void Pistol::shoot() {
    if (ammo > 0) {
        std::cout << "Бах!" << std::endl;
        ammo--;
    }
    else {
        std::cout << "Клац!" << std::endl;
    }
}

int Pistol::getAmmo() const {
    return ammo;
}


Automatic::Automatic() : Pistol(30), rateOfFire(30), maxAmmo(30) {}

Automatic::Automatic(int maxCapacity) : Pistol(maxCapacity), rateOfFire(maxCapacity / 2), maxAmmo(maxCapacity) {}

Automatic::Automatic(int maxCapacity, int fireRate) : Pistol(maxCapacity), rateOfFire(fireRate), maxAmmo(maxCapacity) {}

int Automatic::getRateOfFire() const {
    return rateOfFire;
}

void Automatic::shoot() {
    for (int i = 0; i < rateOfFire && ammo > 0; i++) {
        std::cout << "Бах!" << std::endl;
        ammo--;
    }
    if (ammo == 0) {
        std::cout << "Клац!" << std::endl;
    }
}

void Automatic::shootForSeconds(int seconds) {
    int shots = seconds * rateOfFire;
    for (int i = 0; i < shots && ammo > 0; i++) {
        std::cout << "Бах!" << std::endl;
        ammo--;
    }
    if (ammo == 0) {
        std::cout << "Клац!" << std::endl;
    }
}
