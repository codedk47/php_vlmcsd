# php_vlmcsd
<h4>PHP7.2 extension php_vlmcsd for windows compile VS15</h4>
<a href="https://github.com/codedk47/php_vlmcsd/raw/master/php_vlmcsd.dll">php_vlmcsd.dll</a>
<pre>
vlmcsd_rpcserver([string $local_socket = 'tcp://0.0.0.0:1688']);
//or
vlmcsd_rpcserver('tcp://[::]:1688'); //ipv6 support
//or
if($s = stream_socket_server('tcp://0.0.0.0:1688'))
{
	for(;;)
	{
		if($c = stream_socket_accept($s, 6000)) {
			vlmcsd_stream($c);
		}
	}
}
</pre>
