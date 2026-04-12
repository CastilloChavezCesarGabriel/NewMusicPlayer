#ifndef CHANNEL_H
#define CHANNEL_H

#include "IPathVisitor.h"
#include "../event/ITrackListener.h"

class Channel final : public IPathVisitor {
private:
    ITrackListener& tracks_;

public:
    explicit Channel(ITrackListener& tracks);
    void visit(const std::string& path) override;
};

#endif //CHANNEL_H