#include "ScoreSystem.h"

ScoreSystem::ScoreSystem()
    : _score(0),
      _hits(0),
      _attempts(0)
{}

void ScoreSystem::registerHit() {
    _hits++;
    _attempts++;
    _score += 10;

    print();
}

void ScoreSystem::registerMiss() {
    _attempts++;
    _score -= 2;

    print();
}

int ScoreSystem::getScore() const {
    return _score;
}

int ScoreSystem::getHits() const {
    return _hits;
}

int ScoreSystem::getAttempts() const {
    return _attempts;
}

void ScoreSystem::print() const {
    std::cout
        << "[SCORE] "
        << "Score: " << _score
        << " | Hits: " << _hits
        << " | Attempts: " << _attempts
        << std::endl;
}
