#pragma once
#include <queue>
#include "constants.hpp"
#include "types.hpp"


namespace og {


    class EntityManager {

        private:
            std::queue<og::entity_t> queue{};
            std::size_t mSize = 0;
        
        public:
            EntityManager();
            og::entity_t entityCreate();
            void entityDestroy(const og::entity_t e);
            void clear();
            std::size_t size() const;

    };
    
} // namespace og
