#include <random>

#include "Game.h"

static int getRandomInt(const std::pair<int, int>& range)
{
    std::random_device r;
    std::mt19937 engine(r());
    std::uniform_int_distribution<int> gen(range.first, range.second);
    return gen(engine);
}

Vivoka::Game::Game(std::pair<int, int> bounds, unsigned int limit, QObject* parent)
    : QObject(parent)
    , bounds_(bounds)
    , limit_(limit)
    , number_(getRandomInt(bounds_))
{
}

int Vivoka::Game::getNumber() const
{
    return number_;
}

void Vivoka::Game::onTry(int guess)
{
    if (guess > bounds_.second || guess < bounds_.first)
        emit invalidNumber();

    ++tryNumber_;

    if (guess == number_)
        emit success();
    else if (tryNumber_ >= limit_)
        emit fail();
    else if (guess > number_)
        emit lower();
    else
        emit higher();
}
