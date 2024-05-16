import triple.all;
import samples.common;

using namespace triple;

void sprite_system(
    Commands commands,
    Resource<AssetServer> asset_server,
    Resource<Window> res_win
) {
    commands.spawn().add(
        Camera {
            .width = (float)res_win->width,
            .height = (float)res_win->height,
            .near = -1.0f,
            .far = 1.0f,
        },
        Transform2D {
            .position = {0.0f, 0.0f},
        }
    );
    commands.spawn().add(
        Sprite {
            .color = {1.0f, 1.0f, 1.0f, 1.0f},
            .anchor = Vector2 {0.5f, 0.5f},
            .texture = asset_server->load<Texture2D>("awesomeface.png"),
        },
        Transform2D {
            .position = {0.0f, 0.0f},
        }
    );
}

int main() {
    App app;
    app.add_plugin<SamplesPlugin>().add_system(StartUp, sprite_system).run();

    return 0;
}
