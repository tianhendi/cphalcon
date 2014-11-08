
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
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
  +------------------------------------------------------------------------+
*/

#include "mvc/model/behavior/nestedset.h"
#include "mvc/model/behavior.h"
#include "mvc/model/behaviorinterface.h"
#include "mvc/model/exception.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/object.h"

/**
 * Phalcon\Mvc\Model\Behavior\NestedSet
 *
 */
zend_class_entry *phalcon_mvc_model_behavior_nestedset_ce;

PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, __construct);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, notify);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, missingMethod);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, getOwner);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, setOwner);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, getIsNewRecord);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, getIsDeletedRecord);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, setIsDeletedRecord);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, isLeaf);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, isRoot);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, contains);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, descendants);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, children);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, ancestors);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, roots);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, root);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, parent);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, prev);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, next);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, prependTo);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, prepend);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, appendTo);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, append);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, insertBefore);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, insertAfter);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, remove);
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, makeRoot);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_missingmethod, 0, 0, 2)
	ZEND_ARG_INFO(0, model)
	ZEND_ARG_INFO(0, method)
	ZEND_ARG_INFO(0, arguments)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_setowner, 0, 0, 1)
	ZEND_ARG_INFO(0, owner)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_descendants, 0, 0, 0)
	ZEND_ARG_INFO(0, depth)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_ancestors, 0, 0, 0)
	ZEND_ARG_INFO(0, depth)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_prependto, 0, 0, 1)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_prepend, 0, 0, 1)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_appendto, 0, 0, 1)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_append, 0, 0, 1)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_insertbefore, 0, 0, 1)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_behavior_nestedset_insertafter, 0, 0, 1)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()
static const zend_function_entry phalcon_mvc_model_behavior_nestedset_method_entry[] = {
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, __construct, arginfo_phalcon_mvc_model_behavior_nestedset___construct, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, notify, arginfo_phalcon_mvc_model_behaviorinterface_notify, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, missingMethod, arginfo_phalcon_mvc_model_behavior_nestedset_missingmethod, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, getOwner, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, setOwner, arginfo_phalcon_mvc_model_behavior_nestedset_setowner, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, isLeaf, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, isRoot, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, contains, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, descendants, arginfo_phalcon_mvc_model_behavior_nestedset_descendants, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, children, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, ancestors, arginfo_phalcon_mvc_model_behavior_nestedset_ancestors, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, roots, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, root, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, parent, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, prev, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, prependTo, arginfo_phalcon_mvc_model_behavior_nestedset_prependto, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, prepend, arginfo_phalcon_mvc_model_behavior_nestedset_prepend, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, appendTo, arginfo_phalcon_mvc_model_behavior_nestedset_appendto, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, append, arginfo_phalcon_mvc_model_behavior_nestedset_append, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, insertBefore, arginfo_phalcon_mvc_model_behavior_nestedset_insertbefore, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, insertAfter, arginfo_phalcon_mvc_model_behavior_nestedset_insertafter, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, remove, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Behavior_NestedSet, makeRoot, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

/**
 * Phalcon\Mvc\Model\Behavior\NestedSet initializer
 */
PHALCON_INIT_CLASS(Phalcon_Mvc_Model_Behavior_NestedSet){

	PHALCON_REGISTER_CLASS_EX(Phalcon\\Mvc\\Model\\Behavior, NestedSet, mvc_model_behavior_nestedset, phalcon_mvc_model_behavior_ce, phalcon_mvc_model_behavior_nestedset_method_entry, 0);

	zend_declare_property_null(phalcon_mvc_model_behavior_nestedset_ce, SL("_model"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(phalcon_mvc_model_behavior_nestedset_ce, SL("_hasManyRoots"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_mvc_model_behavior_nestedset_ce, SL("_rootAttribute"), "root", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_mvc_model_behavior_nestedset_ce, SL("_leftAttribute"), "left", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_mvc_model_behavior_nestedset_ce, SL("_rightAttribute"), "right", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_mvc_model_behavior_nestedset_ce, SL("_levelAttribute"), "level", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_behavior_nestedset_ce, SL("_primaryKey"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(phalcon_mvc_model_behavior_nestedset_ce TSRMLS_CC, 1, phalcon_mvc_model_behaviorinterface_ce);

	return SUCCESS;
}

PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, __construct){

	zval *options = NULL, *option = NULL;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 0, 1, &options);

	if (phalcon_array_isset_string(options, SS("hasManyRoots"))) {
		PHALCON_OBS_NVAR(option);
		phalcon_array_fetch_string(&option, options, SL("hasManyRoots"), PH_NOISY);

		phalcon_update_property_this(this_ptr, SL("_hasManyRoots"), option TSRMLS_CC);
	}

	if (phalcon_array_isset_string(options, SS("rootAttribute"))) {
		PHALCON_OBS_NVAR(option);
		phalcon_array_fetch_string(&option, options, SL("rootAttribute"), PH_NOISY);

		phalcon_update_property_this(this_ptr, SL("_rootAttribute"), option TSRMLS_CC);
	}

	if (phalcon_array_isset_string(options, SS("leftAttribute"))) {
		PHALCON_OBS_NVAR(option);
		phalcon_array_fetch_string(&option, options, SL("leftAttribute"), PH_NOISY);

		phalcon_update_property_this(this_ptr, SL("_leftAttribute"), option TSRMLS_CC);
	}

	if (phalcon_array_isset_string(options, SS("rightAttribute"))) {
		PHALCON_OBS_NVAR(option);
		phalcon_array_fetch_string(&option, options, SL("rightAttribute"), PH_NOISY);

		phalcon_update_property_this(this_ptr, SL("_rightAttribute"), option TSRMLS_CC);
	}

	if (phalcon_array_isset_string(options, SS("levelAttribute"))) {
		PHALCON_OBS_NVAR(option);
		phalcon_array_fetch_string(&option, options, SL("levelAttribute"), PH_NOISY);

		phalcon_update_property_this(this_ptr, SL("_levelAttribute"), option TSRMLS_CC);
	}

	if (phalcon_array_isset_string(options, SS("primaryKey"))) {
		PHALCON_OBS_NVAR(option);
		phalcon_array_fetch_string(&option, options, SL("primaryKey"), PH_NOISY);

		phalcon_update_property_this(this_ptr, SL("_primaryKey"), option TSRMLS_CC);
	}

	PHALCON_MM_RESTORE();
}

/**
 * Listens for notifications from the models manager
 *
 * @param string $type
 * @param Phalcon\Mvc\ModelInterface $model
 */
PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, notify){

	zval *type, *model;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 2, 0, &type, &model);

	if (PHALCON_IS_STRING(type, "beforeCreate")) {
	} else if (PHALCON_IS_STRING(type, "beforeUpdate")) {
	} else if (PHALCON_IS_STRING(type, "beforeDelete")) {
	}

	PHALCON_MM_RESTORE();
}

PHP_METHOD(Phalcon_Mvc_Model_Behavior_NestedSet, missingMethod){

	zval *model, *method, *arguments = NULL;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 2, 1, &model, &method, &arguments);

	PHALCON_MM_RESTORE();
}

