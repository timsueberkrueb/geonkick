

#include "mainwindow.h"
#include "geonkick_lv2.h"

#include <QApplication>
#include <QWidget>
#include <iostream>

struct GeonkickAPI {
        int api;
};

static LV2UI_Handle
instantiate_ui(const LV2UI_Descriptor*   descriptor,
            const char*               plugin_uri,
            const char*               bundle_path,
            LV2UI_Write_Function      write_function,
            LV2UI_Controller          controller,
            LV2UI_Widget*             widget,
            const LV2_Feature* const* features)
{
        std::cout << __PRETTY_FUNCTION__ << "called" << std::endl;
        if (!QCoreApplication::instance()) {
                std::cout << __PRETTY_FUNCTION__ << "App not running" << std::endl;
                return NULL;
        }

        auto window = new MainWindow;
        *widget = window;
        if (!window->init()) {
                qDebug() << "can't init main window";
                return NULL;
        }

        window->show();
        return window;
}

static void
cleanup_ui(LV2UI_Handle handle)
{
        std::cout << __PRETTY_FUNCTION__ << "called" << std::endl;
        delete static_cast<MainWindow*>(handle);
}

static void port_event_ui (
	LV2UI_Handle ui, uint32_t port_index,
	uint32_t buffer_size, uint32_t format, const void *buffer )
{
        std::cout << __PRETTY_FUNCTION__ << "called" << std::endl;
}

static const LV2UI_Descriptor descriptor_ui = {
	APP_URI_UI,
	instantiate_ui,
	cleanup_ui,
	port_event_ui,
	NULL
};


static int i = 0;

LV2_SYMBOL_EXPORT
const LV2UI_Descriptor*
lv2ui_descriptor(uint32_t index)
{
        std::cout << __PRETTY_FUNCTION__ << "index = " << index << std::endl;

	switch (index) {
	case 0:
		return &descriptor_ui;
	default:
		return NULL;
        }

}

// ----------------------

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
        std::cout << __PRETTY_FUNCTION__ << "called[call system]" << std::endl;
        GeonkickAPI* api = (GeonkickAPI*)malloc(sizeof(GeonkickApi));
	return api;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
}

static void
activate(LV2_Handle instance)
{
}


static void
run(LV2_Handle instance, uint32_t n_samples)
{
}

static void
deactivate(LV2_Handle instance)
{
}

static const LV2_Descriptor descriptor = {
	APP_URI,
	instantiate,
	connect_port,
	activate,
	run,
	deactivate,
	NULL,
	NULL
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
        std::cout << __PRETTY_FUNCTION__ << "index = " << index << std::endl;
	switch (index) {
	case 0:  return &descriptor;
	default: return NULL;
	}
}