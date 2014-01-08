
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
#ifndef PHALCON_HTTP_CLIENT_RESPONSE_H
#define PHALCON_HTTP_CLIENT_RESPONSE_H

#include "php_phalcon.h"

extern zend_class_entry *phalcon_http_client_response_ce;

PHALCON_INIT_CLASS(Phalcon_Http_Client_Response);

PHP_METHOD(Phalcon_Http_Client_Response, __construct);
PHP_METHOD(Phalcon_Http_Client_Response, getHeader);
PHP_METHOD(Phalcon_Http_Client_Response, setBody);
PHP_METHOD(Phalcon_Http_Client_Response, getBody);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_response_setbody, 0, 0, 1)
	ZEND_ARG_INFO(0, body)
ZEND_END_ARG_INFO()

PHALCON_INIT_FUNCS(phalcon_http_client_response_method_entry){
	PHP_ME(Phalcon_Http_Client_Response, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) 
	PHP_ME(Phalcon_Http_Client_Response, getHeader, NULL, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Response, setBody, arginfo_phalcon_http_client_response_setbody, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Response, getBody, NULL, ZEND_ACC_PUBLIC) 
	PHP_FE_END
};

#endif /* PHALCON_HTTP_CLIENT_RESPONSE_H */

