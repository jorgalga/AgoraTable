<?php
$db = pg_connect("host=127.0.0.1 port=5432 dbname=gesturedb user=gesturedb password=#fribourg#");

define("ROOT_PATH","/var/www");
define("AUDIO_PATH","/var/www/gesturedb/media/audios/");
define("ICON_PATH","/var/www/gesturedb/media/icons/");
define("IMAGE_PATH","/var/www/gesturedb/media/images/");
define("PDF_PATH","/var/www/gesturedb/media/pdfs/");
define("QRCODE_PATH","/var/www/gesturedb/media/qrcodes/");
define("USERPICTURE_PATH","/var/www/gesturedb/media/userpictures/");
define("VIDEO_PATH","/var/www/gesturedb/media/videos/");
define("LOG_PATH","/var/www/gesturedb/media/log.txt");

!is_dir(AUDIO_PATH) && mkdir(AUDIO_PATH,0755,true);
!is_dir(ICON_PATH) && mkdir(ICON_PATH,0755,true);
!is_dir(IMAGE_PATH) && mkdir(IMAGE_PATH,0755,true);
!is_dir(PDF_PATH) && mkdir(PDF_PATH,0755,true);
!is_dir(QRCODE_PATH) && mkdir(QRCODE_PATH,0755,true);
!is_dir(USERPICTURE_PATH) && mkdir(USERPICTURE_PATH,0755,true);
!is_dir(VIDEO_PATH) && mkdir(VIDEO_PATH,0755,true);

define("VISUALIZATION_IP", "192.168.5.156");
define("VISUALIZATION_PORT", "12345");

define("MAILADDR_FROM", "andreas.pramboeck@aec.at");

require_once("lib.php");
?>
