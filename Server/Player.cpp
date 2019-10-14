#include <QWebSocket>

#include "Player.h"

Vivoka::Player::Player(QWebSocket* socket, std::pair<int, int> bounds,
                       unsigned int limit, QObject* parent)
    : QObject(parent)
    , name_(std::nullopt)
    , connectionTime_(QDateTime::currentDateTime())
    , socket_(socket)
    , instance_(bounds, limit)
{
    connect(socket_, &QWebSocket::textMessageReceived, this, &Player::processTextMessage);

    connect(this, &Player::newTry, &instance_, &Game::onTry);
}

Vivoka::Player::~Player()
{
    socket_->deleteLater();
}

const std::optional<QString>& Vivoka::Player::getName() const
{
    return name_;
}

const QWebSocket* Vivoka::Player::getSocket() const
{
    return socket_;
}

void Vivoka::Player::processTextMessage(const QString& message)
{
    bool isInt = false;
    int guess = message.toInt(&isInt);
    if (isInt)
        emit newTry(guess);
    else name_ = message;
}
