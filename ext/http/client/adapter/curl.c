
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

#include "http/client/adapter/curl.h"

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

/**
 * Phalcon\Http\Client\Adapter\Curl
 */
zend_class_entry *phalcon_http_client_adapter_curl_ce;

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_adapter_curl___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, uri)
	ZEND_ARG_INFO(0, method)
ZEND_END_ARG_INFO()


PHALCON_INIT_FUNCS(phalcon_http_client_adapter_curl_method_entry){
	PHP_ME(Phalcon_Http_Client_Adapter, __construct, arginfo_phalcon_http_client_adapter_curl___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) 
	PHP_FE_END
};

/**
 * Phalcon\Http\Client\Adapter\Curl initializer
 */
PHALCON_INIT_CLASS(Phalcon_Http_Client_Adapter_Curl){

	PHALCON_REGISTER_CLASS_EX(Phalcon\\Http\\Client\\Adapter, Curl, http_client_adapter_gd, phalcon_http_client_adapter_ce,  phalcon_http_client_adapter_curl_method_entry, 0);

	zend_class_implements(phalcon_http_client_adapter_curl_ce TSRMLS_CC, 1, phalcon_http_client_adapterinterface_ce);

	return SUCCESS;
}

PHP_METHOD(Phalcon_Http_Client_Adapter_Curl, __construct){

	zval *uri = NULL, *method = NULL, *base_uri;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 1, 1, &uri, &method);

	PHALCON_INIT_VAR(base_uri);
	object_init_ex(base_uri, phalcon_http_uri_ce);
	PHALCON_CALL_METHOD(NULL, uri, "__construct", uri);

	phalcon_update_property_this(this_ptr, SL("_base_uri"), base_uri TSRMLS_CC);

	if (method) {
		phalcon_update_property_this(this_ptr, SL("_method"), method TSRMLS_CC);
	}

	PHALCON_INIT_VAR(header);
	object_init_ex(header, phalcon_http_client_header_ce);

	phalcon_update_property_this(this_ptr, SL("_header"), header TSRMLS_CC);

	PHALCON_MM_RESTORE();
}

