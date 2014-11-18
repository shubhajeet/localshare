#########################################################
#
#	UNISTALLATION SCRIPT FOR LOCALSHARE
#
#########################################################
#!/bin/sh
if [ -e /usr/local/bin ] # checking if directory to be copied exist
then
	if [ -e /usr/local/bin/localshare ] # checking if the script exist
	then
		# removing the script
		rm /usr/local/bin/localshare
		echo "/usr/local/bin/localshare is deleted"
		if [ -e /usr/local/bin/getshare ] # checking if the script exist
		then
			# removing the script
			rm /usr/local/bin/getshare
			if [ -e /usr/local/bin/glocalshare ]
			then
			    rm /usr/local/bin/glocalshare
			    rm -r /usr/share/glocalshare
			    rm /usr/share/applications/glocalshare.desktop
			fi
		else
			echo "ERROR: getfile does not exist"
		fi
	else
		echo "ERROR: localshare does not exist"
	fi
else
	echo "ERROR: /usr/local/bin does not exist"
	echo "Probably not a linux system or a weird linux system"
fi 	
