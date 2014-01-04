
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  |          ZhuZongXin <dreamsxin@qq.com>                                 |
  +------------------------------------------------------------------------+
*/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "ext/spl/spl_iterators.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/file.h"
#include "kernel/hash.h"
#include "kernel/string.h"

#include "header.h"

/**
 * Phalcon\Http\Client\Header
 */


/**
 * Phalcon\Http\Client\Header initializer
 */
PHALCON_INIT_CLASS(Phalcon_Http_Client_Header){

	PHALCON_REGISTER_CLASS(Phalcon\\Http, Client, http_client, phalcon_http_client_header_method_entry, 0);
	//PHALCON_REGISTER_CLASS(Phalcon\\Http, Client, http_client, phalcon_http_client_header_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zval *messages;
	MAKE_STD_ZVAL(messages);
	array_init(messages);
	//array_init_size(messages, 41);

	phalcon_array_update_long_string(&messages, 100, SL("Continue"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 101, SL("Switching Protocols"), PH_SEPARATE);

	phalcon_array_update_long_string(&messages, 200, SL("OK"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 201, SL("Created"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 202, SL("Accepted"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 203, SL("Non-Authoritative Information"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 204, SL("No Content"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 205, SL("Reset Content"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 206, SL("Partial Content"), PH_SEPARATE);

	phalcon_array_update_long_string(&messages, 300, SL("Multiple Choices"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 301, SL("Moved Permanently"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 302, SL("Found"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 303, SL("See Other"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 304, SL("Not Modified"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 305, SL("Use Proxy"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 306, SL("(Unused)"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 307, SL("Temporary Redirect"), PH_SEPARATE);

	phalcon_array_update_long_string(&messages, 400, SL("Bad Request"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 401, SL("Unauthorized"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 402, SL("Payment Required"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 403, SL("Forbidden"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 404, SL("Not Found"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 405, SL("Method Not Allowed"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 406, SL("Not Acceptable"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 407, SL("Proxy Authentication Required"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 408, SL("Request Timeout"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 409, SL("Conflict"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 410, SL("Gone"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 411, SL("Length Required"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 412, SL("Precondition Failed"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 413, SL("Request Entity Too Large"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 414, SL("Request-URI Too Long"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 415, SL("Unsupported Media Type"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 416, SL("Requested Range Not Satisfiable"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 417, SL("Expectation Failed"), PH_SEPARATE);
	
	phalcon_array_update_long_string(&messages, 500, SL("Internal Server Error"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 501, SL("Not Implemented"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 502, SL("Bad Gateway"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 503, SL("Service Unavailable"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 504, SL("Gateway Timeout"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 505, SL("HTTP Version Not Supported"), PH_SEPARATE);
	phalcon_array_update_long_string(&messages, 506, SL("Bandwidth Limit Exceeded"), PH_SEPARATE);

	zend_declare_property(phalcon_http_client_header_ce, SL("_messages"), messages, ZEND_ACC_PROTECTED TSRMLS_CC);

	zval_ptr_dtor(&messages);

	zval *fields;
	MAKE_STD_ZVAL(fields);
	array_init(fields);

	zend_declare_property(phalcon_http_client_header_ce, SL("_fields"), fields, ZEND_ACC_PROTECTED TSRMLS_CC);

	zval_ptr_dtor(&fields);

	zend_declare_property_long(phalcon_http_client_header_ce, SL("_version"), 1, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(phalcon_http_client_header_ce, SL("_status_code"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_http_client_header_ce, SL("_status_message") ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_http_client_header_ce, SL("_status") ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_image_ce, SL("BUILD_STATUS"), PHALCON_HTTP_CLIENT_HEADER_BUILD_STATUS TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_image_ce, SL("BUILD_FIELDS"), PHALCON_HTTP_CLIENT_HEADER_BUILD_FIELDS TSRMLS_CC);

	zend_class_implements(phalcon_http_client_header_ce TSRMLS_CC, 1, spl_ce_Countable);

	return SUCCESS;
}

PHP_METHOD(Phalcon_Http_Client_Header, set){

	zval *name, *value, *fields;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 2, 0, &name, &value);

	PHALCON_OBS_VAR(fields);
	phalcon_read_property_this(&fields, this_ptr, SL("_fields"), PH_NOISY_CC);

	phalcon_array_update_zval(&fields, key, &value, PH_COPY);
	phalcon_update_property_this(this_ptr, SL("_fields"), fields TSRMLS_CC);

	RETURN_MM();
}

PHP_METHOD(Phalcon_Http_Client_Header, setMultiple){

	zval *values;

	phalcon_fetch_params(0, 1, 0, &values);

	phalcon_update_property_this(this_ptr, SL("_fields"), values TSRMLS_CC);
}

PHP_METHOD(Phalcon_Http_Client_Header, addMultiple){

	zval *values, *fields;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 1, 0, &values);

	PHALCON_OBS_VAR(fields);
	phalcon_read_property_this(&fields, this_ptr, SL("_fields"), PH_NOISY_CC);

	phalcon_merge_append(fields, values);

	phalcon_update_property_this(this_ptr, SL("_fields"), fields TSRMLS_CC);

	RETURN_MM();
}

PHP_METHOD(Phalcon_Http_Client_Header, get){

	zval *name, *field;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 1, 0, &name);

	PHALCON_OBS_VAR(fields);
	phalcon_read_property_this(&fields, this_ptr, SL("_fields"), PH_NOISY_CC);

	PHALCON_OBS_VAR(field);
	phalcon_array_fetch(&field, fields, name, PH_NOISY);

	RETURN_CTOR(field);
}

PHP_METHOD(Phalcon_Http_Client_Header, getAll){

	RETURN_MEMBER(this_ptr, "_fields");
}
