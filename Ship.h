#pragma once
#include <vector>
#include <iostream>
#include <memory>
//#pragma warning(disable: 26495)
#include "json.hpp"

class Ship; // ��������������� ���������� ������ Ship

enum class SegmentState {
    Intact,
    Damaged,
    Destroyed
};


enum class Orientation {
    Horizontal,
    Vertical
};

class ShipSegment {
private:
    SegmentState state;
public:
    ShipSegment();
    SegmentState GetState()const;
    void SetState(SegmentState state_) { state = state_; }
    SegmentState Hit();
    
    // ������������
    nlohmann::json to_json() const;

    // ��������������
    static ShipSegment from_json(const nlohmann::json& j);
};

class Ship {
private:
    int length;
    Orientation orientation;
    std::vector<ShipSegment> segments;
public:
    Ship(int length, Orientation orientation);

    // �������� �����
    int GetLength() const; //���� �� ������� ����� �� ��� ��� �������� �� ������ ���������

    //�������� ����������
    Orientation GetOrientation() const;

    //�������� ��������� �������� �� ��� �������
    SegmentState GetSegmentState(int index) const;

    //�������� ��������� �� ������� �� �������
    ShipSegment* GetSegment(int index);

    //���������� �� �������
    bool IsDestroid() const;


    //// ����� ������������
    nlohmann::json to_json() const;

    //// ����� ��������������
    static Ship from_json(const nlohmann::json& j);
};
