cd domains/ecai23/training/cellular

# 110
rm -rf rule110 && mkdir rule110
PYTHONHASHSEED=1 python3 cellular.py -n 20 -r 110 -s 20 -o rule110/

# 30
rm -rf rule30 && mkdir rule30
PYTHONHASHSEED=1 python3 cellular.py -n 20 -r 30 -s 20 -o rule30/

# 184
rm -rf rule184 && mkdir rule184
PYTHONHASHSEED=1 python3 cellular.py -n 20 -r 184 -s 20 -o rule184/

# 90
rm -rf rule90 && mkdir rule90
PYTHONHASHSEED=1 python3 cellular.py -n 20 -r 90 -s 20 -o rule90/
