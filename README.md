# C++ SFML Game Template (ECS pattern)
---

## Criar um novo Componente

Como exemplo, vamos tentar criar um novo Component chamado
rigid_body que possui essas características:

``` c++
// include/components.hpp
typedef struct rigid_body {
    float speed{};    
    sf::Vector2f direction{};
} rigid_body_t
```
1. Dentro do arquivo include/components.hpp
    - Adicione o componente rigid_body_t
    - Atualize a variável NUM_COMPONENTS para corresponder a alteração no número de components diferentes

``` c++
// include/components.hpp
constexpr std::size_t NUM_COMPONENTS = 3;

...

typedef struct rigid_body {
    float speed{};    
    sf::Vector2f direction{};
} rigid_body_t

...

```

2. Dentro do arquivo include/component_id_manager.hpp
    - Crie um ID único para o component rigid_body_t

```c++
//include/component_id_manager.hpp
const static std::unordered_map<const char*, og::component_id_t> TYPE_ID_MAP = {
    ...
    ...
    {typeid(og::rigid_body_t).name(), 2},
    ...
};

template<typename T>
og::component_id_t getComponentId() {
    return og::TYPE_ID_MAP.at(typeid(T).name());
}
```

3. Dentro do arquivo include/system.hpp
    - Crie a classe **RigidBodySystem** que herda de System para implementar as 
    funcionalidades correspondetes ao component rigid_body_t

``` c++
// include/system.hpp
class System {

    public:
        std::unordered_set<og::entity_t> entities{};

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow& window, og::entity_t e) = 0;

};

class RigidBodySystem : public og::System {

    public:
        void update(float dt) override;
        void draw(sf::RenderWindow& window, og::entity_t e) override;

};
...
...
```

4. Crie um arquivo em src/system_rigid_body.cpp e implemente o código da classe **RigidBodySystem**

``` c++
// src/system_rigid_body.cpp

#include "../include/system.hpp"
#include "../include/ecs.hpp"

void og::RigidBodySystem::update(const float dt) {        
    for (const og::entity_t e : this->entities) {
        og::transform_t& t = og::gEcs.getTransform(e);
        const og::rigid_body_t& r = og::gEcs.getComponent(e);
        t.pos.x += dt * r.speed * r.direction.x;
        t.pos.y += dt * r.speed * r.direction.y;
    }
}


void og::RigidBodySystem::draw(
    sf::RenderWindow& window, 
    const og::entity_t e
) { }
```

5. Dentro de include/component_manager.hpp
    - Registre um novo ComponentArray para o componente rigid_body chamando **registerComponentArray** dentro do construtor de ComponentManager

``` c++
// include/component_manager.hpp
ComponentManager() {
    ...
    this->registerComponentArray<og::rigid_body_t>();
    if (this->componentMap.size() != og::NUM_COMPONENTS) {
        og::Log::error("ComponentArrayMap size != NUM_COMPONENTS");
    }
    ...
}

```

6. Dentro de include/system_manager.hpp
    - Registre uma instância de **RigidBodySystem** chamando **registerSystem** dentro do construtor de SystemManager

``` c++
// include/system_manager.hpp
// O Component transform_t não possui uma classe System associado,
// por isso o número de Systems registrados deve ser igual a NUM_COMPONENTS - 1
SystemManager() {
    ...
    this->registerSystem<og::rigid_body_t, og::RigidBodySystem>();
    ...    
    if (this->systemMap.size() != og::NUM_COMPONENTS - 1) {
        og::Log::error("SystemMap size != NUM_COMPONENTS");
    }
    ...    
}

```

7. Adicione o componente rigid_body_t a alguma Entity

``` c++
const og::entity_t e = og::gEcs.createEntity(0, true);
og::gEcs.addComponent<og::rigid_body_t>(
    e, og::rigid_body_t{
        .speed = 150.f,
        .weight = 10.f
    }
);
```



---

## Linux SFML's dependencies

``` bash
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```
## Configure and build
``` bash
cmake -S . -B build
cmake --build build --config Release
```
## Run

``` bash
./build/bin/Ougi
```

## Solution for safe directory error

``` bash
git config --global --add safe.directory /complete/path/to/Ougi/build/_deps/sfml-src
```
