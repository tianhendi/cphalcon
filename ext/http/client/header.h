
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
#ifndef PHALCON_HTTP_CLIENT_HEADER_H
#define PHALCON_HTTP_CLIENT_HEADER_H

#include "php_phalcon.h"

#define PHALCON_HTTP_CLIENT_HEADER_BUILD_STATUS    1
#define PHALCON_HTTP_CLIENT_HEADER_BUILD_FIELDS    2

extern zend_class_entry *phalcon_http_client_header_ce;

PHALCON_INIT_CLASS(Phalcon_Http_Client_Header);

PHP_METHOD(Phalcon_Http_Client_Header, set);
PHP_METHOD(Phalcon_Http_Client_Header, setMultiple);
PHP_METHOD(Phalcon_Http_Client_Header, addMultiple);
PHP_METHOD(Phalcon_Http_Client_Header, get);
PHP_METHOD(Phalcon_Http_Client_Header, getAll);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_header_set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_header_setmultiple, 0, 0, 1)
	ZEND_ARG_INFO(0, values)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_header_addmultiple, 0, 0, 1)
	ZEND_ARG_INFO(0, values)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_http_client_header_get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()


PHALCON_INIT_FUNCS(phalcon_http_client_header_method_entry){
	PHP_ME(Phalcon_Http_Client_Header, set, arginfo_phalcon_http_client_header_set, ZEND_ACC_PUBLIC) 
	//PHP_ME(Phalcon_Http_Client_Header, set, arginfo_phalcon_http_client_header_set, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) 
	PHP_ME(Phalcon_Http_Client_Header, setMultiple, arginfo_phalcon_http_client_header_setmultiple, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Header, addMultiple, arginfo_phalcon_http_client_header_addmultiple, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Header, get, arginfo_phalcon_http_client_header_get, ZEND_ACC_PUBLIC) 
	PHP_ME(Phalcon_Http_Client_Header, getAll, NULL, ZEND_ACC_PUBLIC) 
	PHP_FE_END
};

#endif /* PHALCON_HTTP_CLIENT_HEADER_H */

