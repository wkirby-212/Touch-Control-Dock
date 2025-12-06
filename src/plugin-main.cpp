#include <obs-module.h>
#include <obs-frontend-api.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("touch-control-dock", "en-US")

static QWidget *g_helpWidget = nullptr;

const char *obs_module_name(void)
{
    return "Touch Control Dock";
}

bool obs_module_load(void)
{
    g_helpWidget = new QWidget();
    auto *layout = new QVBoxLayout(g_helpWidget);

    auto *label = new QLabel(
        "Touch Control Dock loaded.\n\n"
        "This plugin ships a touch UI page at:\n"
        "  data/touch-ui/index.html\n\n"
        "Quick use:\n"
        "1) In OBS: Tools -> WebSocket Server Settings\n"
        "   Enable the server and set a password.\n"
        "2) In OBS: View -> Docks -> Custom Browser Docks\n"
        "   Add a dock named 'Touch Control'.\n"
        "3) Point it to your local index.html file using file:///...\n"
        "   or serve the folder with a local web server.\n\n"
        "This help dock exists to confirm the plugin is loaded."
    );

    label->setWordWrap(true);
    layout->addWidget(label);

    obs_frontend_add_dock_by_id(
        "touch.control.help",
        "Touch Control Help",
        g_helpWidget
    );

    blog(LOG_INFO, "[Touch Control Dock] Loaded.");
    return true;
}

void obs_module_unload(void)
{
    obs_frontend_remove_dock("touch.control.help");

    delete g_helpWidget;
    g_helpWidget = nullptr;

    blog(LOG_INFO, "[Touch Control Dock] Unloaded.");
}
