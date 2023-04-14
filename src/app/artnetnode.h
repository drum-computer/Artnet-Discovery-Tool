#ifndef ARTNETNODE_H
#define ARTNETNODE_H

#include "qhostaddress.h"
#include "ArtNetStructs.h"
#include <memory.h>
#include <QDebug>

static int counter_{0};

class ArtNetNode
{
    // Represents a single
    // artnet node instance

public:
    ArtNetNode(const QHostAddress address, const ArtNetStructs::ArtPollReply artpoll_reply);
    ~ArtNetNode();
    const QHostAddress getIpAddress();
    const std::unique_ptr<ArtNetStructs::ArtPollReply> getArtPollReply();
private:
    QHostAddress address_;
    ArtNetStructs::ArtPollReply artpoll_reply_;

};

#endif // ARTNETNODE_H
