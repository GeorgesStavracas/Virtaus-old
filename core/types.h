#ifndef TYPES_H
#define TYPES_H

namespace Virtaus
{
    namespace State
    {
        enum State
        {
            CHANGES_UNSAVED,
            CHANGES_SAVED,
            CHANGES_DISCARTED,
            COLLECTION_OPENED,
            COLLECTION_ADDED,
            COLLECTION_CLOSED,
            COLLECTION_REMOVED,
            CATEGORY_OPENED,
            CATEGORY_ADDED,
            CATEGORY_CLOSED,
            CATEGORY_REMOVED,
            ITEM_OPENED,
            ITEM_ADDED,
            ITEM_CLOSED,
            ITEM_REMOVED,
            ATTRIBUTE_OPENED,
            ATTRIBUTE_ADDED,
            ATTRIBUTE_CLOSED,
            ATTRIBUTE_REMOVED,
            SET_OPENED,
            SET_ADDED,
            SET_CLOSED,
            SET_REMOVED,
        };
    }

    namespace View
    {
        enum Views
        {
            COLLECTION_VIEW,
            COLLECTION_INFO_VIEW,
            SET_MANAGER_VIEW,
            SET_VIEW,
            CATEGORY_VIEW,
            DIAGRAM_VIEW,
            PRODUCT_VIEW,
            ITEM_VIEW,
            COLLECTION_OPTIONS_VIEW
        };
    }
}

#endif // TYPES_H
