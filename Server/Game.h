#pragma once

#include <utility>

#include <QObject>

namespace Vivoka
{

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(std::pair<int, int> bounds, unsigned int limit,
                  QObject* parent = nullptr);

    int getNumber() const;

signals:
    void success();
    void fail();
    void lower();
    void higher();
    void invalidNumber();

public slots:
    void onTry(int guess);

private:
    const std::pair<int, int> bounds_;
    const unsigned int limit_;
    const int number_;

    unsigned int tryNumber_;
};

}
