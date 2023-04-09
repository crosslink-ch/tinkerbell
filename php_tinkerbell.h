/* tinkerbell extension for PHP */

#ifndef PHP_TINKERBELL_H
# define PHP_TINKERBELL_H

extern zend_module_entry tinkerbell_module_entry;
# define phpext_tinkerbell_ptr &tinkerbell_module_entry

# define PHP_TINKERBELL_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_TINKERBELL)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_TINKERBELL_H */
