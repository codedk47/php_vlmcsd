#include "php_vlmcsd.h"

static int ip2str(SOCKADDR *addrsrc, socklen_t addrlen, BYTE *buf, size_t len)
{
	BYTE addr[40], port[6];
	if (getnameinfo(addrsrc, addrlen, addr, sizeof(addr), port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV) == 0)
	{
		return sprintf_s(buf, len, addrsrc->sa_family == AF_INET6 ? "[%s]:%s" : "%s:%s", addr, port);
	}
	return -1;
}

ZEND_FUNCTION(vlmcsd_rpcserver)
{
	zend_string *local_socket = zend_string_init(ZEND_STRL("tcp://0.0.0.0:1688"), 0);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(local_socket)
	ZEND_PARSE_PARAMETERS_END();

	int err = 0;
	zend_string *errstr;
	php_stream *stream = php_stream_xport_create(ZSTR_VAL(local_socket), ZSTR_LEN(local_socket), REPORT_ERRORS,
		STREAM_XPORT_SERVER | STREAM_XPORT_BIND | STREAM_XPORT_LISTEN,
		NULL, NULL, NULL, &errstr, &err);
	
	if (stream == NULL)
	{
		zend_error(E_ERROR, ZSTR_VAL(errstr));
	}
	
	SOCKET s;
	SOCKADDR_STORAGE_LH addrsrc;
	socklen_t addrlen = sizeof(SOCKADDR_STORAGE_LH);
	BYTE addrstr[64];

	printf("vlmscd_rpcserver(%.*s)\n", (int)ZSTR_LEN(local_socket), ZSTR_VAL(local_socket));
	for (;;)
	{
		s = accept(*(SOCKET*)stream->abstract, (SOCKADDR*)&addrsrc, &addrlen);
		if (s != INVALID_SOCKET && (err = ip2str((SOCKADDR*)&addrsrc, addrlen, addrstr, sizeof(addrstr))) != -1)
		{
			printf("Sending activation request(%.*s)...\n", err, addrstr);
			rpcServer(s, 1, addrstr);
		}
	}
	php_stream_to_zval(stream, return_value);
}
ZEND_FUNCTION(vlmcsd_stream)
{
	zval *zstream;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_RESOURCE(zstream)
	ZEND_PARSE_PARAMETERS_END();

	php_stream *stream;
	php_stream_from_zval(stream, zstream);

	SOCKET s = *(SOCKET*)stream->abstract;
	SOCKADDR_STORAGE_LH addrsrc;
	socklen_t addrlen = sizeof(SOCKADDR_STORAGE_LH);
	BYTE addrstr[64];

	if (getpeername(s, (SOCKADDR*)&addrsrc, &addrlen) == 0 && ip2str((SOCKADDR*)&addrsrc, addrlen, addrstr, sizeof(addrstr)) != -1)
	{
		rpcServer(s, 1, addrstr);
	}
}
const zend_function_entry vlmcsd_functions[] = {
	ZEND_FE(vlmcsd_rpcserver, NULL)
	ZEND_FE(vlmcsd_stream, NULL)
	ZEND_FE_END
};
ZEND_MINIT_FUNCTION(vlmcsd)
{
	randomNumberInit();
	loadKmsData();
	return SUCCESS;
}
zend_module_entry vlmcsd_module_entry = {
	STANDARD_MODULE_HEADER,
	"vlmcsd",
	vlmcsd_functions,
	ZEND_MINIT(vlmcsd),
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES
};
ZEND_GET_MODULE(vlmcsd)