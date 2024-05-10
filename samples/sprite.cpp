#include "common.hpp"

int main() {
    App app;
    app.add_plugin<SamplesPlugin>()
        .add_plugin<WindowPlugin>()
        .add_plugin<OpenGLPlugin>()
        .add_plugin<GraphicsPlugin>()
        .add_plugin<RenderPlugin>()
        .add_plugin<SpritePlugin>()
        .add_system(
            StartUp,
            +[](Commands commands,
                Resource<AssetServer> asset_server,
                Resource<Window> res_win) {
                commands.spawn()
                    .add(Camera {
                        .width = (float)res_win->width,
                        .height = (float)res_win->height,
                        .near = -1.0f,
                        .far = 1.0f,
                    })
                    .add(Transform2D {
                        .position = {0.0f, 0.0f},
                    });
                commands.spawn()
                    .add(Sprite {
                        .color = {1.0f, 1.0f, 1.0f, 1.0f},
                        .anchor = Vector2 {0.5f, 0.5f},
                        .texture =
                            asset_server->load<Texture2D>("awesomeface.png"),
                        .program = asset_server->load<Program>("sprite.glsl")
                    })
                    .add(Transform2D {
                        .position = {0.0f, 0.0f},
                    });
            }
        )
        .run();

    return 0;
}