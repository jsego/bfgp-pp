cd domains/ecai23/testing/cellular

# 110
rm -rf rule110 && mkdir rule110
PYTHONHASHSEED=1 python3 cellular.py -n 100 -r 110 -s 100 -o rule110/

# 30
rm -rf rule30 && mkdir rule30
PYTHONHASHSEED=1 python3 cellular.py -n 100 -r 30 -s 100 -o rule30/

# 184
rm -rf rule184 && mkdir rule184
PYTHONHASHSEED=1 python3 cellular.py -n 100 -r 184 -s 100 -o rule184/

# 90
rm -rf rule90 && mkdir rule90
PYTHONHASHSEED=1 python3 cellular.py -n 100 -r 90 -s 100 -o rule90/
