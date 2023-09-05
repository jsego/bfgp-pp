echo $#
echo "$@"

argc=$#
argv=("$@")


folder=""
eval_funcs=""
lines=""
for (( j=1; j < argc; j++ )); do
	if [ ${argv[j]} = "-f" ]; then
	    folder="${argv[j+1]}"
	elif [ ${argv[j]} = "-e" ]; then
		for (( k=j+1; k < argc; k++ )); do
			if [[ ${argv[k]} == -* ]]; then
				break
			fi
			eval_funcs=$eval_funcs"_${argv[k]}"
		done
	elif [ ${argv[j]} = "-l" ]; then
		lines="_${argv[j+1]}"
    fi
done

experiments_folder="experiments/"$(echo $folder | cut -d'/' -f 2-3)"/"
experiments_file=$experiments_folder$(echo $folder | cut -d'/' -f 4-4)$lines$eval_funcs".out"
mkdir -p $experiments_folder
touch $experiments_file
echo $experiments_file
# shellcheck disable=SC2068
timeout 3600 /usr/bin/time -f "time result\ncmd:%C\nreal %es\nmemory:%MKB \n" $@ 2>> $experiments_file

