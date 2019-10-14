#include <iostream>

#include <QWebSocketServer>
#include <QWebSocket>
#include <QString>

#include "Server.h"
#include "Player.h"

static QString getClientInfos(const QWebSocket *peer)
{
    return QStringLiteral("%1 %2:%3").arg(peer->peerName(), peer->peerAddress().toString(),
                                              QString::number(peer->peerPort()));
}

Vivoka::Server::Server(quint16 port, std::pair<int, int> bounds,
                       unsigned int limit, bool debug, QObject *parent)
    : QObject(parent)
    , port_(port)
    , server_(new QWebSocketServer(QStringLiteral("Game Server"), QWebSocketServer::NonSecureMode, this))
    , bounds_(bounds)
    , limit_(limit)
    , debug_(debug)
{
    if (server_->listen(QHostAddress::Any, port_))
    {
        if (debug_)
            qDebug() << "Server listening on port" << port_;
        connect(server_, &QWebSocketServer::newConnection, this, &Server::onConnection);
        connect(server_, &QWebSocketServer::closed, this, &Server::onDisconnection);
    }
    else
        if (debug_)
            qDebug() << "Failed to start the server on port" << port_;
}

Vivoka::Server::~Server()
{
    server_->close();
    if (debug_)
        qDebug() << "Server closed";
}

void Vivoka::Server::onConnection()
{
    QWebSocket *client = server_->nextPendingConnection();
    if (debug_)
        qDebug() << "New connection received from" << getClientInfos(client);

    connect(client, &QWebSocket::disconnected, this, &Server::onDisconnection);

    players_ << std::make_shared<Player>(client, bounds_, limit_);
}

/*void Vivoka::Server::processTextMessage(const QString& message)
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (debug_)
        qDebug() << "Message received:" << message;
    if (client)
        client->sendTextMessage(message);
}*/

void Vivoka::Server::onGameFinished()
{

}

void Vivoka::Server::onDisconnection()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());

    if (client)
    {
        auto& player = *std::find_if(players_.begin(), players_.end(),
                                    [client](std::shared_ptr<Player>& p){ return p->getSocket() == client; });

        QString name = player->getName() ? player->getName().value() : "Anonymous";
        if (debug_)
            qDebug() << "The player" << name << getClientInfos(client) << "has disconnected";
        players_.removeAll(player);
    }
}
