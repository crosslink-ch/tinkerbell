/* tinkerbell extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_tinkerbell.h"
#include "tinkerbell_arginfo.h"
#include "zend_execute.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

// Original execution function
static void (*zend_execute_ex_original)(zend_execute_data *execute_data);

static void my_execute_ex(zend_execute_data *execute_data)
{
	zend_function *func = execute_data->func;
	if (!func)
	{
		zend_execute_ex_original(execute_data);
		return;
	}

	if (!func->common.function_name)
	{
		zend_execute_ex_original(execute_data);
		return;
	}

	php_printf("Calling function: %s\n", ZSTR_VAL(func->common.function_name));

	// Call the original function
	zend_execute_ex_original(execute_data);
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(tinkerbell)
{
#if defined(ZTS) && defined(COMPILE_DL_TINKERBELL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	// Change execution function
	zend_execute_ex_original = zend_execute_ex;
	zend_execute_ex = my_execute_ex;

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(tinkerbell)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tinkerbell support", "enabled");
	php_info_print_table_end();
}
/* }}} */

PHP_MSHUTDOWN_FUNCTION(tinkerbell)
{
	zend_execute_ex = zend_execute_ex_original;
}

/* {{{ tinkerbell_module_entry */
zend_module_entry tinkerbell_module_entry = {
	STANDARD_MODULE_HEADER,
	"tinkerbell",			/* Extension name */
	NULL,					/* zend_function_entry, change to ext_functions if any functions exist */
	NULL,					/* PHP_MINIT - Module initialization */
	NULL,					/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(tinkerbell),	/* PHP_RINIT - Request initialization */
	NULL,					/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(tinkerbell),	/* PHP_MINFO - Module info */
	PHP_TINKERBELL_VERSION, /* Version */
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_TINKERBELL
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(tinkerbell)
#endif
