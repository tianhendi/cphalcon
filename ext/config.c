
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

#include "pconfig.h"
#include "config/exception.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/hash.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/array.h"

#include "internal/arginfo.h"

/**
 * Phalcon\Config
 *
 * Phalcon\Config is designed to simplify the access to, and the use of, configuration data within applications.
 * It provides a nested object property based user interface for accessing this configuration data within
 * application code.
 *
 *<code>
 *	$config = new Phalcon\Config(array(
 *		"database" => array(
 *			"adapter" => "Mysql",
 *			"host" => "localhost",
 *			"username" => "scott",
 *			"password" => "cheetah",
 *			"dbname" => "test_db"
 *		),
 *		"phalcon" => array(
 *			"controllersDir" => "../app/controllers/",
 *			"modelsDir" => "../app/models/",
 *			"viewsDir" => "../app/views/"
 *		)
 * ));
 *</code>
 *
 */
zend_class_entry *phalcon_config_ce;

PHP_METHOD(Phalcon_Config, __construct);
PHP_METHOD(Phalcon_Config, offsetExists);
PHP_METHOD(Phalcon_Config, get);
PHP_METHOD(Phalcon_Config, offsetGet);
PHP_METHOD(Phalcon_Config, offsetSet);
PHP_METHOD(Phalcon_Config, offsetUnset);
PHP_METHOD(Phalcon_Config, merge);
PHP_METHOD(Phalcon_Config, toArray);
PHP_METHOD(Phalcon_Config, count);
PHP_METHOD(Phalcon_Config, __wakeup);
PHP_METHOD(Phalcon_Config, __set_state);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_config___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, arrayConfig)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_config_get, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_config_merge, 0, 0, 1)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_config_toarray, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_config___wakeup, 0, 0, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry phalcon_config_method_entry[] = {
	PHP_ME(Phalcon_Config, __construct, arginfo_phalcon_config___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Phalcon_Config, offsetExists, arginfo_arrayaccess_offsetexists, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, get, arginfo_phalcon_config_get, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, offsetGet, arginfo_arrayaccess_offsetget, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, offsetSet, arginfo_arrayaccess_offsetset, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, offsetUnset, arginfo_arrayaccess_offsetunset, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, merge, arginfo_phalcon_config_merge, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, toArray, arginfo_phalcon_config_toarray, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, count, arginfo_countable_count, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, __wakeup, arginfo_phalcon_config___wakeup, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Config, __set_state, arginfo___set_state, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_MALIAS(Phalcon_Config, __get, offsetGet, arginfo___get, ZEND_ACC_PUBLIC)
	PHP_MALIAS(Phalcon_Config, __set, offsetSet, arginfo___set, ZEND_ACC_PUBLIC)
	PHP_MALIAS(Phalcon_Config, __isset, offsetExists, arginfo___isset, ZEND_ACC_PUBLIC)
	PHP_MALIAS(Phalcon_Config, __unset, offsetUnset, arginfo___unset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


static zend_object_handlers phalcon_config_object_handlers;

typedef struct _phalcon_config_object {
	zend_object obj;  /**< Zend object data */
	HashTable* props; /**< Properties */
} phalcon_config_object;

/**
 * @brief Fetches @c phalcon_config_object
 * @see phalcon_config_object
 * @param zobj @c \Phalcon\Config instance
 * @return phalcon_config_object associated with @a zobj
 */
static inline phalcon_config_object* fetchPhalconConfigObject(zval* zobj TSRMLS_DC)
{
	return (phalcon_config_object*)zend_objects_get_address(zobj TSRMLS_CC);
}

/**
 * @brief Counts the number of elements in the configuration; this is the part of Countable interface
 */
static int phalcon_config_count_elements(zval *object, long int *count TSRMLS_DC)
{
	phalcon_config_object* obj = fetchPhalconConfigObject(object TSRMLS_CC);
	*count = zend_hash_num_elements(obj->props);
	return SUCCESS;
}

/**
 * @brief Common part of @c __get() and @c offsetGet()
 */
static zval* phalcon_config_read_internal(phalcon_config_object *object, zval *key, int type TSRMLS_DC)
{
	zval **retval;

	if (UNEXPECTED(!key) || Z_TYPE_P(key) == IS_NULL) {
		return EG(uninitialized_zval_ptr);
	}

	retval = phalcon_hash_get(object->props, key, type);
	return retval ? *retval : NULL;
}

/**
 * @brief @c read_property handler, used instead of @c __get() magic method
 */
static zval* phalcon_config_read_property(zval *object, zval *offset, int type ZLK_DC TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		if (BP_VAR_IS == type && !zend_get_std_object_handlers()->has_property(object, offset, 0 ZLK_CC TSRMLS_CC)) {
			return EG(uninitialized_zval_ptr);
		}

		return zend_get_std_object_handlers()->read_property(object, offset, type ZLK_CC TSRMLS_CC);
	}

	return phalcon_config_read_internal(obj, offset, type TSRMLS_CC);
}

/**
 * @brief @c read_dimension handler, used instead of @c offsetGet() method
 */
static zval* phalcon_config_read_dimension(zval *object, zval *offset, int type TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		if (BP_VAR_IS == type && !zend_get_std_object_handlers()->has_dimension(object, offset, 0 TSRMLS_CC)) {
			return EG(uninitialized_zval_ptr);
		}

		return zend_get_std_object_handlers()->read_dimension(object, offset, type TSRMLS_CC);
	}

	return phalcon_config_read_internal(obj, offset, type TSRMLS_CC);
}

/**
 * @brief Common part of @c __set() and @c offsetSet()
 */
static void phalcon_config_write_internal(phalcon_config_object *object, zval *offset, zval *value TSRMLS_DC)
{
	if (Z_TYPE_P(value) == IS_ARRAY) {
		zval *instance;
		HashTable *h = Z_ARRVAL_P(value);

		if (!h->nApplyCount) {
			++h->nApplyCount;
			MAKE_STD_ZVAL(instance);
			object_init_ex(instance, phalcon_config_ce);
			phalcon_config_construct_internal(instance, value TSRMLS_CC);
			phalcon_hash_update_or_insert(object->props, offset, instance);
			--h->nApplyCount;
		}
		else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Recursion detected");
		}
	}
	else {
		Z_ADDREF_P(value);
		phalcon_hash_update_or_insert(object->props, offset, value);
	}
}

/**
 * @brief @c write_property handler, used instead of @c __set() magic method
 */
static void phalcon_config_write_property(zval *object, zval *offset, zval *value ZLK_DC TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		zend_get_std_object_handlers()->write_property(object, offset, value ZLK_CC TSRMLS_CC);
		return;
	}

	phalcon_config_write_internal(obj, offset, value TSRMLS_CC);
}

/**
 * @brief @c write_dimension handler, used instead of @c offsetSet() method
 */
static void phalcon_config_write_dimension(zval *object, zval *offset, zval *value TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		zend_get_std_object_handlers()->write_dimension(object, offset, value TSRMLS_CC);
		return;
	}

	phalcon_config_write_internal(obj, offset, value TSRMLS_CC);
}

/**
 * @brief Common part of @c __isset() and @c offsetExists()
 */
static int phalcon_config_has_internal(phalcon_config_object *object, zval *key, int check_empty TSRMLS_DC)
{
	zval **tmp = phalcon_hash_get(object->props, key, BP_VAR_NA);

	if (!tmp) {
		return 0;
	}

	if (0 == check_empty) {
		return Z_TYPE_PP(tmp) != IS_NULL;
	}

	if (1 == check_empty) {
		return zend_is_true(*tmp);
	}

	return 1;
}

static int phalcon_config_has_property(zval *object, zval *offset, int has_set_exists ZLK_DC TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		return zend_get_std_object_handlers()->has_property(object, offset, has_set_exists ZLK_CC TSRMLS_CC);
	}

	return phalcon_config_has_internal(obj, offset, 0 TSRMLS_CC);
}

static int phalcon_config_has_dimension(zval *object, zval *offset, int check_empty TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		return zend_get_std_object_handlers()->has_dimension(object, offset, check_empty TSRMLS_CC);
	}

	return phalcon_config_has_internal(obj, offset, check_empty TSRMLS_CC);
}

/**
 * @brief Common part of @c __unset() and @c offsetUnset()
 */
static void phalcon_config_unset_internal(phalcon_config_object *obj, zval *key TSRMLS_DC)
{
	phalcon_hash_unset(obj->props, key);
}

static void phalcon_config_unset_property(zval *object, zval *member ZLK_DC TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		zend_get_std_object_handlers()->unset_property(object, member ZLK_CC TSRMLS_CC);
		return;
	}

	phalcon_config_unset_internal(obj, member TSRMLS_CC);
}

static void phalcon_config_unset_dimension(zval *object, zval *offset TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(object TSRMLS_CC);

	if (!is_phalcon_class(obj->obj.ce)) {
		zend_get_std_object_handlers()->unset_dimension(object, offset TSRMLS_CC);
		return;
	}

	phalcon_config_unset_internal(obj, offset TSRMLS_CC);
}

/**
 * @brief Returns the list of all internal properties. Used by @c print_r() and other functions
 */
static HashTable* phalcon_config_get_properties(zval* object TSRMLS_DC)
{
	HashTable* props = zend_std_get_properties(object TSRMLS_CC);

	if (!GC_G(gc_active)) {
		phalcon_config_object* obj = fetchPhalconConfigObject(object TSRMLS_CC);
		zend_hash_copy(props, obj->props, (copy_ctor_func_t)zval_add_ref, NULL, sizeof(zval*));
	}

	return props;
}

/**
 * @brief Fast object compare function
 */
static int phalcon_config_compare_objects(zval *object1, zval *object2 TSRMLS_DC)
{
	phalcon_config_object *zobj1, *zobj2;
	zval result;

	zobj1 = fetchPhalconConfigObject(object1 TSRMLS_CC);
	zobj2 = fetchPhalconConfigObject(object2 TSRMLS_CC);

	if (zobj1->obj.ce != zobj2->obj.ce) {
		return 1;
	}

	if (zobj1->props == zobj2->props) {
		return 0;
	}

	zend_compare_symbol_tables(&result, zobj1->props, zobj2->props TSRMLS_CC);
	assert(Z_TYPE_P(&result) == IS_LONG);
	return Z_LVAL_P(&result);
}

/**
 * @brief Frees all memory associated with @c phalcon_config_object
 */
static void phalcon_config_object_dtor(void* v TSRMLS_DC)
{
	phalcon_config_object* obj = v;

	zend_hash_destroy(obj->props);
	FREE_HASHTABLE(obj->props);
	zend_object_std_dtor(&(obj->obj) TSRMLS_CC);
	efree(obj);
}

/**
 * @brief Constructs @c phalcon_config_object
 */
static zend_object_value phalcon_config_object_ctor(zend_class_entry* ce TSRMLS_DC)
{
	phalcon_config_object *obj = ecalloc(1, sizeof(phalcon_config_object));
	zend_object_value retval;

	zend_object_std_init(&obj->obj, ce TSRMLS_CC);
	object_properties_init(&obj->obj, ce);

	ALLOC_HASHTABLE(obj->props);
	zend_hash_init(obj->props, 0, NULL, ZVAL_PTR_DTOR, 0);

	retval.handle = zend_objects_store_put(
		obj,
		(zend_objects_store_dtor_t)zend_objects_destroy_object,
		phalcon_config_object_dtor,
		NULL
		TSRMLS_CC
	);

	retval.handlers = &phalcon_config_object_handlers;

	return retval;
}

static zend_object_value phalcon_config_clone_obj(zval *object TSRMLS_DC)
{
	phalcon_config_object *orig  = fetchPhalconConfigObject(object TSRMLS_CC);
	zend_object_value result     = phalcon_config_object_ctor(Z_OBJCE_P(object) TSRMLS_CC);
	phalcon_config_object *clone = zend_object_store_get_object_by_handle(result.handle TSRMLS_CC);

	zend_objects_clone_members(&clone->obj, result, &orig->obj, Z_OBJ_HANDLE_P(object) TSRMLS_CC);
	zend_hash_copy(clone->props, orig->props, (copy_ctor_func_t)zval_add_ref, NULL, sizeof(zval*));

	return result;
}

/**
 * Phalcon\Config initializer
 */
PHALCON_INIT_CLASS(Phalcon_Config){

	PHALCON_REGISTER_CLASS(Phalcon, Config, config, phalcon_config_method_entry, 0);

	phalcon_config_ce->create_object = phalcon_config_object_ctor;

	phalcon_config_object_handlers = *zend_get_std_object_handlers();
	phalcon_config_object_handlers.count_elements  = phalcon_config_count_elements;
	phalcon_config_object_handlers.read_property   = phalcon_config_read_property;
	phalcon_config_object_handlers.write_property  = phalcon_config_write_property;
	phalcon_config_object_handlers.unset_property  = phalcon_config_unset_property;
	phalcon_config_object_handlers.has_property    = phalcon_config_has_property;
	phalcon_config_object_handlers.read_dimension  = phalcon_config_read_dimension;
	phalcon_config_object_handlers.write_dimension = phalcon_config_write_dimension;
	phalcon_config_object_handlers.unset_dimension = phalcon_config_unset_dimension;
	phalcon_config_object_handlers.has_dimension   = phalcon_config_has_dimension;
	phalcon_config_object_handlers.get_properties  = phalcon_config_get_properties;
	phalcon_config_object_handlers.compare_objects = phalcon_config_compare_objects;
	phalcon_config_object_handlers.clone_obj       = phalcon_config_clone_obj;

	zend_class_implements(phalcon_config_ce TSRMLS_CC, 2, zend_ce_arrayaccess, spl_ce_Countable);

	return SUCCESS;
}

/**
 * Internal implementation of __construct(). Used to avoid calls to userspace when
 * recursively walking the configuration array. Does not use MM.
 */
void phalcon_config_construct_internal(zval* this_ptr, zval *array_config TSRMLS_DC)
{
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	phalcon_config_object* obj;

	if (!array_config || Z_TYPE_P(array_config) == IS_NULL) {
		return;
	}

	phalcon_is_iterable(array_config, &ah0, &hp0, 0, 0);

	obj = fetchPhalconConfigObject(getThis() TSRMLS_CC);

	while (zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) == SUCCESS) {
		zval key = phalcon_get_current_key_w(ah0, &hp0);
		phalcon_config_write_internal(obj, &key, *hd TSRMLS_CC);
		zend_hash_move_forward_ex(ah0, &hp0);
	}
}

/**
 * Internal implementation of non-recursive @c toArray(). Used as an alternative
 * to @c get_object_properties().
 */
PHALCON_ATTR_WARN_UNUSED_RESULT static int phalcon_config_toarray_internal(zval **return_value_ptr, zval *this_ptr TSRMLS_DC)
{
	phalcon_config_object *obj = fetchPhalconConfigObject(this_ptr TSRMLS_CC);
	int result;

	assert(!EG(exception));
	if (likely(obj->obj.ce == phalcon_config_ce)) {
		zval *tmp;
		array_init_size(*return_value_ptr, zend_hash_num_elements(obj->props));
		zend_hash_copy(Z_ARRVAL_PP(return_value_ptr), obj->props, (copy_ctor_func_t)zval_add_ref, (void*)&tmp, sizeof(zval*));
		return SUCCESS;
	}

	if (phalcon_method_exists_ex(this_ptr, SS("toarray") TSRMLS_CC) == SUCCESS) {
		zval *return_value = *return_value_ptr;
		result = phalcon_return_call_method(return_value, return_value_ptr, this_ptr, "toarray", 0, NULL TSRMLS_CC);
	}
	else {
		zval *params[] = { this_ptr };
		zval *return_value = *return_value_ptr;
		result = phalcon_return_call_function(return_value, return_value_ptr, SL("get_object_vars"), 1, params TSRMLS_CC);
	}

	return result;
}

/**
 * Phalcon\Config constructor
 *
 * @param array $arrayConfig
 */
PHP_METHOD(Phalcon_Config, __construct){

	zval *array_config = NULL;

	phalcon_fetch_params(0, 0, 1, &array_config);
	
	/** 
	 * Throw exceptions if bad parameters are passed
	 */
	if (array_config && Z_TYPE_P(array_config) != IS_ARRAY && Z_TYPE_P(array_config) != IS_NULL) {
		PHALCON_THROW_EXCEPTION_STRW(phalcon_config_exception_ce, "The configuration must be an Array");
		return;
	}

	phalcon_config_construct_internal(getThis(), array_config TSRMLS_CC);
}

/**
 * Allows to check whether an attribute is defined using the array-syntax
 *
 *<code>
 * var_dump(isset($config['database']));
 *</code>
 *
 * @param string $index
 * @return boolean
 */
PHP_METHOD(Phalcon_Config, offsetExists){

	zval *index;

	phalcon_fetch_params(0, 1, 0, &index);
	RETURN_BOOL(phalcon_config_has_internal(fetchPhalconConfigObject(getThis() TSRMLS_CC), index, 0 TSRMLS_CC));
}

/**
 * Gets an attribute from the configuration, if the attribute isn't defined returns null
 * If the value is exactly null or is not defined the default value will be used instead
 *
 *<code>
 * echo $config->get('controllersDir', '../app/controllers/');
 *</code>
 *
 * @param string $index
 * @param mixed $defaultValue
 * @return mixed
 */
PHP_METHOD(Phalcon_Config, get){

	zval *index, *default_value = NULL, *value;

	phalcon_fetch_params(0, 1, 1, &index, &default_value);

	value = phalcon_config_read_internal(fetchPhalconConfigObject(getThis() TSRMLS_CC), index, BP_VAR_NA TSRMLS_CC);
	if (!value || Z_TYPE_P(value) == IS_NULL) {
		if (default_value) {
			RETURN_ZVAL(default_value, 1, 0);
		}

		RETURN_NULL();
	}

	RETURN_ZVAL(value, 1, 0);
}

/**
 * Gets an attribute using the array-syntax
 *
 *<code>
 * print_r($config['database']);
 *</code>
 *
 * @param string $index
 * @return string
 */
PHP_METHOD(Phalcon_Config, offsetGet){

	zval *index;
	zval* retval;

	phalcon_fetch_params(0, 1, 0, &index);

	retval = phalcon_config_read_internal(fetchPhalconConfigObject(getThis() TSRMLS_CC), index, BP_VAR_R TSRMLS_CC);
	RETURN_ZVAL(retval, 1, 0);
}

/**
 * Sets an attribute using the array-syntax
 *
 *<code>
 * $config['database'] = array('type' => 'Sqlite');
 *</code>
 *
 * @param string $index
 * @param mixed $value
 */
PHP_METHOD(Phalcon_Config, offsetSet){

	zval *index, *value;

	phalcon_fetch_params(0, 2, 0, &index, &value);
	phalcon_config_write_internal(fetchPhalconConfigObject(getThis() TSRMLS_CC), index, value TSRMLS_CC);
}

/**
 * Unsets an attribute using the array-syntax
 *
 *<code>
 * unset($config['database']);
 *</code>
 *
 * @param string $index
 */
PHP_METHOD(Phalcon_Config, offsetUnset){

	zval *index;

	phalcon_fetch_params(0, 1, 0, &index);
	phalcon_config_unset_internal(fetchPhalconConfigObject(getThis() TSRMLS_CC), index TSRMLS_CC);
}

/**
 * Merges a configuration into the current one
 *
 * @brief void Phalcon\Config::merge(array|object $with)
 *
 *<code>
 *	$appConfig = new Phalcon\Config(array('database' => array('host' => 'localhost')));
 *	$globalConfig->merge($config2);
 *</code>
 *
 * @param Phalcon\Config $config
 * @return Phalcon\Config
 */
PHP_METHOD(Phalcon_Config, merge){

	zval *config, *array_config = NULL, key, *active_value = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	phalcon_config_object *obj;

	phalcon_fetch_params(0, 1, 0, &config);
	
	if (Z_TYPE_P(config) != IS_OBJECT && Z_TYPE_P(config) != IS_ARRAY) {
		zend_throw_exception_ex(phalcon_config_exception_ce, 0 TSRMLS_CC, "Configuration must be an object or array");
		return;
	}

	if (Z_TYPE_P(config) == IS_OBJECT) {
		ALLOC_INIT_ZVAL(array_config);
		if (FAILURE == phalcon_config_toarray_internal(&array_config, config TSRMLS_CC)) {
			zval_ptr_dtor(&array_config);
			return;
		}
	}
	else {
		array_config = config;
		Z_ADDREF_P(array_config);
	}
	
	phalcon_is_iterable(array_config, &ah0, &hp0, 0, 0);
	
	obj = fetchPhalconConfigObject(getThis() TSRMLS_CC);

	while (zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) == SUCCESS) {
	
		key = phalcon_get_current_key_w(ah0, &hp0);
	
		active_value = phalcon_config_read_internal(obj, &key, BP_VAR_NA TSRMLS_CC);

		/**
		 * The key is already defined in the object, we have to merge it
		 */
		if (active_value) {
			if ((Z_TYPE_PP(hd)  == IS_OBJECT || Z_TYPE_PP(hd) == IS_ARRAY) && Z_TYPE_P(active_value) == IS_OBJECT) {
				if (phalcon_method_exists_ex(active_value, SS("merge") TSRMLS_CC) == SUCCESS) { /* Path AAA in the test */
					zval *params[] = { *hd };
					if (FAILURE == phalcon_call_method(NULL, active_value, "merge", 1, params TSRMLS_CC)) {
						break;
					}
				}
				else { /* Path AAB in the test */
					phalcon_config_write_internal(obj, &key, *hd TSRMLS_CC);
				}
			}
			else { /* Path AE in the test */
				phalcon_config_write_internal(obj, &key, *hd TSRMLS_CC);
			}
		}
		else { /* Path B in the test */
			/**
			 * The key is not defined in the object, add it
			 */
			phalcon_config_write_internal(obj, &key, *hd TSRMLS_CC);
		}
	
		zend_hash_move_forward_ex(ah0, &hp0);
	}

	zval_ptr_dtor(&array_config);

	RETURN_THISW();
}

/**
 * Converts recursively the object to an array
 *
 * @brief array Phalcon\Config::toArray(bool $recursive = true);
 *
 *<code>
 *	print_r($config->toArray());
 *</code>
 *
 * @return array
 */
PHP_METHOD(Phalcon_Config, toArray){

	zval *recursive = NULL, *tmp;
	phalcon_config_object *obj;

	phalcon_fetch_params(0, 0, 1, &recursive);

	obj = fetchPhalconConfigObject(getThis() TSRMLS_CC);
	array_init_size(return_value, zend_hash_num_elements(obj->props));
	zend_hash_copy(Z_ARRVAL_P(return_value), obj->props, (copy_ctor_func_t)zval_add_ref, (void*)&tmp, sizeof(zval*));

	if (!recursive || zend_is_true(recursive)) {
		zval **value;
		HashPosition hp;

		for (
			zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(return_value), &hp);
			zend_hash_get_current_data_ex(Z_ARRVAL_P(return_value), (void**)&value, &hp) == SUCCESS;
			zend_hash_move_forward_ex(Z_ARRVAL_P(return_value), &hp)
		) {
			zval key = phalcon_get_current_key_w(Z_ARRVAL_P(return_value), &hp);

			if (Z_TYPE_PP(value) == IS_OBJECT && phalcon_method_exists_ex(*value, SS("toarray") TSRMLS_CC) == SUCCESS) {
				zval *array_value = NULL;
				if (FAILURE == phalcon_call_method(&array_value, *value, "toarray", 0, NULL TSRMLS_CC)) {
					break;
				}

				phalcon_array_update_zval(&return_value, &key, array_value, 0);
			}
		}
	}
}

PHP_METHOD(Phalcon_Config, count)
{
	long int cnt;

	phalcon_config_count_elements(getThis(), &cnt TSRMLS_CC);
	RETURN_LONG(cnt);
}

PHP_METHOD(Phalcon_Config, __wakeup)
{
	HashTable *props;
	phalcon_config_object *obj;

	obj   = fetchPhalconConfigObject(getThis() TSRMLS_CC);
	props = zend_std_get_properties(getThis() TSRMLS_CC);
	zend_hash_copy(obj->props, props, (copy_ctor_func_t)zval_add_ref, NULL, sizeof(zval*));
}

/**
 * Restores the state of a Phalcon\Config object
 *
 * @param array $data
 * @return Phalcon\Config
 */
PHP_METHOD(Phalcon_Config, __set_state){

	zval *data;

	phalcon_fetch_params(0, 1, 0, &data);

	object_init_ex(return_value, phalcon_config_ce);
	phalcon_config_construct_internal(return_value, data TSRMLS_CC);
}
