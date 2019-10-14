#pragma once

#include <optional>

#include <QObject>
#include <QDateTime>

#include "Game.h"

QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace Vivoka
{

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QWebSocket* socket, std::pair<int, int> bounds,
                    unsigned int limit, QObject* parent = nullptr);
    ~Player();

    const std::optional<QString>& getName() const;
    const QWebSocket* getSocket() const;

signals:
    void finished();
    void newTry(int guess);

private slots:
    void processTextMessage(const QString& message);

private:
    std::optional<QString> name_;
    const QDateTime connectionTime_;

    QWebSocket* socket_;
    Game instance_;
};

}
