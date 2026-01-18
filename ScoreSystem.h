//
// Created by stanislaw on 18.01.2026.
//

#ifndef PROJEKT3D_SCORESYSTEM_H
#define PROJEKT3D_SCORESYSTEM_H

#include <iostream>

class ScoreSystem {
public:
    ScoreSystem();

    void registerHit();
    void registerMiss();

    int getScore() const;
    int getHits() const;
    int getAttempts() const;

    void print() const;

private:
    int _score;
    int _hits;
    int _attempts;
};

#endif //PROJEKT3D_SCORESYSTEM_H