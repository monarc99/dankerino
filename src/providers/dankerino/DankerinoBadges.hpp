#pragma once

#include <boost/optional.hpp>
#include <common/Singleton.hpp>

#include "common/Aliases.hpp"

#include <map>
#include <memory>
#include <vector>

namespace chatterino {

struct Emote;
using EmotePtr = std::shared_ptr<const Emote>;

class DankerinoBadges : public Singleton
{
public:
    virtual void initialize(Settings &settings, Paths &paths) override;
    DankerinoBadges();

    boost::optional<EmotePtr> getBadge(const UserId &id);

private:
    void loadDankerinoBadges();
    std::map<QString, int> badgeMap;
    std::vector<EmotePtr> emotes;
};

}  // namespace chatterino
