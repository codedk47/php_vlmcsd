# php_vlmcsd
<h4>php_vlmcsd for PHP7.2.3 extension on windows compile VS15</h4>

<pre>
<?php
vlmcsd_rpcserver([string $local_socket = 'tcp://0.0.0.0:1688']);
//or
vlmcsd_rpcserver('tcp://0.0.0.0:1688');
//or
vlmcsd_rpcserver('tcp://[::]:1688');
//or
if($s = stream_socket_server('tcp://0.0.0.0:1688'))
{
	for(;;) {
		if($c = stream_socket_accept($s, 6000)) {
			vlmcsd_stream($c);
		}
	}
}
</pre>
