#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_zipkin.h"

int le_zipkin_person;

ZEND_DECLARE_MODULE_GLOBALS(zipkin)

static function_entry zipkin_functions[] = {
    PHP_FE(zipkin_world, NULL)
    PHP_FE(zipkin_long, NULL)
    PHP_FE(zipkin_double, NULL)
    PHP_FE(zipkin_bool, NULL)
    PHP_FE(zipkin_null, NULL)
    PHP_FE(zipkin_greetme, NULL)
    PHP_FE(zipkin_add, NULL)
    PHP_FE(zipkin_array, NULL)
    PHP_FE(zipkin_array_strings, NULL)
    PHP_FE(zipkin_get_global_var, NULL)
    PHP_FE(zipkin_set_local_var, NULL)
    PHP_FE(zipkin_person_new, NULL)
    PHP_FE(zipkin_person_greet, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry zipkin_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_ZIPKIN_WORLD_EXTNAME,
    zipkin_functions,
    PHP_MINIT(zipkin),
    PHP_MSHUTDOWN(zipkin),
    PHP_RINIT(zipkin),
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_ZIPKIN_WORLD_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_zipkin
ZEND_GET_MODULE(zipkin)
#endif

PHP_INI_BEGIN()
    PHP_INI_ENTRY("zipkin.host", "localhost", PHP_INI_ALL, NULL)
    STD_PHP_INI_ENTRY("zipkin.sample", "11", PHP_INI_ALL,
        OnUpdateBool, direction, zend_zipkin_globals, zipkin_globals)
PHP_INI_END()

static void php_zipkin_init_globals(zend_zipkin_globals *zipkin_globals)
{
    zipkin_globals->direction = 1;
}

PHP_RINIT_FUNCTION(zipkin)
{
    zipkin_G(counter) = 0;

    return SUCCESS;
}

PHP_MINIT_FUNCTION(zipkin)
{
    le_zipkin_person = zend_register_list_destructors_ex(NULL, NULL,
        PHP_ZIPKIN_PERSON_RES_NAME, module_number);
    ZEND_INIT_MODULE_GLOBALS(zipkin, php_zipkin_init_globals, NULL);
    REGISTER_INI_ENTRIES();

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(zipkin)
{
    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}

PHP_FUNCTION(zipkin_world)
{
    RETURN_STRING(INI_STR("zipkin.host"), 1);
}

PHP_FUNCTION(zipkin_long)
{
    if (zipkin_G(direction)) {
        zipkin_G(counter)++;
    } else {
        zipkin_G(counter)--;
    }

    RETURN_LONG(zipkin_G(counter));
}

PHP_FUNCTION(zipkin_double)
{
    RETURN_DOUBLE(3.1415926535);
}

PHP_FUNCTION(zipkin_bool)
{
    RETURN_BOOL(1);
}

PHP_FUNCTION(zipkin_null)
{
    RETURN_NULL();
}

PHP_FUNCTION(zipkin_greetme)
{
    zval *zname;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zname) == FAILURE) {
        RETURN_NULL();
    }

    convert_to_string(zname);
    php_printf("zipkin ");
    PHPWRITE(Z_STRVAL_P(zname), Z_STRLEN_P(zname));
    php_printf("\n");

    RETURN_TRUE;
}

PHP_FUNCTION(zipkin_add)
{
    long a;
    double b;
    zend_bool return_long = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld|b", &a, &b, &return_long) == FAILURE) {
        RETURN_NULL();
    }

    if (return_long) {
        RETURN_LONG(a + b);
    } else {
        RETURN_DOUBLE(a + b);
    }
}

// Part 2

PHP_FUNCTION(zipkin_array)
{
    char *mystr;
    zval *mysubarray;

    array_init(return_value);

    add_index_long(return_value, 42, 123);

    add_next_index_string(return_value, "I should now be found at index 43", 1);

    add_next_index_stringl(return_value, "I'm at 44!", 10, 1);

    mystr = estrdup("Forty Five");
    add_next_index_string(return_value, mystr, 0);

    add_assoc_double(return_value, "pi", 3.1415926535);

    ALLOC_INIT_ZVAL(mysubarray);
    array_init(mysubarray);
    add_next_index_string(mysubarray, "zipkin", 1);
    add_assoc_zval(return_value, "subarray", mysubarray);
}

PHP_FUNCTION(zipkin_array_strings)
{
    zval *arr, **data;
    HashTable *arr_hash;
    HashPosition pointer;
    int array_count;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
        RETURN_NULL();
    }

    arr_hash = Z_ARRVAL_P(arr);
    array_count = zend_hash_num_elements(arr_hash);

    php_printf("The array passed contains %d elements\n", array_count);

    for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer);
        zend_hash_get_current_data_ex(arr_hash, (void**) &data, &pointer) == SUCCESS;
        zend_hash_move_forward_ex(arr_hash, &pointer)) {

        zval temp;
        char *key;
        int key_len;
        long index;

        if (zend_hash_get_current_key_ex(arr_hash, &key, &key_len, &index, 0, &pointer) == HASH_KEY_IS_STRING) {
            PHPWRITE(key, key_len);
        } else {
            php_printf("%ld", index);
        }

        php_printf(" => ");

        temp = **data;
        zval_copy_ctor(&temp);
        convert_to_string(&temp);
        PHPWRITE(Z_STRVAL(temp), Z_STRLEN(temp));
        php_printf("\n");
        zval_dtor(&temp);

    }
    RETURN_TRUE;
}

PHP_FUNCTION(zipkin_get_global_var)
{
    char *varname;
    int varname_len;
    zval **varvalue;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &varname, &varname_len) == FAILURE) {
        RETURN_NULL();
    }

    if (zend_hash_find(&EG(symbol_table), varname, varname_len + 1, (void**)&varvalue) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Undefined variable: %s", varname);
        RETURN_NULL();
    }

    *return_value = **varvalue;
    zval_copy_ctor(return_value);
}

PHP_FUNCTION(zipkin_set_local_var)
{
    zval *newvar;
    char *varname;
    int varname_len;
    zval *value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz", &varname, &varname_len, &value) == FAILURE) {
        RETURN_NULL();
    }

    ALLOC_INIT_ZVAL(newvar);
    *newvar = *value;
    zval_copy_ctor(newvar);
    zend_hash_add(EG(active_symbol_table), varname, varname_len + 1, &newvar, sizeof(zval*), NULL);

    RETURN_TRUE;
}

// Part 3

PHP_FUNCTION(zipkin_person_new)
{
    php_zipkin_person *person;
    char *name;
    int name_len;
    long age;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &name, &name_len, &age) == FAILURE) {
        RETURN_FALSE;
    }

    if (name_len < 1) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "No name given, person resource not created.", age);
        RETURN_FALSE;
    }

    if (age < 0 || age > 255) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Nonsense age (%d) given, person resource not created.", age);
        RETURN_FALSE;
    }

    person = emalloc(sizeof(php_zipkin_person));
    person->name = estrndup(name, name_len);
    person->name_len = name_len;
    person->age = age;

    ZEND_REGISTER_RESOURCE(return_value, person, le_zipkin_person);
}

PHP_FUNCTION(zipkin_person_greet)
{
    php_zipkin_person *person;
    zval *zperson;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zperson) == FAILURE) {
        RETURN_FALSE;
    }

    ZEND_FETCH_RESOURCE(person, php_zipkin_person*, &zperson, -1,
        PHP_zipkin_PERSON_RES_NAME, le_zipkin_person);

    php_printf("zipkin ");
    PHPWRITE(person->name, person->name_len);
    php_printf("!\nAccording to my records, you are %d years old.\n", person->age);

    RETURN_TRUE;
}

