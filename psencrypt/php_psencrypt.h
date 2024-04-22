/* psencrypt extension for PHP (c) 2024 Netor0x86 */

#ifndef PHP_PSENCRYPT_H
# define PHP_PSENCRYPT_H

extern zend_module_entry psencrypt_module_entry;
# define phpext_psencrypt_ptr &psencrypt_module_entry

# define PHP_PSENCRYPT_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_PSENCRYPT)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_PSENCRYPT_H */
