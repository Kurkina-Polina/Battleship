#include <iostream>
#include "Ship.h"
#include "Exceptions.h"
#include <memory>
#include <vector>
ShipSegment::ShipSegment() :state(SegmentState::Intact){}
SegmentState ShipSegment::GetState()const {
    return state;
}
SegmentState ShipSegment::Hit() {
    if (state == SegmentState::Intact) {
        state = SegmentState::Damaged;
    }
    else if (state == SegmentState::Damaged) {
        state = SegmentState::Destroyed;

    }
    return GetState();
    

}

ShipSegment  ShipSegment::from_json(const nlohmann::json& j) {
    ShipSegment segment;
    std::string stateStr = j["state"].get<std::string>();
    if (stateStr == "Intact") { segment.SetState(SegmentState::Intact); }
    else if (stateStr == "Damaged") { segment.SetState(SegmentState::Damaged); }
    else if (stateStr == "Destroyed") { segment.SetState(SegmentState::Destroyed); }
    else { std::cout << "problem in fromjson in segment"; }

    return segment;
}

nlohmann::json ShipSegment::to_json() const {
    nlohmann::json j;
    switch (state) {
    case SegmentState::Intact: j["state"] = "Intact"; break;
    case SegmentState::Damaged: j["state"] = "Damaged"; break;
    case SegmentState::Destroyed: j["state"] = "Destroyed"; break;
    }
    return j;
}


Ship::Ship(int length_, Orientation orientation_ = Orientation::Horizontal) :
    orientation(orientation_) {
    if (length_ < 1 || length_ > 4) {
        throw InvalidLen(length_);
    }
    length = length_;
    segments.resize(length_, ShipSegment());
}

int Ship::GetLength() const { return length; }

Orientation Ship::GetOrientation() const { return orientation; }

SegmentState Ship::GetSegmentState(int index) const { return segments[index].GetState();
}

ShipSegment* Ship::GetSegment(int index) {
    return &segments[index];
}

bool Ship::IsDestroid() const {
    for (auto state : segments) {
        if (state.GetState() != SegmentState::Destroyed) {
            return false;
        }
    }
    return true;
}

nlohmann::json Ship::to_json() const {
    nlohmann::json ship_j;
    nlohmann::json segments_j = nlohmann::json::array();
    for (const auto& seg : segments) {
        segments_j.push_back(seg.to_json());
    }
    ship_j["segments"] = segments_j;
    switch (orientation) {
    case Orientation::Horizontal: ship_j["orientation"] = "Horizontal"; break;
    case Orientation::Vertical: ship_j["orientation"] = "Vertical"; break;
    }
    return ship_j;
}

Ship  Ship::from_json(const nlohmann::json& j) {
    if (!j.contains("segments") || !j.contains("orientation")) {
        throw std::invalid_argument("problem in fromjson in ship : /");
    }

    if (!j["segments"].is_array() || !j["orientation"].is_string()) {
        throw std::invalid_argument("problem in fromjson in ship : /");
    }

    std::vector<ShipSegment> segments;
    nlohmann::json segments_j = j["segments"];
    int size = 0;
    for (const auto& segment_j : segments_j) {
        segments.push_back(ShipSegment::from_json(segment_j));
        size += 1;
    }
    Ship ship(size, Orientation::Horizontal);
    ship.segments = segments;
    std::string orientation_str = j["orientation"].get<std::string>();
    if (orientation_str == "Horizontal") { ship.orientation = Orientation::Horizontal; }
    else  if (orientation_str == "Vertical") { ship.orientation = Orientation::Vertical; }
    else { throw std::invalid_argument("problem in fromjson in ship : / "); }
    return ship;
}