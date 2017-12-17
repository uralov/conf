root $root_path;
index index.php index.html index.htm;
error_page   404  =  /404.php;
charset utf-8;

location ~* ^.+\.(jpg|jpeg|gif|png|ico|css|bmp|js|swf|flv)$ {
    root $root_path;
    access_log off;
    expires 3d; # кешируем у клиента на 3 дня
}

location ~ \.php$ {
    fastcgi_pass unix:///var/run/php5-fpm.sock;
    fastcgi_index  index.php;
    fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
    fastcgi_param  DOCUMENT_ROOT $root_path;
    include        fastcgi_params;
}

set $mgr_proxy "http://";
location ^~ /manimg/ {
	alias /usr/local/ispmgr/skins/;
}
location ^~ /manager {
	proxy_pass $mgr_proxy;
	proxy_redirect $mgr_proxy /;
	proxy_set_header Host $host:$server_port;
	proxy_set_header X-Forwarded-For $remote_addr;
	proxy_set_header X-Forwarded-Proto $scheme;
	proxy_set_header X-Real-IP $remote_addr;
	proxy_set_header X-Manager-Path /manager;
}
location ^~ /mancgi/ {
	proxy_pass $mgr_proxy;
	proxy_redirect $mgr_proxy /;
	proxy_set_header Host $host:$server_port;
	proxy_set_header X-Forwarded-For $remote_addr;
	proxy_set_header X-Forwarded-Proto $scheme;
	proxy_set_header X-Real-IP $remote_addr;
}
