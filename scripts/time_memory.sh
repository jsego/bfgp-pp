experiments_file="experiments/"$(echo $3 | cut -d'/' -f 2-3)
#validator="./validator.bin"
argc=$#
argv=("$@")

experiments_file=$experiments_file"_${argv[1]}"
for (( j=3; j < argc; j++ )); do
    experiments_file=$experiments_file"_${argv[j]}"
done

#if [ $validator != $1 ] && [ $# -eq 3 ]; then
#	experiments_file=$experiments_file"_h5"
#fi

experiments_file=$experiments_file".out"
echo $experiments_file
# shellcheck disable=SC2068
timeout 3600 /usr/bin/time -f "time result\ncmd:%C\nreal %es\nmemory:%MKB \n" $@ 2>> $experiments_file
#/usr/bin/time -f "time result\ncmd:%C\nreal %es\nuser %Us \nsys  %Ss \nmemory:%MKB \ncpu %P" $@
