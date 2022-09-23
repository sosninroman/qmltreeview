#if defined(WIN32)
    #if defined (FOO_EXPORT)
        #define FOO_API __declspec(dllexport)
    #else
        #define FOO_API __declspec(dllimport)
    #endif
#else
    #define FOO_API
#endif
