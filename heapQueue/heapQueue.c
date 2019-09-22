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
#include "php_heapQueue.h"
#include "heap_queue.c"

/* If you declare any globals in php_heapQueue.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(heapQueue)
*/
#define heapQueueClassName "heapQueue"
#define PHP_HEAP_VER "0.1.0"

/* True global resources - no need for thread safety here */
static int le_heapQueue;

static heapTable_t *heapTablePtr;

zend_class_entry *heapQueuePtr;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("heapQueue.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_heapQueue_globals, heapQueue_globals)
    STD_PHP_INI_ENTRY("heapQueue.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_heapQueue_globals, heapQueue_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_heapQueue_compiled(string arg)
   Return a string to confirm that the module is compiled in */
// PHP_FUNCTION(confirm_heapQueue_compiled)
// {
// 	char *arg = NULL;
// 	size_t arg_len, len;
// 	zend_string *strg;

// 	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
// 		return;
// 	}

// 	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "heapQueue", arg);

// 	RETURN_STR(strg);
// }
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/
/* 获取版本号 无参数 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_heapQueue_getVersion, 0, 0, 0)
ZEND_END_ARG_INFO()

/* 获取版本号 无参数 注册一个PHP类方法*/
PHP_METHOD(heapQueue, getVersion)
{
	zval *rv;
	/**
	 * 参数解释

zend_class_entry *scope	类原型结构体
zval *object	类对象，一般都是使用getThis()
const char *name	成员名
size_t name_length	成员名字符串长度
zend_bool silent	是否报错
zval *rv	未知，不过通过搜索代码发现都是传一个zval *
	 */ 
	zval *str = zend_read_property(heapQueuePtr, getThis(), "version", sizeof("version") - 1, 1 , rv);
	RETURN_ZVAL(str, 1, 0);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_heapQueue_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(heapQueue, __construct)
{
	if (!heapTablePtr) {
		heapTablePtr = heap_init(8);
	}
	
	if (!heapTablePtr) {
		return;
	}
}


/* 押入一个数据 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_heapQueue_push, 0, 0, 2)
    ZEND_ARG_INFO(0, score)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

PHP_METHOD(heapQueue, push)
{
	char *value;
	int charLen;
	long score;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),"ls", &score, &value, &charLen)  == FAILURE ) {
		RETURN_FALSE;
	}

	// switch (Z_TYPE_P(value)) {
	// 	case IS_STRING:
	// 		php_printf("IS_STRING::\n");
	// 		break;
	// 	case IS_INDIRECT:
	// 	    php_printf("IS_INDIRECT::\n");
	// 		break;
	// 	default:
	// 		break;
	// }
	php_printf("指针地址==%d\n", value);
	switch(heap_insert(heapTablePtr, (void *)value, (int)score)) {
		case 1:
		    //Z_TRY_ADDREF_P(value);//加一次引用计数
		    RETURN_TRUE;
			break;
		case -1:
		default:
		    zend_throw_exception(NULL, "insert value Failed to apply for memory", 0);

	}
}


/* 弹出一个数据 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_heapQueue_pop, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(heapQueue, pop)
{
	char *value;
	switch (heap_pop(heapTablePtr,(void **)&value))
	{
	case 0:
		RETURN_NULL();
		php_error_docref(NULL, E_WARNING, "获取出错");
		break;
	default:
	    /* */
		// switch(Z_TYPE_P(value)) {
		// 	case IS_NULL:
		// 	    RETURN_NULL();
		// 		//break;
		//     case IS_TRUE:
		// 		RETURN_TRUE;
		// 		//break;
		//     case IS_FALSE:
		// 		RETURN_FALSE;
		// 		//break;
		// 	case IS_INDIRECT:
		// 		//RETURN_LONG(Z_INDIRECT_P(value));
		// 		//break;
		// 		php_printf("IS_INDIRECT::\n");
		// 	case IS_ARRAY:
		// 		//RETURN_ARR(Z_ARR_P(value));
		// 		//break;
		// 	case IS_STRING:
		// 		//RETURN_STRING(Z_STR_P(value));
		// 		//break;
		// 		php_printf("IS_STRING::\n");
		// 	default:
		// 		RETVAL_ZVAL(value,0,1);
		// }
		RETURN_STRING(value);
		break;
	}
}

/* 获取现有队列大小 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_heapQueue_getSize, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(heapQueue, getSize)
{
	RETURN_LONG(heap_size(heapTablePtr));
}

/* 获取现有数据量 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_heapQueue_getNum, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(heapQueue, getNum)
{
	RETURN_LONG(heap_count(heapTablePtr));
}

/* 释放现有的数据 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_heapQueue_free, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(heapQueue, free)
{
	heap_free(heapTablePtr, 0);
}

/* 释放现有的数据 */
PHP_METHOD(heapQueue, __destruct)
{
	heap_free(heapTablePtr, 0);
}




/* {{{ heapQueue_functions[]
 *
 * Every user visible function must have an entry in heapQueue_functions[].
 */
const zend_function_entry heapQueue_functions[] = {
	/* 给对象注册方法，第三个参数表示参数信息，最后一个表示方法的可见行，私有|公有|受保护的 */
	PHP_ME(heapQueue,getVersion, arginfo_heapQueue_getVersion, ZEND_ACC_PUBLIC)
	PHP_ME(heapQueue,__construct, arginfo_heapQueue_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(heapQueue,push, arginfo_heapQueue_push, ZEND_ACC_PUBLIC)
	PHP_ME(heapQueue,pop, arginfo_heapQueue_pop, ZEND_ACC_PUBLIC)
    PHP_ME(heapQueue,getSize, arginfo_heapQueue_getSize, ZEND_ACC_PUBLIC)
	PHP_ME(heapQueue,getNum, arginfo_heapQueue_getNum, ZEND_ACC_PUBLIC)
	PHP_ME(heapQueue,free, arginfo_heapQueue_free, ZEND_ACC_PUBLIC)
	PHP_ME(heapQueue,__destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	//PHP_FE(confirm_heapQueue_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in heapQueue_functions[] */
};
/* }}} */


/* {{{ php_heapQueue_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_heapQueue_init_globals(zend_heapQueue_globals *heapQueue_globals)
{
	heapQueue_globals->global_value = 0;
	heapQueue_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(heapQueue)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
    zend_class_entry ce;
	/* 初始化 */
    INIT_CLASS_ENTRY(ce, heapQueueClassName, heapQueue_functions);
	/* 注册类 */
    heapQueuePtr = zend_register_internal_class(&ce);
	/* 注册一个私有属性代表版本号 */
	zend_declare_property_stringl(heapQueuePtr,"version", sizeof("version") - 1, PHP_HEAP_VER, sizeof(PHP_HEAP_VER) - 1, ZEND_ACC_PRIVATE);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(heapQueue)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	heap_free(heapTablePtr, 1);
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(heapQueue)
{
#if defined(COMPILE_DL_HEAPQUEUE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(heapQueue)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(heapQueue)
{
	/**
	 * phpinfo函数显示的信息
	 */ 
	php_info_print_table_start();
	php_info_print_table_header(2, "heapQueue support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */



/* {{{ heapQueue_module_entry
 */
zend_module_entry heapQueue_module_entry = {
	STANDARD_MODULE_HEADER,
	heapQueueClassName,
	heapQueue_functions,
	PHP_MINIT(heapQueue),
	PHP_MSHUTDOWN(heapQueue),
	PHP_RINIT(heapQueue),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(heapQueue),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(heapQueue),
	PHP_HEAPQUEUE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HEAPQUEUE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(heapQueue)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
