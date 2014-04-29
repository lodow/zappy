#!/usr/bin/php
<?php

function my_exit($fp)
{
	fclose($fp);
	exit(0);
}

function ia($fp, $team, $host, $port)
{

	if (fgets($fp) != "BIENVENUE\n")
	   my_exit($fp);
	fwrite($fp, $team."\n");
	$num_client = (int) fgets($fp);
	$map_size = fgets($fp);
	$map_size_x = explode(" ", $map_size);
	$map_size_y =(int) $map_size_x[1];
	$map_size_x = (int) $map_size_x[0];
	echo "CLIENT #$num_client connect\nMap $map_size_x x $map_size_y\n";
	for ($i = 0; $i < 5; $i++)
	{
		fwrite($fp, "avance"."\n");
		if (fgets($fp) != "ok\n")
	   	   my_exit($fp);
		sleep(1);
	}
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
$fp = fsockopen($host, $port, $errno, $errstr);
if (!$fp)
   {
	echo "ERROR: $errno - $errstr<br />\n";
    	exit(0);
   }
else
   {
	ia($fp, $team, $host, $port);
	fclose($fp);
   }
?>