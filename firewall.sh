#!/bin/bash
cat > packets.txt
	while read -r line ; do
		cat packets.txt > packets_copy.txt
		line=`echo "$line" | sed 's/ //g' | cut -f1 -d "#"`
		if [ "$line" == "" ]; then
			continue
		fi
		IFS=',' read -r -a rules <<< "$line"
		for rule in "${rules[@]}" ; do
			if [ "$rule" == "" ]; then
				continue
			fi
			cat packets_copy.txt |./firewall.exe "$rule" > valid_packet.txt 
			cat valid_packet.txt > packets_copy.txt
		done
		cat packets_copy.txt >> packets_to_print.txt

	done <$1
	echo "$(<packets_to_print.txt)" | sed '/^$/d' | uniq | sed 's/ //g' | sort
	rm *.txt
