/* psencrypt extension for PHP (c) 2024 Netor0x86 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_psencrypt.h"
#include "psencrypt_arginfo.h"
#include "include/log/sencrypt_log.h"

char *psencrypt_log_file = NULL;
int log_level = psencrypt_log_notice;

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "psencrypt");
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

ZEND_INI_MH(php_s_encrypt_log_file)
{
    if (ZSTR_LEN(new_value) == 0)
    {
        return SUCCESS;
    }

    psencrypt_log_file = estrdup(ZSTR_VAL(new_value));

    if (psencrypt_log_file == NULL)
    {
        return FAILURE;
    }

    return SUCCESS;
}

ZEND_INI_MH(php_s_encrypt_log_level)
{
    char *level = NULL;

    if (ZSTR_LEN(new_value) == 0)
    {
        return SUCCESS;
    }

    level = ZSTR_VAL(new_value);

    if (level == NULL)
    {
        return FAILURE;
    }

    if (strcasecmp(level, "debug") == 0)
    {
        log_level = psencrypt_log_debug;
    }
    else if (strcasecmp(level, "notice") == 0)
    {
        log_level = psencrypt_log_notice;
    }
    else if (strcasecmp(level, "error") == 0)
    {
        log_level = psencrypt_log_error;
    }
    else
    {
        return FAILURE;
    }

    return SUCCESS;
}

PHP_INI_BEGIN()
    PHP_INI_ENTRY("psencrypt.log_file", "./php-s-encrypt.log", PHP_INI_ALL, php_s_encrypt_log_file)
    PHP_INI_ENTRY("psencrypt.log_level", "notice", PHP_INI_ALL, php_s_encrypt_log_level)
PHP_INI_END()

PHP_MINIT_FUNCTION(psencrypt)
{
    REGISTER_INI_ENTRIES();

    if (psencrypt_log_init(psencrypt_log_file, log_level) == -1)
    {
        php_error_docref(NULL, E_ERROR, "Unable open log file for sencrypt");
        return FAILURE;
    }

    psencrypt_write_log(psencrypt_log_notice, "php-s-encrypt ext loaded!!");

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(psencrypt)
{
    UNREGISTER_INI_ENTRIES();

    psencrypt_log_destroy();

    return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(psencrypt)
{
#if defined(ZTS) && defined(COMPILE_DL_PSENCRYPT)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(psencrypt)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "psencrypt support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ psencrypt_module_entry */
zend_module_entry psencrypt_module_entry = {
	STANDARD_MODULE_HEADER,
	"psencrypt",					/* Extension name */
	ext_functions,					/* zend_function_entry */
    PHP_MINIT(psencrypt),							/* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(psencrypt),							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(psencrypt),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(psencrypt),			/* PHP_MINFO - Module info */
	PHP_PSENCRYPT_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PSENCRYPT
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(psencrypt)
#endif
