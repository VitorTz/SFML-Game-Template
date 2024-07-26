#pragma once
#include <unordered_map>
#include <typeinfo>
#include "components.hpp"
#include "types.hpp"


namespace og {


    const static std::unordered_map<const char*, og::component_id_t> TYPE_ID_MAP = {
        {typeid(og::transform_t).name(), 0},
        {typeid(og::sprite_t).name(), 1},
        {typeid(og::obstacle_t).name(), 2}
    };

    template<typename T>
    og::component_id_t getComponentId() {
        return og::TYPE_ID_MAP.at(typeid(T).name());
    }
    
} // namespace og
