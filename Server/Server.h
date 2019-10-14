#pragma once

#include <utility>
#include <vector>
#include <memory>

#include <QObject>
#include <QList>

#include "Game.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace Vivoka
{

class Player;

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(quint16 port, std::pair<int, int> bounds,
                    unsigned int limit, bool debug = false, QObject* parent = nullptr);
    ~Server();

signals:
    void closed();

private slots:
    void onConnection();
    void processTextMessage(const QString& message);
    void onGameFinished();
    void onDisconnection();

private:
    const unsigned int port_;
    QWebSocketServer* server_;
    QList<std::shared_ptr<Player>> players_;

    const std::pair<int, int> bounds_;
    const unsigned int limit_;

    bool debug_;
};

}
