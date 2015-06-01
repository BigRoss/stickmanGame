#ifndef TESTS_H
#define TESTS_H

#include "gamedialog.h"
#include <iostream>

class Tests
{
public:
    static bool runTests();

private:
    Tests();

    bool checkStickmanSize() const;
    bool checkAddStickmanLives() const;
    bool checkDefaultStickmanLives() const;
    bool checkStickmanXStart() const;
    bool checkStickmanSpeed() const;
    bool checkObstacleCollision() const;
    bool checkPowerUpSize() const;

    inline void updateFailCounter();
    inline bool failedTests() const;

    unsigned int m_testFailCounter;
};

#endif // TESTS_H
