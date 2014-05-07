
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
#include "request.h"

/**
 * Phalcon\Http\Client\Request
 */


/**
 * Phalcon\Http\Client\Header initializer
 */
PHALCON_INIT_CLASS(Phalcon_Http_Client_Request){

	PHALCON_REGISTER_CLASS(Phalcon\\Http, Client, http_client, phalcon_http_client_request_method_entry, 0);

	zend_declare_property_null(phalcon_http_client_request_ce, SL("_base_uri") ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_http_client_request_ce, SL("_header") ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_stringl(phalcon_http_client_request_ce, SL("VERSION"), SL("0.0.1") TSRMLS_CC);

	return SUCCESS;
}

PHP_METHOD(Phalcon_Http_Client_Request, __construct){

	zval *uri, *header;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(uri);
	object_init_ex(uri, phalcon_http_uri_ce);
	PHALCON_CALL_METHOD(NULL, uri, "__construct");

	phalcon_update_property_this(this_ptr, SL("_base_uri"), uri TSRMLS_CC);

	PHALCON_INIT_VAR(header);
	object_init_ex(header, phalcon_http_client_header_ce);

	phalcon_update_property_this(this_ptr, SL("_header"), header TSRMLS_CC);

	PHALCON_MM_RESTORE();
}

PHP_METHOD(Phalcon_Http_Client_Request, getProvider){

}

PHP_METHOD(Phalcon_Http_Client_Request, getHeader){

	RETURN_MEMBER(this_ptr, "_header");
}

PHP_METHOD(Phalcon_Http_Client_Request, setBaseUri){

}

PHP_METHOD(Phalcon_Http_Client_Request, getBaseUri){

}

PHP_METHOD(Phalcon_Http_Client_Request, resolveUri){

}

