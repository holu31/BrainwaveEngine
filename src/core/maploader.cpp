#include <core/maploader.hpp>
#include <core/engine.hpp>

#include <fstream>

Core::MapLoader::MapLoader(std::string path){
    LOG(std::ifstream map(path), "INFO", "loading map");
    json data = json::parse(map);

    Render::Shaders *shader = new Render::Shaders("resources/shaders/mesh.vert",
                            	"resources/shaders/mesh.frag");

    for(auto& [key, val] : data.items()){
        Render::Texture *texture = nullptr;
        if(val.contains("shader")){
            shader = new Render::Shaders(val["shader"][0], val["shader"][1]);
        }
        if(val.contains("texture")){
            texture = new Render::Texture(val["texture"]);
        }
        Render::Mesh *mesh = new Render::Mesh(Render::MESH_CUBE, shader, texture);
        mesh->pos = glm::vec3(val["positions"][0],
                            val["positions"][1],
                            val["positions"][2]);
        objects.insert({
            val["name"],
            mesh
        });
    }
}

void Core::MapLoader::draw(){
    for(auto object = objects.begin();
        object != objects.end(); object++){
            object->second->draw();
    }
}