
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
PHALCON_INIT_CLASS(Phalcon_Http_Client_Response){

	PHALCON_REGISTER_CLASS(Phalcon\\Http, Client, http_client, phalcon_http_client_response_method_entry, 0);

	zend_declare_property_null(phalcon_http_client_response_ce, SL("_header") ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_http_client_response_ce, SL("_body") ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;
}

PHP_METHOD(Phalcon_Http_Client_Response, __construct){

	zval *header;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(header);
	object_init_ex(header, phalcon_http_client_header_ce);

	phalcon_update_property_this(this_ptr, SL("_header"), header TSRMLS_CC);

	PHALCON_MM_RESTORE();
}

PHP_METHOD(Phalcon_Http_Client_Response, getHeader){

	RETURN_MEMBER(this_ptr, "_header");
}

PHP_METHOD(Phalcon_Http_Client_Response, setBody){
	
	zval *body;

	phalcon_fetch_params(0, 1, 0, &body);

	phalcon_update_property_this(this_ptr, SL("_body"), body TSRMLS_CC);
}

PHP_METHOD(Phalcon_Http_Client_Response, getBody){

	RETURN_MEMBER(this_ptr, "_body");
}

