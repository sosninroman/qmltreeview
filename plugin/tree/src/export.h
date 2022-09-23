#if defined(WIN32)
#if defined (TREE_VIEW_EXPORT)
#define TREE_VIEW_API __declspec(dllexport)
#else
#define TREE_VIEW_API __declspec(dllimport)
#endif
#else
#define FOO_API
#endif
