
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

#include "http/client/adapter.h"
#include "http/client/adapterinterface.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/file.h"

/**
 * Phalcon\Http\Client\Adapter
 */
zend_class_entry *phalcon_http_client_adapter_ce; 

PHP_METHOD(Phalcon_Http_Client_Adapter, __construct);
PHP_METHOD(Phalcon_Http_Client_Adapter, setUserAgent);
PHP_METHOD(Phalcon_Http_Client_Adapter, setAuthentication);
PHP_METHOD(Phalcon_Http_Client_Adapter, setHeaders);
PHP_METHOD(Phalcon_Http_Client_Adapter, setCookies);
PHP_METHOD(Phalcon_Http_Client_Adapter, setContentType);
PHP_METHOD(Phalcon_Http_Client_Adapter, setData);
PHP_METHOD(Phalcon_Http_Client_Adapter, setFile);
PHP_METHOD(Phalcon_Http_Client_Adapter, get);
PHP_METHOD(Phalcon_Http_Client_Adapter, head);
PHP_METHOD(Phalcon_Http_Client_Adapter, post);
PHP_METHOD(Phalcon_Http_Client_Adapter, put);
PHP_METHOD(Phalcon_Http_Client_Adapter, delete);
PHP_METHOD(Phalcon_Http_Client_Adapter, setUri)
PHP_METHOD(Phalcon_Http_Client_Adapter, setMethod)
PHP_METHOD(Phalcon_Http_Client_Adapter, send);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_adapter___construct, 0, 0, 0)
	ZEND_ARG_INFO(1, uri)
	ZEND_ARG_INFO(0, method)
ZEND_END_ARG_INFO()

PHALCON_INIT_FUNCS(phalcon_http_client_adapter_method_entry){
	PHP_ME(Phalcon_Http_Client_Adapter, __construct, arginfo_phalcon_http_client_adapter___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) 
	PHP_ME(Phalcon_Http_Client_Adapter, setUserAgent, arginfo_phalcon_http_client_adapterinterface_setuseragent, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Adapter, setAuthentication, arginfo_phalcon_http_client_adapterinterface_setauthentication, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, setHeaders, arginfo_phalcon_http_client_adapterinterface_setheaders, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, setCookies, arginfo_phalcon_http_client_adapterinterface_setcookies, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, setContentType, arginfo_phalcon_http_client_adapterinterface_setcontenttype, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, setData, arginfo_phalcon_http_client_adapterinterface_setdata, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, setFile, arginfo_phalcon_http_client_adapterinterface_setfile, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, get, arginfo_phalcon_http_client_adapterinterface_get, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, head, arginfo_phalcon_http_client_adapterinterface_head, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, post, arginfo_phalcon_http_client_adapterinterface_post, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, put, arginfo_phalcon_http_client_adapterinterface_put, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, delete, arginfo_phalcon_http_client_adapterinterface_delete, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, setUri, arginfo_phalcon_http_client_adapterinterface_seturi, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, setMethod, arginfo_phalcon_http_client_adapterinterface_setmethod, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Http_Client_Adapter, send, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

/**
 * Phalcon\Http\Client\Adapter initializer
 */
PHALCON_INIT_CLASS(Phalcon_Http_Client_Adapter){

	PHALCON_REGISTER_CLASS(Phalcon\\Http\\Client, Adapter, http_client_adapter, phalcon_http_client_adapter_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(phalcon_http_client_adapter_ce, SL("_header") ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_http_client_adapter_ce, SL("_base_uri") ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_http_client_adapter_ce, SL("_method"), "GET", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_stringl(phalcon_http_client_adapter_ce, SL("VERSION"), SL("0.0.1") TSRMLS_CC);

	zend_class_implements(phalcon_http_client_adapter_ce TSRMLS_CC, 1, phalcon_http_client_adapterinterface_ce);

	return SUCCESS;
}

PHP_METHOD(Phalcon_Http_Client_Adapter, __construct){

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

PHP_METHOD(Phalcon_Http_Client_Adapter, setUserAgent){

}

PHP_METHOD(Phalcon_Http_Client_Adapter, setAuthentication){

}

PHP_METHOD(Phalcon_Http_Client_Adapter, setHeaders){

}

PHP_METHOD(Phalcon_Http_Client_Adapter, setCookies){

}

PHP_METHOD(Phalcon_Http_Client_Adapter, setContentType){

}

PHP_METHOD(Phalcon_Http_Client_Adapter, setData){

}

PHP_METHOD(Phalcon_Http_Client_Adapter, setFile){

}

PHP_METHOD(Phalcon_Http_Client_Adapter, get){

	phalcon_update_property_string(this_ptr, SL("_method"), SL("GET") TSRMLS_CC);

	PHALCON_CALL_METHOD(NULL, this_ptr, "send");

	RETURN_THIS();
}

PHP_METHOD(Phalcon_Http_Client_Adapter, head){

	phalcon_update_property_string(this_ptr, SL("_method"), SL("HEAD") TSRMLS_CC);

	PHALCON_CALL_METHOD(NULL, this_ptr, "send");

	RETURN_THIS();
}

PHP_METHOD(Phalcon_Http_Client_Adapter, post){

	phalcon_update_property_string(this_ptr, SL("_method"), SL("POST") TSRMLS_CC);

	PHALCON_CALL_METHOD(NULL, this_ptr, "send");

	RETURN_THIS();
}

PHP_METHOD(Phalcon_Http_Client_Adapter, put){

	phalcon_update_property_string(this_ptr, SL("_method"), SL("PUT") TSRMLS_CC);

	PHALCON_CALL_METHOD(NULL, this_ptr, "send");

	RETURN_THIS();
}

PHP_METHOD(Phalcon_Http_Client_Adapter, delete){

	phalcon_update_property_string(this_ptr, SL("_method"), SL("DELETE") TSRMLS_CC);

	PHALCON_CALL_METHOD(NULL, this_ptr, "send");

	RETURN_THIS();
}

PHP_METHOD(Phalcon_Http_Client_Adapter, setUri){

	zval *uri;

	phalcon_fetch_params(0, 1, 0, &uri);

	phalcon_update_property_this(this_ptr, SL("_base_uri"), uri TSRMLS_CC);
}

PHP_METHOD(Phalcon_Http_Client_Adapter, setMethod){

	zval *method;

	phalcon_fetch_params(0, 1, 0, &method);

	phalcon_update_property_this(this_ptr, SL("_method"), method TSRMLS_CC);
}

PHP_METHOD(Phalcon_Http_Client_Adapter, send){

}

