# php_vlmcsd
php_vlmcsd

vlmcsd_rpcserver();

vlmcsd_rpcserver('tcp://0.0.0.0:1688');

vlmcsd_rpcserver('tcp://[::]:1688');

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
