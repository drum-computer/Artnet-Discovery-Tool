#include "artnetnode.h"
#include <QDebug>

ArtNetNode::ArtNetNode(const QHostAddress address, const ArtNetStructs::ArtPollReply artpoll_reply)
{
    counter_++;
    qDebug() << "Artnet node created, counter: " << counter_;
    address_ = address;
    artpoll_reply_ = artpoll_reply;
}

ArtNetNode::~ArtNetNode()
{
    counter_--;
    qDebug() << "Artnet node deleted, counter: " << counter_;
}

const QHostAddress ArtNetNode::getIpAddress()
{
    // returns ip address of a given artnet node
    return address_;
}

const std::unique_ptr<ArtNetStructs::ArtPollReply> ArtNetNode::getArtPollReply()
{
    // returns a pointer to an
    // artpoll reply data
    // associated with this node
    return std::make_unique<ArtNetStructs::ArtPollReply>(std::move(artpoll_reply_));
}
