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
		if [ -e getshare ] # checking if getfile exist
		then
			# coping script to the /usr/local/bin
			cp getshare /usr/local/bin/getshare
			if [ -e glocalshare ]
			then
			    #copying gnome application
			    cp glocalshare /usr/local/bin/
			    cp glocalshare.desktop /usr/share/applications/
			    cp builder.ui /usr/local/bin/
			    cp icon.png /usr/local/bin/
			fi
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
exit
