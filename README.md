# php_vlmcsd
[php_vlmcsd.dll (PHP7.2 For Windows10 VC15 x64 TS)](https://github.com/codedk47/php_vlmcsd/raw/master/php_vlmcsd.dll)
```php
vlmcsd_rpcserver();
//or
vlmcsd_rpcserver('tcp://[::]:1688'); //ipv6 support
//or
if($s = stream_socket_server('tcp://0.0.0.0:1688'))
{
	for(;;)
	{
		if($c = stream_socket_accept($s, 6000))
		{
			vlmcsd_stream($c);
		}
	}
}
```
