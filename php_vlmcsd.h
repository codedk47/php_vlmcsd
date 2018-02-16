#ifndef PHP_VLMCSD_H
#define PHP_VLMCSD_H
#define PHP_COMPILER_ID "VC14"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"Shlwapi.lib")
#include "network.h"
#include "kmsdata.h"
#include "helpers.h"
#include "rpc.h"
#include "php.h"
#include "zend.h"

zend_module_entry vlmcsd_module_entry;

#endif//PHP_VLMCSD_H