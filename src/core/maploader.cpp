#include <core/maploader.hpp>
#include <core/engine.hpp>

#include <fstream>

Core::MapLoader::MapLoader(std::string path){
    LOG(std::ifstream map(path), "INFO", "loading map");
    json data = json::parse(map);

    Render::Shaders *shader = new Render::Shaders("resources/shaders/mesh.vert",
                            	"resources/shaders/mesh.frag");

    for(auto& [key, val] : data.items()){
        if(val["type"] == "mesh"){
            Render::Texture *texture = nullptr;
            if(val.contains("shader")){
                shader = new Render::Shaders(val["shader"][0], val["shader"][1]);
            }
            if(val.contains("texture")){
                texture = new Render::Texture(val["texture"]);
            }
            if(val["type_mesh"] == "cube"){
                Render::Mesh *mesh = new Render::Mesh(Render::MESH_CUBE, shader, texture);
                if(val.contains("position")){
                    mesh->pos = glm::vec3(val["position"][0],
                                        val["position"][1],
                                        val["position"][2]);
                }
                if(val.contains("rotate")){
                    mesh->rot = glm::vec3(val["rotate"][0],
                                    val["rotate"][1],
                                    val["rotate"][2]);
                }
                if(val.contains("scale")){
                    mesh->scale = glm::vec3(val["scale"][0],
                                    val["scale"][1],
                                    val["scale"][2]);
                }
                if(objects_mesh.find(val["name"]) != objects_mesh.end() && \
                    objects_sprite.find(val["name"]) != objects_sprite.end() && \
                    objects_dlight.find(val["name"]) != objects_dlight.end())
                {
                    throw LOG(nullptr, "ERROR", "maploader error, an object with the same name already exists")
                }
                objects_mesh.insert({
                    val["name"],
                    mesh
                });
            }
        }

        else if(val["type"] == "sprite2d"){
            if(val.contains("shader")){
                shader = new Render::Shaders(val["shader"][0], val["shader"][1]);
            }
            Render::Texture *texture = new Render::Texture(val["texture"]);
            Render::Sprite2D *sprite = new Render::Sprite2D(shader, texture);
            if(val.contains("position")){
                sprite->pos = glm::vec2(val["position"][0],
                                    val["position"][1]);
            }
            if(val.contains("rotate")){
                sprite->rot = val["rotate"];
            }
            if(val.contains("scale")){
                sprite->scale = glm::vec2(val["scale"][0],
                                    val["scale"][1]);
            }
            if(objects_mesh.find(val["name"]) != objects_mesh.end() && \
                objects_sprite.find(val["name"]) != objects_sprite.end() && \
                objects_dlight.find(val["name"]) != objects_dlight.end())
            {
                throw LOG(nullptr, "ERROR", "maploader error, an object with the same name already exists")
            }
            objects_sprite.insert({
                val["name"],
                sprite
            });
        }

        else if(val["type"] == "directional light"){
            glm::vec3 lightColor = glm::vec3(1.0f);
            float ambientStrength = 0.4f;
            float specularStrength = 0.5f;

            if(val.contains("lightColor")){
                lightColor = glm::vec3(val["lightColor"][0],
                                        val["lightColor"][1],
                                        val["lightColor"][2]);
            }
            if(val.contains("ambientStrength")){
                ambientStrength = val["ambientStrength"];
            }
            if(val.contains("specularStrength")){
                ambientStrength = val["specularStrength"];
            }

            if(objects_mesh.find(val["name"]) != objects_mesh.end() && \
                objects_sprite.find(val["name"]) != objects_sprite.end() && \
                objects_dlight.find(val["name"]) != objects_dlight.end())
            {
                throw LOG(nullptr, "ERROR", "maploader error, an object with the same name already exists")
            }

            Render::DirectionalLight *dlight = new Render::DirectionalLight(
                lightColor, ambientStrength, specularStrength
            );
            if(val.contains("position")){
                dlight->pos = glm::vec3(val["position"][0],
                                        val["position"][1],
                                        val["position"][2]);
            }

            objects_dlight.insert({
                val["name"],
                dlight
            });
        }
    }
}

void Core::MapLoader::draw(){
    for(auto object = objects_mesh.begin();
        object != objects_mesh.end(); object++){
            object->second->draw();
    }

    for(auto object = objects_sprite.begin();
        object != objects_sprite.end(); object++){
            object->second->draw();
    }
}