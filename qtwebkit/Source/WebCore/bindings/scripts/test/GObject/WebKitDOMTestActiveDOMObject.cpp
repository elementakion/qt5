/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "WebKitDOMTestActiveDOMObject.h"

#include "DOMObjectCache.h"
#include "ExceptionCode.h"
#include "JSMainThreadExecState.h"
#include "WebKitDOMBinding.h"
#include "WebKitDOMNodePrivate.h"
#include "WebKitDOMTestActiveDOMObjectPrivate.h"
#include "gobject/ConvertToUTF8String.h"
#include "webkitglobalsprivate.h"
#include <wtf/GetPtr.h>
#include <wtf/RefPtr.h>

namespace WebKit {

WebKitDOMTestActiveDOMObject* kit(WebCore::TestActiveDOMObject* obj)
{
    g_return_val_if_fail(obj, 0);

    if (gpointer ret = DOMObjectCache::get(obj))
        return static_cast<WebKitDOMTestActiveDOMObject*>(ret);

    return static_cast<WebKitDOMTestActiveDOMObject*>(DOMObjectCache::put(obj, WebKit::wrapTestActiveDOMObject(obj)));
}

WebCore::TestActiveDOMObject* core(WebKitDOMTestActiveDOMObject* request)
{
    g_return_val_if_fail(request, 0);

    WebCore::TestActiveDOMObject* coreObject = static_cast<WebCore::TestActiveDOMObject*>(WEBKIT_DOM_OBJECT(request)->coreObject);
    g_return_val_if_fail(coreObject, 0);

    return coreObject;
}

WebKitDOMTestActiveDOMObject* wrapTestActiveDOMObject(WebCore::TestActiveDOMObject* coreObject)
{
    g_return_val_if_fail(coreObject, 0);

    // We call ref() rather than using a C++ smart pointer because we can't store a C++ object
    // in a C-allocated GObject structure. See the finalize() code for the matching deref().
    coreObject->ref();

    return WEBKIT_DOM_TEST_ACTIVE_DOM_OBJECT(g_object_new(WEBKIT_TYPE_DOM_TEST_ACTIVE_DOM_OBJECT, "core-object", coreObject, NULL));
}

} // namespace WebKit

G_DEFINE_TYPE(WebKitDOMTestActiveDOMObject, webkit_dom_test_active_dom_object, WEBKIT_TYPE_DOM_OBJECT)

enum {
    PROP_0,
    PROP_EXCITING_ATTR,
};

static void webkit_dom_test_active_dom_object_finalize(GObject* object)
{

    WebKitDOMObject* domObject = WEBKIT_DOM_OBJECT(object);
    
    if (domObject->coreObject) {
        WebCore::TestActiveDOMObject* coreObject = static_cast<WebCore::TestActiveDOMObject*>(domObject->coreObject);

        WebKit::DOMObjectCache::forget(coreObject);
        coreObject->deref();

        domObject->coreObject = 0;
    }


    G_OBJECT_CLASS(webkit_dom_test_active_dom_object_parent_class)->finalize(object);
}

static void webkit_dom_test_active_dom_object_set_property(GObject* object, guint propertyId, const GValue* value, GParamSpec* pspec)
{
    WebCore::JSMainThreadNullState state;
    switch (propertyId) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, propertyId, pspec);
        break;
    }
}


static void webkit_dom_test_active_dom_object_get_property(GObject* object, guint propertyId, GValue* value, GParamSpec* pspec)
{
    WebCore::JSMainThreadNullState state;

    WebKitDOMTestActiveDOMObject* self = WEBKIT_DOM_TEST_ACTIVE_DOM_OBJECT(object);
    WebCore::TestActiveDOMObject* coreSelf = WebKit::core(self);

    switch (propertyId) {
    case PROP_EXCITING_ATTR: {
        g_value_set_long(value, coreSelf->excitingAttr());
        break;
    }
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, propertyId, pspec);
        break;
    }
}


static void webkit_dom_test_active_dom_object_constructed(GObject* object)
{

    if (G_OBJECT_CLASS(webkit_dom_test_active_dom_object_parent_class)->constructed)
        G_OBJECT_CLASS(webkit_dom_test_active_dom_object_parent_class)->constructed(object);
}

static void webkit_dom_test_active_dom_object_class_init(WebKitDOMTestActiveDOMObjectClass* requestClass)
{
    GObjectClass* gobjectClass = G_OBJECT_CLASS(requestClass);
    gobjectClass->finalize = webkit_dom_test_active_dom_object_finalize;
    gobjectClass->set_property = webkit_dom_test_active_dom_object_set_property;
    gobjectClass->get_property = webkit_dom_test_active_dom_object_get_property;
    gobjectClass->constructed = webkit_dom_test_active_dom_object_constructed;

    g_object_class_install_property(gobjectClass,
                                    PROP_EXCITING_ATTR,
                                    g_param_spec_long("exciting-attr", /* name */
                                                           "test_active_dom_object_exciting-attr", /* short description */
                                                           "read-only  glong TestActiveDOMObject.exciting-attr", /* longer - could do with some extra doc stuff here */
                                                           G_MINLONG, /* min */
G_MAXLONG, /* max */
0, /* default */
                                                           WEBKIT_PARAM_READABLE));


}

static void webkit_dom_test_active_dom_object_init(WebKitDOMTestActiveDOMObject* request)
{
}

void
webkit_dom_test_active_dom_object_exciting_function(WebKitDOMTestActiveDOMObject* self, WebKitDOMNode* nextChild)
{
    g_return_if_fail(self);
    WebCore::JSMainThreadNullState state;
    WebCore::TestActiveDOMObject* item = WebKit::core(self);
    g_return_if_fail(nextChild);
    WebCore::Node* convertedNextChild = 0;
    if (nextChild) {
        convertedNextChild = WebKit::core(nextChild);
        g_return_if_fail(convertedNextChild);
    }
    item->excitingFunction(convertedNextChild);
}

void
webkit_dom_test_active_dom_object_post_message(WebKitDOMTestActiveDOMObject* self, const gchar* message)
{
    g_return_if_fail(self);
    WebCore::JSMainThreadNullState state;
    WebCore::TestActiveDOMObject* item = WebKit::core(self);
    g_return_if_fail(message);
    WTF::String convertedMessage = WTF::String::fromUTF8(message);
    item->postMessage(convertedMessage);
}

glong
webkit_dom_test_active_dom_object_get_exciting_attr(WebKitDOMTestActiveDOMObject* self)
{
    g_return_val_if_fail(self, 0);
    WebCore::JSMainThreadNullState state;
    WebCore::TestActiveDOMObject* item = WebKit::core(self);
    glong result = item->excitingAttr();
    return result;
}

