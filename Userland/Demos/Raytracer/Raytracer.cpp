/*
* Copyright (c) 2022, KrasnotR <me@krasno.one>
*
* SPDX-License-Identifier: BSD-2-Clause
*/

#include <LibMain/Main.h>
#include <LibGUI/Window.h>
#include <LibGUI/Frame.h>
#include <LibGfx/Bitmap.h>
#include <LibGUI/Menu.h>
#include <LibGUI/Application.h>
#include <LibCore/System.h>
#include <LibGUI/Icon.h>
#include <stdio.h>
#include <stdlib.h>

class Raytracer : public GUI::Frame {
    C_OBJECT(Raytracer);

public:
    virtual ~Raytracer() override = default;
    void set_stat_label(RefPtr<GUI::Label> l) { stats = l; };

private:
    Raytracer();
    RefPtr<Gfx::Bitmap> bitmap;
    RefPtr<GUI::Label> stats;

    virtual void paint_event(GUI::PaintEvent&) override;
    virtual void mousedown_event(GUI::MouseEvent& event) override;
    virtual void mousemove_event(GUI::MouseEvent& event) override;
    virtual void mouseup_event(GUI::MouseEvent& event) override;
};

ErrorOr<int> serenity_main(Main::Arguments arguments) {
    auto app = TRY(GUI::Application::try_create(arguments));

    TRY(Core::System::pledge("stdio recvfd sendfd rpath"));
    TRY(Core::System::unveil("/res", "r"));
    TRY(Core::System::unveil(nullptr, nullptr));

    auto window = TRY(GUI::Window::try_create());
    window->set_double_buffering_enabled(false);
    window->set_title("Raytracer");
    window->set_resizable(false);
    window->resize(640, 480);

    window->show();

    auto app_icon = TRY(GUI::Icon::try_create_default_icon("app-raytracer"));
    window->set_icon(app_icon.bitmap_for_size(32));

    return app->exec();
}
