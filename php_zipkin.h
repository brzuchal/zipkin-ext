#ifndef PHP_ZIPKIN_H
#define PHP_ZIPKIN_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(zipkin)
    long counter;
    zend_bool direction;
ZEND_END_MODULE_GLOBALS(zipkin)

#ifdef ZTS
#define ZIPKIN_G(v) TSRMG(zipkin_globals_id, zend_zipkin_globals *, v)
#else
#define ZIPKIN_G(v) (zipkin_globals.v)
#endif

#define PHP_ZIPKIN_WORLD_VERSION "1.0"
#define PHP_ZIPKIN_WORLD_EXTNAME "zipkin"

typedef struct _php_zipkin_person {
    char *name;
    int name_len;
    long age;
} php_zipkin_person;

#define PHP_ZIPKIN_PERSON_RES_NAME "Person Data"

PHP_MINIT_FUNCTION(zipkin);
PHP_MSHUTDOWN_FUNCTION(zipkin);
PHP_RINIT_FUNCTION(zipkin);

PHP_FUNCTION(zipkin_world);
PHP_FUNCTION(zipkin_long);
PHP_FUNCTION(zipkin_double);
PHP_FUNCTION(zipkin_bool);
PHP_FUNCTION(zipkin_null);
PHP_FUNCTION(zipkin_greetme);
PHP_FUNCTION(zipkin_add);
// Part 2
PHP_FUNCTION(zipkin_array);
PHP_FUNCTION(zipkin_array_strings);
PHP_FUNCTION(zipkin_get_global_var);
PHP_FUNCTION(zipkin_set_local_var);
// Part 3
PHP_FUNCTION(zipkin_person_new);
PHP_FUNCTION(zipkin_person_greet);

extern zend_module_entry zipkin_module_entry;
#define phpext_zipkin_prt &zipkin_module_entry

#endif
