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

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_extQueue.h"
#include "list.c"

/**
 * 队列的标示名字
 */ 
#define QUEUE_KEY_NAME "ext_queue"

/* If you declare any globals in php_extQueue.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(extQueue)
*/

/* True global resources - no need for thread safety here */
/**
 * 资源标记
 */ 
static int le_extQueue;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("extQueue.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_extQueue_globals, extQueue_globals)
    STD_PHP_INI_ENTRY("extQueue.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_extQueue_globals, extQueue_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_extQueue_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_extQueue_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "extQueue", arg);

	RETURN_STR(strg);
}

/**
 * 创建队列资源ID
 */ 
PHP_FUNCTION(queue_list_create)
{
	zval *res;
	list_t *ls;
	int resource_id;
	ls = create_list();
	if (!ls) {
		RETURN_FALSE;
	}
	/**
	 * 注册资源ID
	 */ 
	RETURN_RES(zend_register_resource(ls, le_extQueue));
}

PHP_FUNCTION(list_push)
{
	zval *res,*data;
	list_t *ls;
	if ( zend_parse_parameters(ZEND_NUM_ARGS(),"rz",&res, &data) == FAILURE ) {
		RETURN_FALSE;
	}

	ls = zend_fetch_resource(Z_RES_P(res),QUEUE_KEY_NAME,le_extQueue);
	if (!ls) {
		printf("获取资源类型错误\n");
		RETURN_FALSE;
	}

	if(list_push(ls, (void *)data) == 1) {
		/*zend_add_ref(&data);*/
		RETURN_TRUE;
	}
	printf("加入队列错误\n");
	RETURN_FALSE;

}


PHP_FUNCTION(list_pop)
{
	zval *res, *data;
	list_t *ls;
	if ( zend_parse_parameters(ZEND_NUM_ARGS(),"r",&res) == FAILURE ) {
		RETURN_FALSE;
	}
	ls = zend_fetch_resource(Z_RES_P(res),QUEUE_KEY_NAME,le_extQueue);
	if (!ls) {
		printf("pop获取资源类型错误\n");
		RETURN_FALSE;
	}

	if(list_pop(ls,(void **)&data)) {
	
		RETURN_ZVAL(data, 1, 1);
	}
    printf("pop获取数据错误\n");
	RETURN_FALSE;
}


PHP_FUNCTION(list_count)
{
	zval *res;
	list_t *ls;
	if ( zend_parse_parameters(ZEND_NUM_ARGS(),"r",&res) == FAILURE ) {
		RETURN_FALSE;
	}
	ls = zend_fetch_resource(Z_RES_P(res),QUEUE_KEY_NAME,le_extQueue);
	if (ls == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(list_count(ls));
}



/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_extQueue_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_extQueue_init_globals(zend_extQueue_globals *extQueue_globals)
{
	extQueue_globals->global_value = 0;
	extQueue_globals->global_string = NULL;
}
*/
/* }}} */
//
/*static void free(zend_rsrc_list_entry *rsrc TSRMLS_DC){*/
static void free_list(zend_resource *rsrc TSRMLS_DC){
     list_t *fp = (list_t *) rsrc->ptr;
     list_free(fp);
}


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(extQueue)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	/**
	 * 注册资源类型，返回资源类型标示ID
	 */ 
	le_extQueue = zend_register_list_destructors_ex(free_list, NULL, QUEUE_KEY_NAME, module_number);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(extQueue)
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
PHP_RINIT_FUNCTION(extQueue)
{
#if defined(COMPILE_DL_EXTQUEUE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(extQueue)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(extQueue)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "extQueue support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ extQueue_functions[]
 *
 * Every user visible function must have an entry in extQueue_functions[].
 */
const zend_function_entry extQueue_functions[] = {
	PHP_FE(confirm_extQueue_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(queue_list_create, NULL)
	PHP_FE(list_push, NULL)
	PHP_FE(list_pop, NULL)
	PHP_FE(list_count, NULL)
	PHP_FE_END	/* Must be the last line in extQueue_functions[] */
};
/* }}} */

/* {{{ extQueue_module_entry
 */
zend_module_entry extQueue_module_entry = {
	STANDARD_MODULE_HEADER,
	"extQueue",
	extQueue_functions,
	PHP_MINIT(extQueue),
	PHP_MSHUTDOWN(extQueue),
	PHP_RINIT(extQueue),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(extQueue),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(extQueue),
	PHP_EXTQUEUE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_EXTQUEUE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(extQueue)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
