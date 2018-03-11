# php_vlmcsd
<a href="/codedk47/php_vlmcsd/raw/master/php_vlmcsd.dll">php_vlmcsd.dll (PHP7.2 For Windows10 VC15 x64 TS)</a><br>
<pre>
vlmcsd_rpcserver([string $local_socket = 'tcp://0.0.0.0:1688']);
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
</pre>
