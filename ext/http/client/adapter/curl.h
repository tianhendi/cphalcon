
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
#ifndef PHALCON_HTTP_CLIENT_ADAPTER_CURL_H
#define PHALCON_HTTP_CLIENT_ADAPTER_CURL_H

#include "php_phalcon.h"

extern zend_class_entry *phalcon_http_client_adapter_curl_ce;

PHALCON_INIT_CLASS(Phalcon_Http_Client_Adapter_Curl);

PHP_METHOD(Phalcon_Http_Client_Adapter_Curl, __construct);
PHP_METHOD(Phalcon_Http_Client_Adapter_Curl, getProvider);
PHP_METHOD(Phalcon_Http_Client_Adapter_Curl, getHeader);
PHP_METHOD(Phalcon_Http_Client_Adapter_Curl, setBaseUri);
PHP_METHOD(Phalcon_Http_Client_Adapter_Curl, getBaseUri);
PHP_METHOD(Phalcon_Http_Client_Adapter_Curl, resolveUri);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_adapter_curl_setbaseuri, 0, 0, 1)
	ZEND_ARG_INFO(0, uri)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_adapter_curl_resolveuri, 0, 0, 1)
	ZEND_ARG_INFO(0, uri)
ZEND_END_ARG_INFO()

PHALCON_INIT_FUNCS(phalcon_http_client_adapter_curl_method_entry){
	PHP_ME(Phalcon_Http_Client_Adapter_Curl, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) 
	PHP_ME(Phalcon_Http_Client_Adapter_Curl, getProvider, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) 
	PHP_ME(Phalcon_Http_Client_Adapter_Curl, getHeader, NULL, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Adapter_Curl, setBaseUri, arginfo_phalcon_http_client_adapter_curl_setbaseuri, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Adapter_Curl, getBaseUri, NULL, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Adapter_Curl, resolveUri, arginfo_phalcon_http_client_adapter_curl_resolveuri, ZEND_ACC_PUBLIC) 
	PHP_FE_END
};

#endif /* PHALCON_HTTP_CLIENT_ADAPTER_CURL_H */

