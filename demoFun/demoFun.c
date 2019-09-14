/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <string.h>
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_demoFun.h"

/* If you declare any globals in php_demoFun.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(demoFun)
*/

/* True global resources - no need for thread safety here */
static int le_demoFun;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("demoFun.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_demoFun_globals, demoFun_globals)
    STD_PHP_INI_ENTRY("demoFun.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_demoFun_globals, demoFun_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_demoFun_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_demoFun_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "demoFun", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(demo_fun_copy)
{
	/*
	*用来接受外部传入的字符串
	*/
	char *str = NULL;
	/*
	*外部传入的参数个数
	*/
	int argc = ZEND_NUM_ARGS();
 
	/*
	*用来接受外部字符串的长度
	*/
	int str_len;
	
	/**
	 * 用来接受外部传入的第二个参数
	 */
	long n;
 
	char *result; /* Points to resulting string */
 
	char *ptr; /* Points at the next location we want to copy to */
 
	int result_length; /* Length of resulting string */
 
	if (zend_parse_parameters(argc TSRMLS_CC, "sl", &str, &str_len, &n) == FAILURE)
 
	return;
 
	/* Calculate length of result */
 
	result_length = (str_len * n);
 
	/* Allocate memory for result */
 
	result = (char *) emalloc(result_length + 1);
 
	/* Point at the beginning of the result */
 
	ptr = result;
 
	while (n--) {
		/* 拷贝字符串*/
		/* Copy str to the result */
 
		memcpy(ptr, str, str_len);
 
		/* Increment ptr to point at the next position we want to write to */
		/* 内存地址往前走*/
		ptr += str_len;
 
	}
 
	/* Null terminate the result. Always null-terminate your strings
	
	even if they are binary strings */
 
	*ptr = '\0';/*在指针指向的位置赋值*/
 
	/* Return result to the scripting engine without duplicating it*/
 
	RETURN_STRINGL(result, result_length);
}


/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_demoFun_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_demoFun_init_globals(zend_demoFun_globals *demoFun_globals)
{
	demoFun_globals->global_value = 0;
	demoFun_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(demoFun)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(demoFun)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(demoFun)
{
#if defined(COMPILE_DL_DEMOFUN) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(demoFun)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(demoFun)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "demoFun support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ demoFun_functions[]
 *
 * Every user visible function must have an entry in demoFun_functions[].
 */
/*
* 注册函数，告知PHP内核扩展提供的函数有哪些
*/
const zend_function_entry demoFun_functions[] = {
	PHP_FE(confirm_demoFun_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(demo_fun_copy, NULL)
	PHP_FE_END	/* Must be the last line in demoFun_functions[] */
};
/* }}} */

/* {{{ demoFun_module_entry
 */
zend_module_entry demoFun_module_entry = {
	STANDARD_MODULE_HEADER,
	"demoFun",
	demoFun_functions,
	PHP_MINIT(demoFun),
	PHP_MSHUTDOWN(demoFun),
	PHP_RINIT(demoFun),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(demoFun),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(demoFun),
	PHP_DEMOFUN_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DEMOFUN
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(demoFun)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
