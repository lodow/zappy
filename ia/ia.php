#!/usr/bin/php
<?php

function ia($fp, $team, $host, $port)
{

}

if ($argc < 5)
   {
	echo "USAGE ./$argv[0] -n team_name -p port [-h host]\n";
	exit(0);
   }
$port = -1;
$host = "localhost";
$team = "";
$i = 1;
while ($i < $argc)
      {
	if ($argv[$i] == "-n" && $i + 1 < $argc && strncmp($argv[$i + 1], "-", 1) != 0)
	   $team = $argv[$i + 1];
	if ($argv[$i] == "-p" && $i + 1 < $argc && is_numeric($argv[$i + 1]))
	   $port = (int) $argv[$i + 1];
	if ($argv[$i] == "-h" && $i + 1 < $argc && strncmp($argv[$i + 1], "-", 1) != 0)
	   $host = (int) $argv[$i + 1];
	$i++;
      }
if ($team == "" || $port == -1)
   {
	echo "USAGE ./$argv[0] -n team_name -p port [-h host]\n";
	exit(0);
   }
$fp = fsockopen("udp://".$host, $port, $errno, $errstr);
if (!$fp)
   {
	echo "ERROR: $errno - $errstr<br />\n";
    	exit(0);
   }
else
   {
	ia($fp, $team, $host, $port);
   }
?>