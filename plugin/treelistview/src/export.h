#if defined(WIN32)
#if defined (TREE_LIST_VIEW_EXPORT)
#define TREE_LIST_VIEW_API __declspec(dllexport)
#else
#define TREE_LIST_VIEW_API __declspec(dllimport)
#endif
#else
#define FOO_API
#endif
