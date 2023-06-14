echo 'VALIDATION'
domains=("corridor" "fibonacci" "find" "gripper" "reverse" "select" "sorting" "triangular_sum" "visitall")
domain_args=('-f 12 -t 1011' '-f 12 -t 44' '-f 100 -s 10 -t 1100' '-f 12 -t 1011' '-m validation -f 100 -s 10 -t 1100' '-m validation -f 100 -s 10 -t 1100' '-m validation -f 12 -s 1 -t 111' '-f 12 -t 1011' '-f 12 -t 61')
total=${#domains[@]}
root_folder="domains/aij23/validation/"
# for d in ${domains[@]}
for (( i=0; i<$(($total)); i++ ))
do		
	d=${domains[i]}
	args=${domain_args[i]}
	folder="$root_folder$d/"
	echo "Generating $d instances at $folder..."
	if [ -d $folder ]; then
		rm -rf $folder/*
	else
		mkdir -p $folder
	fi
	PYTHONHASHSEED=0 python domains/aij23/generators/$d.py $args -o $folder	
done




