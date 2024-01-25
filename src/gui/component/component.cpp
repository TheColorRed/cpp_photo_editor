// #include <gtk/gtk.h>

// #include <cstddef>

// #include "component.h"

// // template <typename T>
// void Component::initSelf(ComponentDeclaration declaration) {
//   printf("Component::init\n");
//   // GTK_WIDGET(g_object_new(TFE_TYPE_ALERT, NULL));
//   // this->initBindings(, declaration.name, declaration.member_name);
//   // init();
//   // auto component = Component::get<Component>(this->tpl);
//   // if (component.has_value()) {
//   //   this->tpl = component.value().templatePath;
//   //   this->css = component.value().cssPath;
//   // }
// }

// /**
//  * @param widget_class The class of the widget.
//  * @param name The name of the child in the template.
//  * @param type The type example: `offsetof(Test, some_member)`.
// */
// void Component::initBindings(GtkWidgetClass *widget_class, string name, gssize type) {
//   printf("draw_image_class_init\n");
//   gtk_widget_class_set_template_from_resource(widget_class, "/ui/components/image/image.component.ui");
//   gtk_widget_class_bind_template_child_full(widget_class, name.c_str(), FALSE, type);
//   // offsetof(Test, member_name));
//   // G_STRUCT_OFFSET(TypeName, member_name))
//   // gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), name, font_dialog_btn);
// }
