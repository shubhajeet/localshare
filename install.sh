#########################################################
#
#	INSTALLATION SCRIPT FOR LOCALSHARE
#
#########################################################
#!/bin/sh
if [ -e /usr/local/bin ] # checking if the directory where file to be copied exist
then
	if [ -e localshare ] # checking if localshare exist
	then
		# coping script to the /usr/local/bin
		cp localshare /usr/local/bin/localshare
		if [ -e getfile ] # checking if getfile exist
		then
			# coping script to the /usr/local/bin
			cp getfile /usr/local/bin/getfile
		else
			echo "ERROR: getfile does not exist"
			rm /usr/local/bin/localshare
		fi
	else
		echo "ERROR: localshare does not exist"
	fi
else
	echo "ERROR: /usr/local/bin does not exist"
	echo "Probably not a linux system or a weird linux system"
fi
 	
